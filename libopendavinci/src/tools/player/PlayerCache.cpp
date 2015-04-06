/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <cstdlib>
#include <cstring>

#include "core/base/Lock.h"
#include "core/base/Thread.h"

#include "core/data/SharedData.h"
#include "core/data/image/SharedImage.h"
#include "core/wrapper/SharedMemoryFactory.h"

#include "tools/MemorySegment.h"
#include "tools/player/PlayerCache.h"

namespace tools {
    namespace player {

        using namespace std;
        using namespace core;
        using namespace core::base;
        using namespace core::data;
        using namespace tools;

        PlayerCache::PlayerCache(const uint32_t size, const uint32_t sizeMemorySegments, const bool &autoRewind, istream &in, istream *inSharedMemoryFile) :
                m_cacheSize(size),
                m_autoRewind(autoRewind),
                m_in(in),
                m_inSharedMemoryFile(inSharedMemoryFile),
                m_queue(),
                m_recBuffer(),
                m_memBuffer(),
                m_mapOfMemories(),
                m_bufferIn(),
                m_bufferOut(),
                m_sharedPointers(),
                m_modifyCacheMutex() {
            m_cacheSize = (m_cacheSize < 3) ? 3 : m_cacheSize;
            m_queue.clear();

            m_recBuffer.clear();
            m_memBuffer.clear();

            cout << "PlayerCache: preparing buffer...";
            for(uint32_t id = 0; id < m_cacheSize; id++) {
                MemorySegment ms;
                ms.m_size = sizeMemorySegments;
                ms.m_id = id;
                void *ptr = ::malloc(ms.m_size);
                m_mapOfMemories[ms.m_id] = static_cast<char*>(ptr);

                Container c(Container::UNDEFINEDDATA, ms);
                m_bufferIn.enter(c);
            }
            cout << "done." << endl;

            // Start over.
            clearQueueRewindInputStreams();
        }

        PlayerCache::~PlayerCache() {
            m_queue.clear();

            cout << "PlayerCache: cleaning up buffers..." << endl;

            for(map<uint32_t, char*>::iterator it = m_mapOfMemories.begin();
                it != m_mapOfMemories.end(); it++) {
                cout << "Cleaning memory segment " << it->first << endl;
                ::free(it->second);
            }

            m_bufferIn.clear();
            m_bufferOut.clear();

            cout << "done." << endl;
        }

        Container PlayerCache::getNextContainer() {
            Container c;

            if (getNumberOfEntries() > 0) {
                c = m_queue.leave();
            }

            return c;
        }

        uint32_t PlayerCache::getNumberOfEntries() const {
            return m_queue.getSize();
        }

        void PlayerCache::rewindInputStreams() {
            // Start from beginning.
            m_in.clear();

            // Seek to the beginning of the input stream.
            m_in.seekg(ios::beg);

            // If a memory dump file was found, reset it as well.
            if (m_inSharedMemoryFile != NULL) {
                m_inSharedMemoryFile->clear();
                m_inSharedMemoryFile->seekg(ios::beg);
            }
        }

        void PlayerCache::clearQueueRewindInputStreams() {
            Lock l(m_modifyCacheMutex);

            m_queue.clear();

            // Put all memory segments from m_bufferOut back to m_bufferIn for re-use.
            while (!m_bufferOut.isEmpty()) {
                Container c = m_bufferOut.leave();
                m_bufferIn.enter(c);
            }

            rewindInputStreams();
        }

        void PlayerCache::updateCache() {
            // Do only fill cache if not in currently rewinding.
            Lock l(m_modifyCacheMutex);

            // Read further data ONLY IFF the cache has free slots AND the buffer for shared memory segments is not completely filled.
            const uint32_t numberOfEntries = m_queue.getSize();
            while ( (numberOfEntries < m_cacheSize) && (!m_bufferIn.isEmpty()) ) {
                bool bufferFilled = fillCache();
                if (!bufferFilled) {
                    if (m_autoRewind) {
                        // Rewind streams without clearing the current cache.
                        rewindInputStreams();
                    }
                    break;
                }
            }
        }

        void PlayerCache::beforeStop() {}

        void PlayerCache::run() {
            serviceReady();

            while (isRunning()) {
                updateCache();

                Thread::usleep(1000);
            }
            cerr << "PlayerCache: No more data to cache." << endl;
        }

        bool PlayerCache::fillCache() {
            Container fromRecFile;
            Container fromMemFile;

            bool readFromRecFile = false;
            bool readFromMemFile = false;

            // Get next datum from m_rec:
            if (!m_recBuffer.isEmpty()) {
                // Check if a previously delayed entry (due to younger time stamps) need to be processed.
                fromRecFile = m_recBuffer.pop();
                readFromRecFile = true;
            }
            else {
                // Try to read directly from file.
                if (m_in.good()) {
                    m_in >> fromRecFile;
                    if (m_in.gcount() > 0) {
                        readFromRecFile = true;
                    }
                }
            }

            // Get next datum from m_mem:
            if (!m_memBuffer.isEmpty()) {
                // Check if a previously delayed entry (due to younger time stamps) need to be processed.
                fromMemFile = m_memBuffer.pop();
                readFromMemFile = true;
            }
            else {
                if ( (m_inSharedMemoryFile != NULL) && (m_inSharedMemoryFile->good()) ) {
                    *m_inSharedMemoryFile >> fromMemFile;

                    if (m_inSharedMemoryFile->gcount() > 0) {
                        putRawMemoryDataIntoBuffer(fromMemFile);
                        readFromMemFile = true;
                    }
                }
            }

            // Multiplexing if both, a .rec and a .mem file were found.
            if (readFromRecFile && readFromMemFile) {
                // Compare timestamps from both Containers, put the older one into the queue and the younger one into the mem/recBuffer.
                if (fromRecFile.getReceivedTimeStamp() < fromMemFile.getReceivedTimeStamp()) {
                    m_queue.enter(fromRecFile);
                    m_memBuffer.push(fromMemFile);
                }
                else {
                    m_recBuffer.push(fromRecFile);
                    m_queue.enter(fromMemFile);
                }
            }

            if (readFromRecFile && !readFromMemFile) {
                m_queue.enter(fromRecFile);
            }

            if (!readFromRecFile && readFromMemFile) {
                m_queue.enter(fromMemFile);
            }

            if (!readFromRecFile && !readFromMemFile) {
                // Data could not be read - neither from the rec file nor from the mem file. 
            }

            return (readFromRecFile || readFromMemFile);
        }

        void PlayerCache::putRawMemoryDataIntoBuffer(Container &header) {
            if (!m_bufferIn.isEmpty()) {
                string nameOfSharedMemory = "";
                uint32_t size = 0;

                if (header.getDataType() == Container::SHARED_IMAGE) {
                    core::data::image::SharedImage si = header.getData<core::data::image::SharedImage>();

                    nameOfSharedMemory = si.getName();
                    size = si.getSize();
                }
                else if (header.getDataType() == Container::SHARED_DATA) {
                    core::data::SharedData sd = header.getData<core::data::SharedData>();

                    nameOfSharedMemory = sd.getName();
                    size = sd.getSize();
                }

                // Check, whether a shared memory was already created for this SharedImage or SharedData; otherwise, create it and save it for later.
                map<string, SharedPointer<core::wrapper::SharedMemory> >::iterator it = m_sharedPointers.find(nameOfSharedMemory);
                if (it == m_sharedPointers.end()) {
                    SharedPointer<core::wrapper::SharedMemory> sp = core::wrapper::SharedMemoryFactory::createSharedMemory(nameOfSharedMemory, size);
                    m_sharedPointers[nameOfSharedMemory] = sp;
                }

                // Get current position in stream.
                int32_t curr = m_inSharedMemoryFile->tellg();

                // Get pointer to next available memory segment from the buffer.
                Container c = m_bufferIn.leave();
                MemorySegment ms = c.getData<MemorySegment>();

                // Store meta data.
                ms.m_header = header;

                // Get pointer to memory where to store the data.
                char *ptrToMemory = m_mapOfMemories[ms.m_id];

                // Seek to the current position in the stream.
                m_inSharedMemoryFile->seekg(curr);

                // Read the data into the buffer.
                m_inSharedMemoryFile->read(ptrToMemory, size);

                // Store the consumed size of the MemorySegment.
                ms.m_consumedSize = size;

                // Save meta information.
                c = Container(Container::UNDEFINEDDATA, ms);

                // Put the processed element into the output buffer.
                m_bufferOut.enter(c);
            }
        }

        void PlayerCache::copyMemoryToSharedMemory(core::data::Container &container) {
            // The m_bufferOut should never run empty.
            if (!m_bufferOut.isEmpty()) {
                string nameOfSharedMemory = "";

                // SharedData meta data structure does not provide size information; thus, it is not handled.

                if (container.getDataType() == Container::SHARED_IMAGE) {
                    core::data::image::SharedImage si = container.getData<core::data::image::SharedImage>();
                    nameOfSharedMemory = si.getName();
                }
                else if (container.getDataType() == Container::SHARED_DATA) {
                    core::data::SharedData sd = container.getData<core::data::SharedData>();
                    nameOfSharedMemory = sd.getName();
                }

                // Check, if a shared memory exists for this container.
                map<string, SharedPointer<core::wrapper::SharedMemory> >::iterator it = m_sharedPointers.find(nameOfSharedMemory);
                if (it != m_sharedPointers.end()) {
                    // Get next entry to process from output queue.
                    Container c = m_bufferOut.leave();
                    MemorySegment ms = c.getData<MemorySegment>();

                    // Get pointer to memory with the data.
                    char *src = m_mapOfMemories[ms.m_id];

                    // Get shared memory based on "header" informaton.
                    SharedPointer<core::wrapper::SharedMemory> sp = it->second;

                    // memcpy src to shared memory.
                    ::memcpy(sp->getSharedMemory(), src, ms.m_consumedSize);

                    // Reset meta information.
                    ms.m_consumedSize = 0;

                    // Save meta information.
                    c = Container(Container::UNDEFINEDDATA, ms);

                    // After processing, return the processed memory segment to input queue.
                    m_bufferIn.enter(c);
                }
            }
        }

    } // player
} // tools

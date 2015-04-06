/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/wrapper/SharedMemoryFactory.h"
#include "core/io/StreamFactory.h"
#include "core/io/URL.h"

#include "tools/MemorySegment.h"
#include "tools/recorder/SharedDataListener.h"

namespace tools {

    namespace recorder {

        using namespace core;
        using namespace core::base;
        using namespace core::data;
        using namespace core::data::image;
        using namespace core::io;
        using namespace tools;

        SharedDataListener::SharedDataListener(ostream &out, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const bool &threading) :
            m_threading(threading),
            m_sharedDataWriter(NULL),
		    m_mapOfAvailableSharedData(),
		    m_mapOfAvailableSharedImages(),
            m_mapOfMemories(),
            m_bufferIn(),
            m_bufferOut(),
            m_droppedSharedMemories(0),
            m_sharedPointers(),
            m_out(out) {

            cout << "SharedDataListener: preparing buffer...";
            for(uint32_t id = 0; id < numberOfMemorySegments; id++) {
                MemorySegment ms;
                ms.m_size = memorySegmentSize;
                ms.m_id = id;
                void *ptr = ::malloc(ms.m_size);
                m_mapOfMemories[ms.m_id] = static_cast<char*>(ptr);

                Container c(Container::UNDEFINEDDATA, ms);
                m_bufferIn.enter(c);
            }
            cout << "done." << endl;

            m_sharedDataWriter = new SharedDataWriter(m_out, m_mapOfMemories, m_bufferIn, m_bufferOut);
            if ( (m_sharedDataWriter != NULL) && (m_threading) ) {
                m_sharedDataWriter->start();
            }
        }

        SharedDataListener::~SharedDataListener() {
            if ( (m_sharedDataWriter != NULL) && (m_threading) ) {
                m_sharedDataWriter->stop();
            }
            OPENDAVINCI_CORE_DELETE_POINTER(m_sharedDataWriter);

            cout << "SharedDataListener: Cleaning up buffers..." << endl;

            m_out.flush();

            for(map<uint32_t, char*>::iterator it = m_mapOfMemories.begin();
                it != m_mapOfMemories.end(); it++) {
                cout << "  Cleaning memory segment " << it->first << endl;
                ::free(it->second);
            }

            m_bufferIn.clear();
            m_bufferOut.clear();

            cout << "done." << endl;
        }

        bool SharedDataListener::copySharedMemoryToMemorySegment(const string &name, const Container &header) {
            bool copied = false;

            // Check if m_bufferIn has some capacity left to store the new image.
            if (!m_bufferIn.isEmpty()) {
                // Get next usable memory segment.
                Container c = m_bufferIn.leave();
                MemorySegment ms = c.getData<MemorySegment>();

                // Copy the data.
                SharedPointer<core::wrapper::SharedMemory> memory = m_sharedPointers[name];
                if ( (memory.isValid()) && (memory->isValid()) ) {
                    char *destPtr = m_mapOfMemories[ms.m_id];

                    // Lock shared memory segment.                
                    memory->lock();
                        if (memory->getSize() < ms.m_size) {
                            // Get pointer to shared memory segment.
                            char *src = static_cast<char*>(memory->getSharedMemory());

                            // Copy data from shared memory segment into MemorySegment data structure.
                            ::memcpy(destPtr, src, memory->getSize());

                            // Store meta information.
                            ms.m_header = header;
                            ms.m_consumedSize = memory->getSize();

                            // Save meta information.
                            c = Container(Container::UNDEFINEDDATA, ms);

                            copied = true;
                        }
                    // Unlock shared memory segment.
                    memory->unlock();
                }

                if (copied) {
                    // Enter memory segment to processing queue.
                    m_bufferOut.enter(c);                
                }
            }

            return copied;
        }

        void SharedDataListener::add(const Container &container) {
            bool hasCopied = false;

            if (container.getDataType() == Container::SHARED_DATA) {
                SharedData sd = const_cast<Container&>(container).getData<SharedData>();

                map<string, core::data::SharedData>::iterator it = m_mapOfAvailableSharedData.find(sd.getName());
                if (it == m_mapOfAvailableSharedData.end()) {
            		m_mapOfAvailableSharedData[sd.getName()] = sd;

                    cout << "Connecting to shared memory " << sd.getName() << " at ";
                    
                    SharedPointer<core::wrapper::SharedMemory> sp = core::wrapper::SharedMemoryFactory::attachToSharedMemory(sd.getName());
                    m_sharedPointers[sd.getName()] = sp;

                    cout << sp->getSharedMemory() << " ";

                    cout << "done." << endl;
                }
                hasCopied = copySharedMemoryToMemorySegment(sd.getName(), container);
            }

            if (container.getDataType() == Container::SHARED_IMAGE) {
                SharedImage si = const_cast<Container&>(container).getData<SharedImage>();

                map<string, core::data::image::SharedImage>::iterator it = m_mapOfAvailableSharedImages.find(si.getName());
                if (it == m_mapOfAvailableSharedImages.end()) {
            		m_mapOfAvailableSharedImages[si.getName()] = si;

                    cout << "Connecting to shared image " << si.getName() << " at ";

                    SharedPointer<core::wrapper::SharedMemory> sp = core::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
                    m_sharedPointers[si.getName()] = sp;

                    cout << sp->getSharedMemory() << " ";

                    cout << "done." << endl;
                }
                hasCopied = copySharedMemoryToMemorySegment(si.getName(), container);
            }

            m_droppedSharedMemories = m_droppedSharedMemories + (!hasCopied ? 1 : 0);

            // If we are not running in threading mode, we need to trigger the disk dump manually.
            if ( (m_sharedDataWriter != NULL) && (!m_threading) ) {
                m_sharedDataWriter->recordEntries();
            }

            cout << "IN: " << m_bufferIn.getSize() << ", " << "OUT: " << m_bufferOut.getSize() << ", " << "DROPPED: " << m_droppedSharedMemories << endl;
        }

        void SharedDataListener::clear() {}

        uint32_t SharedDataListener::getSize() const {
            return m_bufferIn.getSize();
        }

        bool SharedDataListener::isEmpty() const {
            return (getSize() == 0);
        }

    } // recorder
} // tools


/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/TCPConnection.h"

namespace core {
    namespace wrapper {

        TCPConnection::TCPConnection() :
            m_connectionListenerMutex(),
            m_connectionListener(NULL),
            m_stringListenerMutex(),
            m_stringListener(NULL),
            m_partialData()
        {

            m_connectionListenerMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_connectionListenerMutex.get() == NULL) {
                throw std::string("(TCPConnection) Error creating mutex for connection listener.");
            }

            m_stringListenerMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_stringListenerMutex.get() == NULL) {
                throw std::string("(TCPConnection) Error creating mutex for string listener.");
            }
        }

        TCPConnection::~TCPConnection()
        {
            setStringListener(NULL);
            setConnectionListener(NULL);
        }

        void TCPConnection::setConnectionListener(ConnectionListener* listener) {
            m_connectionListenerMutex->lock();
                m_connectionListener = listener;
            m_connectionListenerMutex->unlock();
        }

        void TCPConnection::invokeConnectionListener() {
            m_connectionListenerMutex->lock();
                if (m_connectionListener != NULL) {
                    m_connectionListener->handleConnectionError();
                }
            m_connectionListenerMutex->unlock();
        }

        void TCPConnection::setStringListener(StringListener *listener) {
            m_stringListenerMutex->lock();
                m_stringListener = listener;
            m_stringListenerMutex->unlock();
        }

        void TCPConnection::invokeStringListener(const string& data)
        {
            m_stringListenerMutex->lock();
                if (m_stringListener != NULL) {
                    m_stringListener->nextString(data);
                }
            m_stringListenerMutex->unlock();
        }

        void TCPConnection::send(const string& data) {
            const uint32_t dataSize = htonl(data.length());
            stringstream dataStream;
            dataStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32_t));
            dataStream << data;

            sendImplementation(dataStream.str());
        }

        void TCPConnection::receivedString(const string &s)
        {
            m_partialData.write(s.c_str(), s.length());

            if ( hasCompleteData() ) {
                m_partialData.seekg(0, ios_base::beg);

                uint32_t dataSize = 0;
                m_partialData.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32_t));
                dataSize = ntohl(dataSize);
                const uint32_t bytesToIgnore = m_partialData.gcount();

                // Split the stringstreams's string into to pieces. The first
                // piece contains the data for the StringListener, the second
                // piece will remain in the stringstream.
                invokeStringListener(m_partialData.str().substr(bytesToIgnore, dataSize));
                m_partialData.str(m_partialData.str().substr(bytesToIgnore+dataSize));

                // After using str() to set the remaining string, the write pointer
                // points to the beginning of the stream and further receivedString() calls
                // would override existing data. So the write pointer as to point to the
                // end of the stream.
                m_partialData.seekp(0, ios_base::end);
            }
        }

        bool TCPConnection::hasCompleteData()
        {
            // Get size of stringstream
            m_partialData.seekg(0, ios_base::end);
            const uint32_t streamSize = m_partialData.tellg();
            m_partialData.seekg(0, ios_base::beg);

            // Read size of transfered data
            uint32_t dataSize = 0;
            m_partialData.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32_t));
            dataSize = ntohl(dataSize);
            const uint32_t bytesToIgnore = m_partialData.gcount();

            if ( streamSize >= dataSize + bytesToIgnore) {
                return true;
            }

            return false;
        }
    }
}

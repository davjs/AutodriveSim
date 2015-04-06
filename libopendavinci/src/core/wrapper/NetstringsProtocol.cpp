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
#include "core/wrapper/NetstringsProtocol.h"

namespace core {
    namespace wrapper {

        NetstringsProtocol::NetstringsProtocol() :
            AbstractProtocol(),
            m_stringListenerMutex(),
            m_stringListener(NULL),
            m_partialData()
        {
            m_stringListenerMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_stringListenerMutex.get() == NULL) {
                throw std::string("(NetstringsProtocol) Error creating mutex for string listener.");
            }
        }

        NetstringsProtocol::~NetstringsProtocol() {
            setStringListener(NULL);
        }

        void NetstringsProtocol::setStringListener(StringListener* listener) {
            m_stringListenerMutex->lock();
                m_stringListener = listener;
            m_stringListenerMutex->unlock();
        }

        void NetstringsProtocol::send(const string& data) {
            if (data.length() > 0) {
                stringstream netstring;

                netstring << (int)data.length() << ":" << data << ",";

                sendByStringSender(netstring.str());
            }
        }

        void NetstringsProtocol::receivedPartialString(const string &s) {
            m_partialData.write(s.c_str(), s.length());

            decodeNetstring();

            // After using str() to set the remaining string, the write pointer
            // points to the beginning of the stream and further receivedString() calls
            // would override existing data. So the write pointer has to point to the
            // end of the stream.
            m_partialData.seekp(0, ios_base::end);
        }

        void NetstringsProtocol::decodeNetstring(void) {
            // Netstrings have the following format:
            // ASCII Number representing the length of the payload + ':' + payload + ','

            m_partialData.seekg(0, ios_base::beg);

            // Start decoding only if we have received enough data.
            while(m_partialData.str().length() > 3) {
                unsigned int lengthOld = m_partialData.str().length();
                // On WIN32, the .str() returns a temporary object that is destroyed after the expression.
                // The reference keeps its existence instead.
                const string &m_partialDataString = m_partialData.str();
                const char *receiveBuffer = m_partialDataString.c_str();
                char *colonSign = NULL;
                unsigned int lengthOfPayload = strtol(receiveBuffer, &colonSign, 10);
                if (lengthOfPayload == 0) {
                    // Remove empty Netstring: 0:, (size is 3).

                    m_partialData.str(m_partialData.str().substr(3));
                    continue; // Try to decode next Netstring if any.
                }

                if (lengthOfPayload > lengthOld) {
                    // Incomplete Netstring received. Wait for more data.
                    break;
                }

                if (*colonSign == 0x3a) {
                    // Found colon sign. Now, check if (receiveBuffer + 1 + lengthOfPayload) == ','.
                    if ((colonSign[1 + lengthOfPayload]) == 0x2c) {
                        // Successfully found a complete Netstring.
                        string receivedPayload = m_partialData.str().substr((colonSign + 1) - receiveBuffer, lengthOfPayload);

                        invokeStringListener(receivedPayload);

                        // Remove decoded Netstring: "<lengthOfPayload> : <payload> ,"
                        int lengthOfNetstring = (colonSign + 1 + lengthOfPayload + 1) - receiveBuffer;

                        m_partialData.str(m_partialData.str().substr(lengthOfNetstring));
                    }
                }

                if (lengthOld == m_partialData.str().length()) {
                    // This should not happen, received data might be corrupted.

                    // Reset buffer.
                    m_partialData.str("");
                }
            }    
        }

        void NetstringsProtocol::invokeStringListener(const string& data) {
            m_stringListenerMutex->lock();
                if (m_stringListener != NULL) {
                    m_stringListener->nextString(data);
                }
            m_stringListenerMutex->unlock();
        }

    }
}


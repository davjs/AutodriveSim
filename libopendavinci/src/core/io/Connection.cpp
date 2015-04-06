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

#include "core/base/Lock.h"
#include "core/exceptions/Exceptions.h"
#include "core/io/Connection.h"
#include "core/wrapper/TCPFactory.h"

namespace core {
    namespace io {

        using namespace std;

        Connection::Connection(const std::string& ip, const uint32_t port)
                : m_listener(NULL),
                m_listenerMutex(),
                m_connection(NULL),
                m_errorHandler(NULL),
                m_errorHandlerMutex(),
                m_connected(false),
                m_connectedMutex() {
            try {
                m_connection = wrapper::TCPFactory::createTCPConnectionTo(ip, port);
            } catch (string& s) {
                OPENDAVINCI_CORE_THROW_EXCEPTION(ConnectException, s);
            }

            m_connection->setStringListener(this);
            m_connection->setConnectionListener(this);
        }

        Connection::Connection(wrapper::TCPConnection* connection)
                : m_listener(NULL),
                m_listenerMutex(),
                m_connection(connection),
                m_errorHandler(NULL),
                m_errorHandlerMutex(),
                m_connected(false),
                m_connectedMutex() {
            m_connection->setStringListener(this);
            m_connection->setConnectionListener(this);
        }

        Connection::~Connection() {
            m_connection->setConnectionListener(NULL);
            m_connection->setStringListener(NULL);
            m_connection->stop();

            {
                core::base::Lock l(m_connectedMutex);
                m_connected = false;
            }

            OPENDAVINCI_CORE_DELETE_POINTER(m_connection);
        }

        bool Connection::isConnected() {
            core::base::Lock l(m_connectedMutex);
            return m_connected;
        }

        void Connection::send(core::data::Container& container) {
            container.setSentTimeStamp(core::data::TimeStamp());

            stringstream stringstreamValue;
            stringstreamValue << container;
            m_connection->send(stringstreamValue.str());
        }

        void Connection::nextString(const string &s) {
            core::base::Lock l(m_listenerMutex);

            if ( m_listener != NULL ) {
                stringstream stringstreamData(s);
                core::data::Container container;
                stringstreamData >> container;
                container.setReceivedTimeStamp(core::data::TimeStamp());

                // Inform the registered container listener about the new data.
                m_listener->nextContainer(container);
            }
        }

        void Connection::handleConnectionError() {
            {
                core::base::Lock l(m_errorHandlerMutex);

                if (m_errorHandler != NULL ) {
                    m_errorHandler->handleConnectionError();
                }
            }

            {
                core::base::Lock l(m_connectedMutex);
                m_connected = false;
            }
        }

        void Connection::setErrorListener(ConnectionErrorListener* el) {
            core::base::Lock l(m_errorHandlerMutex);
            m_errorHandler = el;
        }

        void Connection::setContainerListener(ContainerListener *cl) {
            core::base::Lock l(m_listenerMutex);
            m_listener = cl;
        }

        void Connection::start() {
            m_connection->start();

            {
                core::base::Lock l(m_connectedMutex);
                m_connected = true;
            }
        }

        void Connection::stop() {
            m_connection->stop();

            {
                core::base::Lock l(m_connectedMutex);
                m_connected = false;
            }
        }
    }
}

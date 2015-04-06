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

#ifndef MOCKS__TCPACCEPTORLISTENERMOCK_H
#define MOCKS__TCPACCEPTORLISTENERMOCK_H

#include "FunctionCallWaiter.h"

#include "core/wrapper/TCPAcceptorListener.h"
#include "core/wrapper/TCPConnection.h"

namespace mocks {
    class TCPAcceptorListenerMock : public core::wrapper::TCPAcceptorListener {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             */
            TCPAcceptorListenerMock(const TCPAcceptorListenerMock& );

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             */
            TCPAcceptorListenerMock& operator=(const TCPAcceptorListenerMock&);

            core::wrapper::TCPConnection* m_connection;

        public:
            TCPAcceptorListenerMock() :
                m_connection(NULL),
                CALLWAITER_onNewConnection()
            {};

            ~TCPAcceptorListenerMock() {
                if (m_connection) {
                    delete m_connection;
                }
            };

            core::wrapper::TCPConnection* getConnection() {
                return m_connection;
            }

            void dontDeleteConnection() {
                m_connection = NULL;
            }

             virtual void onNewConnection(core::wrapper::TCPConnection* connection) {
                m_connection = connection;
                CALLWAITER_onNewConnection.called();
            }

            FunctionCallWaiter CALLWAITER_onNewConnection;
    };
}
#endif

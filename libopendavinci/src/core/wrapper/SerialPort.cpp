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
#include "core/wrapper/SerialPort.h"

namespace core {
    namespace wrapper {

        SerialPortSettings::SerialPortSettings() :
            m_parity(SP_PARITY_NONE),
            m_dataBits(SP_DATA_8),
            m_stopBits(SP_STOP_1) {}

        SerialPort::SerialPort() :
            m_settings(),
            m_connectionListenerMutex(),
            m_connectionListener(NULL),
            m_partialStringReceiverMutex(),
            m_partialStringReceiver(NULL)
        {
            m_connectionListenerMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_connectionListenerMutex.get() == NULL) {
                throw std::string("(SerialPort) Error creating mutex for connection listener.");
            }

            m_partialStringReceiverMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_partialStringReceiverMutex.get() == NULL) {
                throw std::string("(SerialPort) Error creating mutex for partial string receiver.");
            }
        }

        SerialPort::~SerialPort() {
            setConnectionListener(NULL);
            setPartialStringReceiver(NULL);
        }

        void SerialPort::setSettings(const SerialPortSettings &settings) {
            m_settings = settings;
        }

        const SerialPortSettings SerialPort::getSettings() const {
            return m_settings;
        }

        void SerialPort::setConnectionListener(ConnectionListener* listener) {
            m_connectionListenerMutex->lock();
                m_connectionListener = listener;
            m_connectionListenerMutex->unlock();
        }

        void SerialPort::setPartialStringReceiver(PartialStringReceiver* psr) {
            m_partialStringReceiverMutex->lock();
                m_partialStringReceiver = psr;
            m_partialStringReceiverMutex->unlock();
        }

        void SerialPort::send(const string& data) {
            sendImplementation(data);
        }

        void SerialPort::receivedString(const string &s)
        {
            m_partialStringReceiverMutex->lock();
                if (m_partialStringReceiver != NULL) {
                    m_partialStringReceiver->receivedPartialString(s);
                }
            m_partialStringReceiverMutex->unlock();
        }

         void SerialPort::invokeConnectionListener() {
            m_connectionListenerMutex->lock();
                if (m_connectionListener != NULL) {
                    m_connectionListener->handleConnectionError();
                }
            m_connectionListenerMutex->unlock();
        }

   }
}

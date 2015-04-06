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

#ifndef OPENDAVINCI_CORE_WRAPPER_SERIALPORT_H_
#define OPENDAVINCI_CORE_WRAPPER_SERIALPORT_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/wrapper/ConnectionObserver.h"
#include "core/wrapper/Mutex.h"
#include "core/wrapper/PartialStringReceiver.h"
#include "core/wrapper/StringSender.h"

namespace core {
    namespace wrapper {

        using namespace std;

        class OPENDAVINCI_API SerialPortSettings {
            public:
                enum SerialPortParity {
                    SP_PARITY_NONE = 0, 
                    SP_PARITY_EVEN, 
                    SP_PARITY_ODD
                };

                enum SerialPortDataBits {
                    SP_DATA_5 = 5,
                    SP_DATA_6,
                    SP_DATA_7,
                    SP_DATA_8
                };

                enum SerialPortStopBits {
                    SP_STOP_1 = 1,
                    SP_STOP_2
                };

                SerialPortSettings();

                SerialPortParity m_parity;
                SerialPortDataBits m_dataBits;
                SerialPortStopBits m_stopBits;
        };

        class OPENDAVINCI_API SerialPort : public StringSender, public ConnectionObserver {
            protected:
                /**
                 * Protected constructor for enforcing subclasses for this class.
                 */
                SerialPort();

            public:
                virtual ~SerialPort();

                /**
                 * This method registers a ConnectionListener that will be
                 * informed about connection errors.
                 *
                 * @param cl The ConnectionListener
                 */
                void setConnectionListener(ConnectionListener* cl);

                /**
                 * This method sets the PartialStringReceiver that will realize the protocol.
                 *
                 * @param psr PartialStringReceiver that will receive incoming data.
                 */
                void setPartialStringReceiver(PartialStringReceiver* psr);

                /**
                 * This method must be called to start the connection.
                 */
                virtual void start() = 0;

                /**
                 * This method closes a connection.
                 */
                virtual void stop() = 0;

                virtual void send(const string &data);

            protected:
                /**
                 * This method has to be implemented in subclasses
                 * to send data. It is called from within the send()-
                 * method.
                 *
                 * param data Data with prepended size information.
                 */
                virtual void sendImplementation(const string& data) = 0;

                /**
                 * This method has to be called by subclasses whenever
                 * new (partial) data was received. This method is
                 * responsible for gathering partial data and invoking
                 * the registered StringListener when a complete data
                 * packet was gathered.
                 *
                 * @param partialData Partially received data that will
                 *                    be gathered until the complete
                 *                    data can be passed to the registered
                 *                    StringListener.
                 */
                void receivedString(const string &partialData);

                /**
                 * This method is called by subclasses to invoke
                 * the connection listener.
                 */
                void invokeConnectionListener();

                /**
                 * This method sets the serial port settings.
                 *
                 * @param settings
                 */
                void setSettings(const SerialPortSettings &settings);

                /**
                 * This method returns the serial port settings.
                 *
                 * @return settings
                 */
                const SerialPortSettings getSettings() const;

            private:
                SerialPortSettings m_settings;

                std::auto_ptr<Mutex> m_connectionListenerMutex;
                ConnectionListener* m_connectionListener;

                std::auto_ptr<Mutex> m_partialStringReceiverMutex;
                PartialStringReceiver *m_partialStringReceiver;

                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                SerialPort(const SerialPort &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                SerialPort& operator=(const SerialPort &);
        };
    }
}

#endif /* OPENDAVINCI_CORE_WRAPPER_SERIALPORT_H_ */

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

#ifndef OPENDAVINCI_CORE_WRAPPER_POSIXSERIALPORTCONNECTION_H_
#define OPENDAVINCI_CORE_WRAPPER_POSIXSERIALPORTCONNECTION_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/wrapper/Runnable.h"
#include "core/wrapper/SerialPort.h"
#include "core/wrapper/Thread.h"
#include "core/wrapper/Mutex.h"

namespace core {
    namespace wrapper {
        namespace POSIX {

            class POSIXSerialPort : public SerialPort, public Runnable {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    POSIXSerialPort(const POSIXSerialPort &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    POSIXSerialPort& operator=(const POSIXSerialPort &);

                public:
                    POSIXSerialPort(const std::string &port, const uint32_t &baudRate, const SerialPortSettings &settings = SerialPortSettings());

                    virtual ~POSIXSerialPort();

                    virtual void sendImplementation(const std::string& data);

                    virtual void start();
                    virtual void stop();

                    virtual bool isRunning();
                    virtual void run();

                protected:
                    void initialize();

                    bool openPort(const std::string &port, const uint32_t &baudRate, const SerialPortSettings &settings);
                    void closePort();
                    bool isOpen();
                    bool setBaudrate(const uint32_t &baudRate);
                    bool setDataBits(const SerialPortSettings::SerialPortDataBits &dataBits);
                    bool setStopBits(const SerialPortSettings::SerialPortStopBits &stopBits);
                    bool setParity(const SerialPortSettings::SerialPortParity &parity);


                    std::auto_ptr<Thread> m_thread;

                    std::auto_ptr<Mutex> m_socketMutex;
                    int32_t m_fileDescriptor;

                    enum { BUFFER_SIZE = 2048 };
                    char m_buffer[BUFFER_SIZE];
                    std::string m_port;
                    uint32_t m_baudRate;

                    bool m_open;
            };
        }
    }
}
#endif /* OPENDAVINCI_CORE_WRAPPER_POSIXSERIALPORTCONNECTION_H_ */

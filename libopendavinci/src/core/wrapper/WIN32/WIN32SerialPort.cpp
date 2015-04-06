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

#ifdef __linux__

#include <termios.h> // POSIX terminal control definitions
#include <linux/serial.h>
#include <sys/ioctl.h>

#include "core/wrapper/ConcurrencyFactory.h"
#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/POSIX/POSIXSerialPort.h"

namespace core {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            POSIXSerialPort::POSIXSerialPort(const std::string &port, const uint32_t &baudRate, const SerialPortSettings &settings) :
                    m_thread(),
                    m_socketMutex(),
                    m_fileDescriptor(-1),
                    m_buffer(),
                    m_port(port),
                    m_baudRate(baudRate),
                    m_open(false) {
                setSettings(settings);
                initialize();
                openPort(m_port, m_baudRate, getSettings());
            }

            POSIXSerialPort::~POSIXSerialPort() {
                stop();
                closePort();
            }

            void POSIXSerialPort::start() {
                m_thread->start();
            }

            void POSIXSerialPort::stop() {
                m_thread->stop();
            }

            bool POSIXSerialPort::isRunning() {
                return m_thread->isRunning();
            }

            bool POSIXSerialPort::openPort(const std::string &port, const uint32_t &baudRate, const SerialPortSettings &settings) {
                if (m_open) {
                    return m_open;
                }

                m_fileDescriptor = ::open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
                if (m_fileDescriptor == -1) {
                    stringstream s;
                    s << "Error while opening serial port " << port << " at " << __FILE__ << ": " << __LINE__;
                    throw s.str();
                }

                m_open = true;

                // Setup non-blocking reads.
                ::fcntl(m_fileDescriptor, F_SETFL, FNDELAY);

                struct termios options;
                if (tcgetattr(m_fileDescriptor, &options) != 0) {
                    stringstream s;
                    s << "Error while reading serial port option at " << __FILE__ << ": " << __LINE__;

                    closePort();

                    throw s.str();
                }

                // Enable the receiver and set local mode.
                options.c_cflag |= CREAD|CLOCAL;

                // Set to raw input.
                options.c_lflag &= ~(ICANON|ECHO|ECHOE|ECHOK|ECHONL|ISIG);

                // Disable flow control.
                options.c_cflag &= ~CRTSCTS;
                options.c_iflag &= ~(IXON|IXOFF|IXANY);

                // Setup misc stuff.
                options.c_iflag &= (~(INPCK|IGNPAR|PARMRK|ISTRIP|ICRNL|IXANY));
                options.c_oflag &= (~OPOST);
                options.c_cc[VMIN] = 0;

                #ifdef _POSIX_VDISABLE
                    // Some systems allow for per-device disable-characters, so get the proper value for the configured device.
                    const long vdisable = ::fpathconf(m_fileDescriptor, _PC_VDISABLE);
                    options.c_cc[VINTR] = vdisable;
                    options.c_cc[VQUIT] = vdisable;
                    options.c_cc[VSTART] = vdisable;
                    options.c_cc[VSTOP] = vdisable;
                    options.c_cc[VSUSP] = vdisable;
                #endif

                // Apply the new options for the port.
                if (tcsetattr(m_fileDescriptor, TCSANOW, &options) != 0) {
                    stringstream s;
                    s << "Error while applying serial port options at " << __FILE__ << ": " << __LINE__;

                    closePort();

                    throw s.str();
                }

                if (!setDataBits(settings.m_dataBits)) {
                    stringstream s;
                    s << "Error while applying serial port options at " << __FILE__ << ": " << __LINE__;

                    closePort();

                    throw s.str();
                }

                if (!setStopBits(settings.m_stopBits)) {
                    stringstream s;
                    s << "Error while applying serial port options at " << __FILE__ << ": " << __LINE__;

                    closePort();

                    throw s.str();
                }

                if (!setParity(settings.m_parity)) {
                    stringstream s;
                    s << "Error while applying serial port options at " << __FILE__ << ": " << __LINE__;

                    closePort();

                    throw s.str();
                }

                // Change baud rate only if we are not using pseudo terminals.
                size_t isPTS = port.find_first_of("/dev/pts");

                // Skip lines containing no key-value-pairs.
                if (isPTS == string::npos) {
                    if (!setBaudrate(baudRate)) {
                        stringstream s;
                        s << "Error while applying serial port options at " << __FILE__ << ": " << __LINE__;

                        closePort();

                        throw s.str();
                    }
                }

                return (m_open = true);
            }

            void POSIXSerialPort::closePort() {
                if (m_open) {
                    struct termios options;
                    tcgetattr(m_fileDescriptor, &options);
                    options.c_cc[VTIME] = 1;
                    options.c_cc[VMIN] = 0;
                    tcsetattr(m_fileDescriptor, TCSANOW, &options);

                    ::close(m_fileDescriptor);
                }
                m_open = false;
            }

            bool POSIXSerialPort::isOpen() {
                return m_open;
            }

            bool POSIXSerialPort::setBaudrate(const uint32_t &baudRate) {
                if (!m_open) {
                    return false;
                }

                speed_t baud = 0;
                switch (baudRate) {
                    case      50: baud =      B50; break;
                    case      75: baud =      B75; break;
                    case     110: baud =     B110; break;
                    case     134: baud =     B134; break;
                    case     150: baud =     B150; break;
                    case     200: baud =     B200; break;
                    case     300: baud =     B300; break;
                    case     600: baud =     B600; break;
                    case    1200: baud =    B1200; break;
                    case    1800: baud =    B1800; break;
                    case    2400: baud =    B2400; break;
                    case    4800: baud =    B4800; break;
                    case    9600: baud =    B9600; break;
                    case   19200: baud =   B19200; break;
                    case   38400: baud =   B38400; break;
                    case   57600: baud =   B57600; break;
                    case  115200: baud =  B115200; break;
                    case  230400: baud =  B230400; break;
                    case  460800: baud =  B460800; break;
                    case  500000: baud =  B500000; break;
                    case  576000: baud =  B576000; break;
                    case  921600: baud =  B921600; break;
                    case 1000000: baud = B1000000; break;
                    case 1152000: baud = B1152000; break;
                    case 1500000: baud = B1500000; break;
                    case 2000000: baud = B2000000; break;
                    case 2500000: baud = B2500000; break;
                    case 3000000: baud = B3000000; break;
                    case 3500000: baud = B3500000; break;
                    case 4000000: baud = B4000000; break;
                    default:      baud = 0; break;
                }

                struct termios options;
                if (tcgetattr(m_fileDescriptor, &options) != 0) {
                    return false;
                }

                serial_struct ser_info;

                // Default is 38400.
                if (baud == 0) {
                    if (::ioctl(m_fileDescriptor, TIOCGSERIAL, &ser_info) != 0) {
                        return false;
                    }

                    ser_info.flags &= ~ASYNC_SPD_MASK;
                    ser_info.flags |= ASYNC_SPD_CUST | ASYNC_LOW_LATENCY;
                    ser_info.custom_divisor = ser_info.baud_base / baudRate;

                    cfsetspeed(&options, B38400);
                    if (tcsetattr(m_fileDescriptor, TCSANOW, &options) != 0) {
                        return false;
                    }

                    if (::ioctl(m_fileDescriptor, TIOCSSERIAL, &ser_info) != 0) {
                        return false;
                    }
                }
                else {
                    cfsetspeed(&options, baud);
                    if (tcsetattr(m_fileDescriptor, TCSANOW, &options) != 0) {
                        return false;
                    }

                    if (::ioctl(m_fileDescriptor, TIOCGSERIAL, &ser_info) != 0) {
                        return false;
                    }
                    else {
                        ser_info.flags &= ~ASYNC_SPD_CUST;
                        ser_info.custom_divisor = 0;
                        if (ioctl(m_fileDescriptor, TIOCSSERIAL, &ser_info) != 0) {
                            return false;
                        }
                    }
                }

                return true;
            }

            bool POSIXSerialPort::setDataBits(const SerialPortSettings::SerialPortDataBits &dataBits) {
                if (!m_open) {
                    return false;
                }

                struct termios options;
                if (tcgetattr(m_fileDescriptor, &options) != 0) {
                    return false;
                }

                options.c_cflag &= ~CSIZE;

                switch (dataBits) {
                    case SerialPortSettings::SP_DATA_5:
                        options.c_cflag |= CS5;
                    break;

                    case SerialPortSettings::SP_DATA_6:
                        options.c_cflag |= CS6;
                    break;

                    case SerialPortSettings::SP_DATA_7:
                        options.c_cflag |= CS7;
                    break;

                    default:
                        options.c_cflag |= CS8;
                    break;
                }

                if (tcsetattr(m_fileDescriptor, TCSANOW, &options) != 0) {
                    return false;
                }

                SerialPortSettings settings = getSettings();
                settings.m_dataBits = dataBits;
                setSettings(settings);

                return true;
            }

            bool POSIXSerialPort::setStopBits(const SerialPortSettings::SerialPortStopBits &stopBits) {
                if (!m_open) {
                    return false;
                }

                struct termios options;
                if (tcgetattr(m_fileDescriptor, &options) != 0) {
                    return false;
                }

                switch (stopBits) {
                    case SerialPortSettings::SP_STOP_2:
                        options.c_cflag |= CSTOPB;
                    break;

                    default:
                        options.c_cflag &= ~CSTOPB;
                    break;
                }

                if (tcsetattr(m_fileDescriptor, TCSANOW, &options) != 0) {
                    return false;
                }

                SerialPortSettings settings = getSettings();
                settings.m_stopBits = stopBits;
                setSettings(settings);

                return true;
            }

            bool POSIXSerialPort::setParity(const SerialPortSettings::SerialPortParity &parity) {
                if (!m_open) {
                    return false;
                }

                struct termios options;
                if (tcgetattr(m_fileDescriptor, &options) != 0) {
                    return false;
                }

                switch (parity) {
                    case SerialPortSettings::SP_PARITY_EVEN:
                        options.c_cflag |= PARENB;
                        options.c_cflag &= ~PARODD;
                    break;

                    case SerialPortSettings::SP_PARITY_ODD:
                        options.c_cflag |= PARENB;
                        options.c_cflag |= PARODD;
                    break;

                    default:
                        options.c_cflag &= ~PARENB;
                    break;
                }

                if (tcsetattr(m_fileDescriptor, TCSANOW, &options) != 0) {
                    return false;
                }

                SerialPortSettings settings = getSettings();
                settings.m_parity = parity;
                setSettings(settings);

                return true;
            }

            void POSIXSerialPort::run() {
                fd_set rfds;
                struct timeval timeout;
                bool ready = true;

                while ( isRunning() && ready ) {
                    timeout.tv_sec = 0;
                    timeout.tv_usec = 10000;

                    FD_ZERO(&rfds);
                    FD_SET(m_fileDescriptor, &rfds);

                    select(m_fileDescriptor + 1, &rfds, NULL, NULL, &timeout);

                    if (FD_ISSET(m_fileDescriptor, &rfds)) {
                        int32_t numBytes = ::read(m_fileDescriptor, m_buffer, BUFFER_SIZE);

                        if (numBytes > 0) {
                            // Get data.
                            string stringData(m_buffer, numBytes);

                            // Process data in higher layers.
                            receivedString(stringData);
                        } else if (numBytes <= 0) {
                            // Handle error: numBytes == 0 if peer shut down, numBytes < 0 in any case of error.
                            invokeConnectionListener();
                            ready = false;
                        }
                    }
                }
            }

            void POSIXSerialPort::sendImplementation(const std::string &data) {
                m_socketMutex->lock();
                int32_t numBytes = ::write(m_fileDescriptor, data.c_str(), data.length());

                if (numBytes == -1) {
                    // Handle error.
                    invokeConnectionListener();
                }
                m_socketMutex->unlock();
            }


            void POSIXSerialPort::initialize() {
                m_thread = auto_ptr<Thread>(ConcurrencyFactory::createThread(*this));
                if (m_thread.get() == NULL) {
                    throw std::string("[PosixSerialPort] Error creating thread");
                }

                m_socketMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
                if (m_socketMutex.get() == NULL) {
                    throw std::string("[PosixSerialPort] Error creating mutex for socket");
                }
            }
        }
    }
}

#endif /* __linux__ */

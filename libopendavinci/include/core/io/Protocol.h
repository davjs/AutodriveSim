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

#ifndef OPENDAVINCI_CORE_IO_PROTOCOL_H_
#define OPENDAVINCI_CORE_IO_PROTOCOL_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

namespace core {
    namespace io {

        using namespace std;

        /**
         * This class provides a protocol parser.
         *
         * @code
         * void foo() {
         *     Protocol::PROTOCOL p = Protocol::getProtocol("file://myFile");
         *     ...
         * }
         * @endcode
         */
        class Protocol {
            public:
                enum PROTOCOL {
                    UNKNOWNPROTOCOL,
                    FILEPROTOCOL
                };

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                Protocol(const Protocol &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                Protocol& operator=(const Protocol &);

            private:
                Protocol();

            public:
                virtual ~Protocol();

                /**
                 * This method tries to extract the connection type by parsing
                 * the protocol type.
                 *
                 * @param connection The connection string to be parsed. The type of protocol is removed from the string.
                 * @return Connection type.
                 */
                static PROTOCOL getProtocol(string &connection);
        };

    }
} // core::io

#endif /*OPENDAVINCI_CORE_IO_PROTOCOL_H_*/

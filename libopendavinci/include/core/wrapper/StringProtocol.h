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

#ifndef OPENDAVINCI_CORE_WRAPPER_STRINGPROTOCOL_H_
#define OPENDAVINCI_CORE_WRAPPER_STRINGPROTOCOL_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include <sstream>

#include "core/wrapper/Mutex.h"
#include "core/wrapper/AbstractProtocol.h"
#include "core/wrapper/StringObserver.h"
#include "core/wrapper/StringSender.h"

namespace core {
    namespace wrapper {

        using namespace std;

        class OPENDAVINCI_API StringProtocol : public StringObserver, public AbstractProtocol {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                StringProtocol(const StringProtocol &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                StringProtocol& operator=(const StringProtocol &);

            public:
                /**
                 * Constructor.
                 */
                StringProtocol();

                virtual ~StringProtocol();

                /**
                 * This method sends the data in the following format:
                 *
                 * size data
                 *
                 * Size: htonl((uint32_t) data.length())
                 *
                 * @param data Data to be sent.
                 */
                void send(const string& data);

                /**
                 * This method sets the StringListener that will receive
                 * incoming data.
                 *
                 * @param listener StringListener that will receive incoming data.
                 */
                void setStringListener(StringListener* listener);

                virtual void receivedPartialString(const string &partialData);

            private:
                bool hasCompleteData();

                /**
                 * This method is used to pass received data thread-safe
                 * to the registered StringListener.
                 */
                void invokeStringListener(const string& data);

                std::auto_ptr<Mutex> m_stringListenerMutex;
                StringListener *m_stringListener;

                stringstream m_partialData;
        };
    }
}

#endif /* OPENDAVINCI_CORE_WRAPPER_STRINGPROTOCOL_H_ */


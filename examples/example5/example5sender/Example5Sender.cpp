/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "core/io/ContainerConference.h"
#include "core/wrapper/SerialPortFactory.h"
#include "core/wrapper/SerialPort.h"
#include "core/wrapper/StringProtocol.h"

#include "Example5Sender.h"

namespace examples {

    using namespace std;
    using namespace core::base;

    Example5Sender::Example5Sender(const int32_t &argc, char **argv) :
            ConferenceClientModule(argc, argv, "Example5Sender")
    		{}

    Example5Sender::~Example5Sender() {}

    void Example5Sender::setUp() {}

    void Example5Sender::tearDown() {}

    void Example5Sender::handleConnectionError() {
        cout << "Example5Sender: connection error.'" << endl;
    }

    void Example5Sender::nextString(const string &s) {
        cout << "Example5Sender: '" << s << "'" << endl;
    }

    ModuleState::MODULE_EXITCODE Example5Sender::body() {
        // Create SerialPort.
        core::wrapper::SerialPort *serialPort = core::wrapper::SerialPortFactory::createSerialPort("/dev/pts/2", 115200);
        serialPort->setConnectionListener(this);

        core::wrapper::StringProtocol sp;
        sp.setStringListener(this); // Example5Sender shall receive completely received strings from the StringProtocol.
        sp.setStringSender(serialPort); // The StringProtocol will use the SerialPort to send data.
        serialPort->setPartialStringReceiver(&sp); // The SerialPort will distribute partially received data to StringProtocol.

        // Start receiving.
        serialPort->start();

    	uint32_t counter = 0;

    	while (getModuleState() == ModuleState::RUNNING) {
    		// Create user data.
            stringstream data;

            data << "Example5Sender: " << counter++;

            sp.send(data.str());

    		// Restrict counter.
    		if (counter > 1000) counter = 0;
    	}

        // Destroy connections to UDP_Server.
        OPENDAVINCI_CORE_DELETE_POINTER(serialPort);

    	return ModuleState::OKAY;
    }

} // examples

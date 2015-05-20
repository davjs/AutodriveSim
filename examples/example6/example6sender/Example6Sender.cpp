/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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
#include "core/data/Container.h"

#include "Example6Sender.h"
#include "generated/examples/Example6Data.h"

namespace examples {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    Example6Sender::Example6Sender(const int32_t &argc, char **argv) :
        ConferenceClientModule(argc, argv, "Example6Sender")
		{}

    Example6Sender::~Example6Sender() {}

    void Example6Sender::setUp() {}

    void Example6Sender::tearDown() {}


    ModuleState::MODULE_EXITCODE Example6Sender::body() {
    	uint32_t counter = 0;

		Example6Data data;
    	while (getModuleState() == ModuleState::RUNNING) {
    		// Create user data.
    		data.setNumericalValue(counter);
    		data.setStringValue("Example6Sender");

            float f = (0.5f + (float)counter);
            cout << "Adding " << f << " to the list." << endl;
            data.addTo_ListOfValues(f);

    		// Create container with user data type ID 5.
    		Container c(Container::USER_DATA_5, data);

    		// Send container.
    		getConference().send(c);

            counter++;
    		// Restrict counter.
    		if (counter > 1000) counter = 0;
    	}

    	return ModuleState::OKAY;
    }

} // examples

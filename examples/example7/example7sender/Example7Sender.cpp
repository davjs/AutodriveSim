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

#include <cmath>

#include "core/base/Thread.h"
#include "core/io/ContainerConference.h"
#include "core/data/Container.h"

#include "Example7Sender.h"
#include "../Example7Data.h"

namespace examples {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    Example7Sender::Example7Sender(const int32_t &argc, char **argv) :
        ConferenceClientModule(argc, argv, "Example7Sender")
		{}

    Example7Sender::~Example7Sender() {}

    void Example7Sender::setUp() {}

    void Example7Sender::tearDown() {}


    ModuleState::MODULE_EXITCODE Example7Sender::body() {
        uint32_t seed = 24;
    	uint32_t counter = 0;

        srand(seed);

    	while (getModuleState() == ModuleState::RUNNING) {
    		// Create user data.
    		Example7Data data;
    		data.setNumericalValue(counter++);
    		data.setStringValue("Example7Sender");

    		// Create container with user data type ID 5.
    		Container c(Container::USER_DATA_5, data);

    		// Send container.
    		getConference().send(c);

    		// Restrict counter.
    		if (counter > 1000) counter = 0;

            // Provoke unexpected delays to demonstrate the need for --pulse in supercomponent.
            double r = ((rand() / (double)RAND_MAX)) * 1000 * 1100;
            cerr << "Sleep for " << r << " ms." << endl;
            Thread::usleep((long)r);
        }

    	return ModuleState::OKAY;
    }

} // examples

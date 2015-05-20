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

#include <iostream>

#include "core/data/Container.h"
#include "core/io/ContainerConference.h"

#include "Example7Receiver.h"
#include "../Example7Data.h"

namespace examples {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    Example7Receiver::Example7Receiver(const int32_t &argc, char **argv) :
        ConferenceClientModule(argc, argv, "Example7Receiver")
		{}

    Example7Receiver::~Example7Receiver() {}

    void Example7Receiver::setUp() {}

    void Example7Receiver::tearDown() {}

    ModuleState::MODULE_EXITCODE Example7Receiver::body() {
        uint32_t sum = 0;
        uint32_t expected_sum = 0;
        uint32_t counter = 0;

    	while (getModuleState() == ModuleState::RUNNING) {
			Container c = getKeyValueDataStore().get(Container::USER_DATA_5);
			Example7Data data = c.getData<Example7Data>();
            sum += data.getNumericalValue();
			cout << "Latest container from data type " << (uint32_t)c.getDataType() << ", content: " << data.toString() << ", sum = " << sum << endl;

            if (sum > 0) {
                counter++;
                expected_sum += counter;
                cout << "Diff: " << (expected_sum - sum) << endl;
            }
    	}

    	return ModuleState::OKAY;
    }

} // examples

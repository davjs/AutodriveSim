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

#include "Example6Receiver.h"
#include "generated/examples/Example6Data.h"

namespace examples {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    Example6Receiver::Example6Receiver(const int32_t &argc, char **argv) :
        ConferenceClientModule(argc, argv, "Example6Receiver"),
        m_fifo()
		{}

    Example6Receiver::~Example6Receiver() {}

    void Example6Receiver::setUp() {}

    void Example6Receiver::tearDown() {}

    ModuleState::MODULE_EXITCODE Example6Receiver::body() {
    	// Connect the FIFO data store with the ContainerConference to get
    	// notified for each exchanged Container of the type "USER_TYPE".
//    	addDataStoreFor(Container::USER_DATA_5, m_fifo);
    	addDataStoreFor(m_fifo);

    	while (getModuleState() == ModuleState::RUNNING) {
    		// Process received entries.
    		while (!m_fifo.isEmpty()) {
    			Container c = m_fifo.leave();

    			if (c.getDataType() == Container::USER_DATA_5) {
    				Example6Data data = c.getData<Example6Data>();
    				cout << "Received Container from data type " << (uint32_t)c.getDataType() << ", content: " << data.toString() << endl;

                    cout << "Is the list empty: " << data.isEmpty_ListOfValues() << endl;
                    cout << "Number of elements: " << data.getSize_ListOfValues() << endl;
                    cout << "Does the list contain the value 0.5: " << data.contains_ListOfValues(0.5) << endl;
                    cout << "Does the list contain the value -0.5: " << data.contains_ListOfValues(-0.5) << endl;
                    cout << "Printing elements: " << endl;
                    std::vector<float>::iterator it = data.iteratorBegin_ListOfValues();
                    std::vector<float>::iterator itEnd = data.iteratorEnd_ListOfValues();
                    while (it != itEnd) {
                        cout << *it++ << ", ";
                    }
                    cout << endl;
    			}

    		}
    	}

    	return ModuleState::OKAY;
    }

} // examples

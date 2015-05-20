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

#include <iostream>

#include "core/data/Container.h"
#include "core/io/ContainerConference.h"

#include "Example3Receiver.h"
#include "../Example3Data.h"

namespace examples {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    Example3Receiver::Example3Receiver(const int32_t &argc, char **argv) :
            ConferenceClientModule(argc, argv, "Example3Receiver"),
            m_fifo()
    		{}

    Example3Receiver::~Example3Receiver() {}

    void Example3Receiver::setUp() {}

    void Example3Receiver::tearDown() {}

    ModuleState::MODULE_EXITCODE Example3Receiver::body() {
    	// Connect the FIFO data store with the ContainerConference to get
    	// notified for each exchanged Container of the type "USER_TYPE".
//    	addDataStoreFor(Container::USER_DATA_0, m_fifo);
    	addDataStoreFor(m_fifo);

    	while (getModuleState() == ModuleState::RUNNING) {
    		// Process received entries.
    		while (!m_fifo.isEmpty()) {
    			Container c = m_fifo.leave();

    			if (c.getDataType() == Container::USER_DATA_5) {
    				Example3Data data = c.getData<Example3Data>();
    				cout << "Received Container from data type " << (uint32_t)c.getDataType() << ", content: " << data.toString() << endl;
    			}

    		}
    	}

    	return ModuleState::OKAY;
    }

} // examples

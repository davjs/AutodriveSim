/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include <iostream>

#include "core/data/Container.h"

#include "Spy.h"

namespace spy {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    Spy::Spy(const int32_t &argc, char **argv) :
        ConferenceClientModule(argc, argv, "Spy"),
        m_fifo() {}

    Spy::~Spy() {}

    void Spy::setUp() {}

    void Spy::tearDown() {}

    ModuleState::MODULE_EXITCODE Spy::body() {
        // Add FIFOQueue to spy all data.
        addDataStoreFor(m_fifo);

        while (getModuleState() == ModuleState::RUNNING) {
            while (!m_fifo.isEmpty()) {
                Container c = m_fifo.leave();
                
                cout << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << "-->" << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() << " dt = " << (c.getReceivedTimeStamp() - c.getSentTimeStamp()).toString() << " ID = " << c.getDataType() << ": " << c.toString() << endl; 
            }
        }

        return ModuleState::OKAY;
    }

} // spy

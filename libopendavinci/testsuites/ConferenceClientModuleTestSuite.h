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

#ifndef OPENDAVINCI_CONFERENCECLIENTMODULETESTSUITE_H_
#define OPENDAVINCI_CONFERENCECLIENTMODULETESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "core/base/Lock.h"
#include "core/base/Service.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/io/ContainerConference.h"
#include "core/io/ContainerConferenceFactory.h"
#include "core/io/StreamFactory.h"
#include "core/io/URL.h"

#include "core/base/ConferenceClientModule.h"
#include "core/data/recorder/RecorderCommand.h"
#include "core/dmcp/ModuleConfigurationProvider.h"
#include "core/dmcp/discoverer/Server.h"
#include "core/dmcp/connection/Server.h"
#include "core/dmcp/connection/ConnectionHandler.h"
#include "core/dmcp/connection/ModuleConnection.h"

using namespace std;
using namespace core::base;
using namespace core::data;
using namespace core::io;
using namespace core::data::dmcp;
using namespace core::dmcp;


class ConferenceClientModuleTestModule : public ConferenceClientModule {
    public:
        ConferenceClientModuleTestModule(int argc, char** argv, Condition& condition) :
                ConferenceClientModule(argc, argv, "ConferenceClientModuleTestModule"),
                correctOrder(true),
                setUpCalled(false),
                tearDownCalled(false),
                bodyCalled(false),
                configurationCorrect(true),
                m_condition(condition) {}

        bool correctOrder;
        bool setUpCalled;
        bool tearDownCalled;
        bool bodyCalled;
        bool configurationCorrect;
        Condition& m_condition;

        virtual void setUp() {
            string value1 = getKeyValueConfiguration().getValue<string>("global.config");
            configurationCorrect &= (value1 == "example");

            string value2 = getKeyValueConfiguration().getValue<string>("ConferenceClientModuleTestModule.config1");
            configurationCorrect &= (value2 == "example1");

            string value3 = getKeyValueConfiguration().getValue<string>("ConferenceClientModuleTestModule:ABC.config1");
            configurationCorrect &= (value3 == "example2");

            string value4NotReceived = "";
            try {
                value4NotReceived = getKeyValueConfiguration().getValue<string>("ConferenceClientModuleTestModule:DEF.config1");
                configurationCorrect = false;
            } catch (...) {}

            string value5NotReceived = "";
            try {
                value5NotReceived = getKeyValueConfiguration().getValue<string>("ConferenceClientModuleTestModule2.config2");
                configurationCorrect = false;
            } catch (...) {}

            setUpCalled = true;
            correctOrder &= (setUpCalled && !bodyCalled && !tearDownCalled);
        }

        virtual ModuleState::MODULE_EXITCODE body() {
            bodyCalled = true;
            correctOrder &= (setUpCalled && bodyCalled && !tearDownCalled);
            return ModuleState::OKAY;
        }

        virtual void tearDown() {
            tearDownCalled = true;
            correctOrder &= (setUpCalled && bodyCalled && tearDownCalled);
            Lock l(m_condition);
            m_condition.wakeAll();
        }
};


class ConferenceClientModuleTestService : public Service {
    public:
        ConferenceClientModuleTestService(const int32_t &argc, char **argv, Condition& condition) :
                myCCMTM(argc, argv, condition) {}

        virtual void beforeStop() {
            myCCMTM.setModuleState(ModuleState::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myCCMTM.runModule();
        }

        ConferenceClientModuleTestModule myCCMTM;
};

class ConferenceClientModuleTest : public CxxTest::TestSuite,
                     public connection::ConnectionHandler,
                     public ModuleConfigurationProvider {
    public:
        ConferenceClientModuleTest() :
            m_configuration(),
            m_connection() {}

        KeyValueConfiguration m_configuration;
        core::SharedPointer<connection::ModuleConnection> m_connection;

        virtual KeyValueConfiguration getConfiguration(const ModuleDescriptor& /*md*/) {
            return m_configuration;
        }

        virtual void onNewModule(connection::ModuleConnection* mc) {
            m_connection = core::SharedPointer<connection::ModuleConnection>(mc);
        }

        void testConferenceClientModule() {
            // Setup ContainerConference.
            ContainerConference *conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.101");

            // Setup DMCP.
            stringstream sstr;
            sstr << "global.config=example" << endl
            << "ConferenceClientModuleTestModule.config1=example1" << endl
            << "ConferenceClientModuleTestModule:ABC.config1=example2" << endl
            << "ConferenceClientModuleTestModule:DEF.config1=example3" << endl
            << "ConferenceClientModuleTestModule2.config2=example4" << endl;

            m_configuration = KeyValueConfiguration();
            sstr >> m_configuration;

            vector<string> noModulesToIgnore;
            ServerInformation serverInformation("127.0.0.1", 19000);
            discoverer::Server dmcpDiscovererServer(serverInformation,
                                                    "225.0.0.101",
                                                    BROADCAST_PORT_SERVER,
                                                    BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);



            string argv0("ConferenceClientModuleTestModule");
            string argv1("--id=ABC");
            string argv2("--cid=101");
            int argc = 3;
            char **argv;
            argv = new char*[argc];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());

            Condition c;
            ConferenceClientModuleTestService ccmtms(argc, argv, c);
            TS_ASSERT(ccmtms.myCCMTM.getIdentifier() == "ABC");
            //TS_ASSERT( cmtm.runModule() == ModuleState::OKAY );

            //Lock l(c);
            //if ( cmtm.getModuleState() == ModuleState::RUNNING ) {
            //    c.waitOnSignal();
            //}

            ccmtms.start();

            Thread::usleep(10000000);

            ccmtms.stop();

            TS_ASSERT(ccmtms.myCCMTM.correctOrder);
            TS_ASSERT(ccmtms.myCCMTM.setUpCalled);
            TS_ASSERT(ccmtms.myCCMTM.bodyCalled);
            TS_ASSERT(ccmtms.myCCMTM.tearDownCalled);



            OPENDAVINCI_CORE_DELETE_POINTER(conference);
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);
        }
};

#endif /*CORE_CONFERENCECLIENTMODULETESTSUITE_H_*/

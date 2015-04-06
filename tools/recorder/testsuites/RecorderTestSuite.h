/**
 * recorder - Tool for recording data
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

#ifndef RECORDERMODULETESTSUITE_H_
#define RECORDERMODULETESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "core/base/Service.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/data/recorder/RecorderCommand.h"
#include "core/io/ContainerConference.h"
#include "core/io/ContainerConferenceFactory.h"
#include "core/io/StreamFactory.h"
#include "core/io/URL.h"
#include "core/dmcp/ModuleConfigurationProvider.h"
#include "core/dmcp/discoverer/Server.h"
#include "core/dmcp/connection/Server.h"
#include "core/dmcp/connection/ConnectionHandler.h"
#include "core/dmcp/connection/ModuleConnection.h"

#include "../include/RecorderModule.h"

using namespace std;
using namespace recorder;
using namespace core::base;
using namespace core::data;
using namespace core::data::dmcp;
using namespace core::dmcp;
using namespace core::io;

class RecorderTestService : public Service {
    public:
        RecorderTestService(const int32_t &argc, char **argv) :
                myRecorder(argc, argv) {}

        virtual void beforeStop() {
            // Stop recorder.
            myRecorder.setModuleState(ModuleState::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myRecorder.runModule();
        }

    private:
        RecorderModule myRecorder;
};

class RecorderTest : public CxxTest::TestSuite,
                     public connection::ConnectionHandler,
                     public ModuleConfigurationProvider {
    public:
        RecorderTest() :
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

        void testRecorder() {
            // Setup ContainerConference.
            ContainerConference *conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.100");

            // Setup DMCP.
            stringstream sstr;
            sstr << "recorder.output = file://RecorderTest.rec" << endl
            << "global.buffer.memorySegmentSize = 1000" << endl
            << "global.buffer.numberOfMemorySegments = 5" << endl
            << "recorder.remoteControl = 0" << endl;

            m_configuration = KeyValueConfiguration();
            sstr >> m_configuration;

            vector<string> noModulesToIgnore;
            ServerInformation serverInformation("127.0.0.1", 19000);
            discoverer::Server dmcpDiscovererServer(serverInformation,
                                                    "225.0.0.100",
                                                    BROADCAST_PORT_SERVER,
                                                    BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);

            // Setup recorder.
            string argv0("recorder");
            string argv1("--cid=100");
            int32_t argc = 2;
            char **argv;
            argv = new char*[2];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());

            RecorderTestService rts(argc, argv);

            rts.start();

            Thread::usleep(10000000);
            // Send data.
            TimeStamp ts1(0, 1);
            Container c1(Container::TIMESTAMP, ts1);
            conference->send(c1);

            Thread::usleep(100000);

            TimeStamp ts2(1, 2);
            Container c2(Container::TIMESTAMP, ts2);
            conference->send(c2);

            Thread::usleep(100000);

            TimeStamp ts3(2, 3);
            Container c3(Container::TIMESTAMP, ts3);
            conference->send(c3);

            Thread::usleep(100000);

            TimeStamp ts4(3, 4);
            Container c4(Container::TIMESTAMP, ts4);
            conference->send(c4);

            Thread::usleep(100000);

            TimeStamp ts5(4, 5);
            Container c5(Container::TIMESTAMP, ts5);
            conference->send(c5);

            Thread::usleep(100000);

            rts.stop();

            Thread::usleep(100000);

            delete &(StreamFactory::getInstance());

            fstream fin("RecorderTest.rec", ios::binary | ios::in);
            TS_ASSERT(fin.good());
            Container c;
            TimeStamp ts;

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts1.toMicroseconds());
            TS_ASSERT(fin.good());

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts2.toMicroseconds());
            TS_ASSERT(fin.good());

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts3.toMicroseconds());
            TS_ASSERT(fin.good());

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts4.toMicroseconds());
            TS_ASSERT(fin.good());

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts5.toMicroseconds());
            TS_ASSERT(fin.good());
            fin.close();
            UNLINK("RecorderTest.rec");

            // "Ugly" cleaning up conference.
            OPENDAVINCI_CORE_DELETE_POINTER(conference);
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);
        }

        void testRecorderCommand() {
            core::data::recorder::RecorderCommand rc;
            stringstream s;
            s << rc;

            core::data::recorder::RecorderCommand rc2;
            s >> rc2;

            core::data::recorder::RecorderCommand rc3;
            rc3 = rc;

            core::data::recorder::RecorderCommand rc4(rc);

            TS_ASSERT(rc.toString() == "Not recording.");
            TS_ASSERT(rc.toString() == rc2.toString());
            TS_ASSERT(rc.toString() == rc3.toString());
            TS_ASSERT(rc.toString() == rc4.toString());

            rc.setCommand(core::data::recorder::RecorderCommand::RECORD);
            s << rc;
            s >> rc2;
            rc3 = rc;

            core::data::recorder::RecorderCommand rc5(rc);

            TS_ASSERT(rc.toString() == "Recording.");
            TS_ASSERT(rc.toString() == rc2.toString());
            TS_ASSERT(rc.toString() == rc3.toString());
            TS_ASSERT(rc.toString() == rc5.toString());
        }

        void testRecorderRemoteControl() {
            // Setup ContainerConference.
            ContainerConference *conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.100");

            // Setup DMCP.
            stringstream sstr;
            sstr << "recorder.output = file://RecorderTest2.rec" << endl
            << "global.buffer.memorySegmentSize = 1000" << endl
            << "global.buffer.numberOfMemorySegments = 5" << endl
            << "recorder.remoteControl = 1" << endl;

            m_configuration = KeyValueConfiguration();
            sstr >> m_configuration;

            vector<string> noModulesToIgnore;
            ServerInformation serverInformation("127.0.0.1", 19000);
            discoverer::Server dmcpDiscovererServer(serverInformation,
                                                    "225.0.0.100",
                                                    BROADCAST_PORT_SERVER,
                                                    BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);

            // Setup recorder.
            string argv0("recorder");
            string argv1("--cid=100");
            int32_t argc = 2;
            char **argv;
            argv = new char*[2];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());

            RecorderTestService rts(argc, argv);
            core::data::recorder::RecorderCommand recorderCommand;

            rts.start();

            Thread::usleep(10000000);

            // Send data.
            TimeStamp ts1(0, 1);
            Container c1(Container::TIMESTAMP, ts1);
            conference->send(c1);

            Thread::usleep(100000);

            // Start recording.
            recorderCommand.setCommand(core::data::recorder::RecorderCommand::RECORD);
            Container cRC1(Container::RECORDER_COMMAND, recorderCommand);
            conference->send(cRC1);

            Thread::usleep(100000);

            TimeStamp ts2(1, 2);
            Container c2(Container::TIMESTAMP, ts2);
            conference->send(c2);

            Thread::usleep(100000);

            TimeStamp ts3(2, 3);
            Container c3(Container::TIMESTAMP, ts3);
            conference->send(c3);

            Thread::usleep(100000);

            TimeStamp ts4(3, 4);
            Container c4(Container::TIMESTAMP, ts4);
            conference->send(c4);

            Thread::usleep(100000);

            // Stop recording.
            recorderCommand.setCommand(core::data::recorder::RecorderCommand::STOP);
            Container cRC2(Container::RECORDER_COMMAND, recorderCommand);
            conference->send(cRC2);

            Thread::usleep(100000);

            TimeStamp ts5(4, 5);
            Container c5(Container::TIMESTAMP, ts5);
            conference->send(c5);

            Thread::usleep(100000);

            rts.stop();

            Thread::usleep(100000);

            delete &(StreamFactory::getInstance());

            fstream fin("RecorderTest2.rec", ios::binary | ios::in);
            TS_ASSERT(fin.good());
            Container c;
            TimeStamp ts;

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts2.toMicroseconds());
            TS_ASSERT(fin.good());

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts3.toMicroseconds());
            TS_ASSERT(fin.good());

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts4.toMicroseconds());
            TS_ASSERT(fin.good());
            fin.close();

            UNLINK("RecorderTest2.rec");

            // "Ugly" cleaning up conference.
            OPENDAVINCI_CORE_DELETE_POINTER(conference);
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);
        }
};

#endif /*RECORDERTESTSUITE_H_*/

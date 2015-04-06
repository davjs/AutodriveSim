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

#ifndef CONTEXT_RUNTIMECONTROLCONTAINERMULTIPLEAPPSTESTSUITE_H_
#define CONTEXT_RUNTIMECONTROLCONTAINERMULTIPLEAPPSTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <stdint.h>
#include <iostream>
#include <string>

#include "core/base/KeyValueConfiguration.h"
#include "core/base/Deserializer.h"
#include "core/base/FIFOQueue.h"
#include "core/base/Hash.h"
#include "core/base/Serializable.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/data/SerializableData.h"
#include "core/base/ConferenceClientModule.h"
#include "core/data/environment/Point3.h"
#include "core/data/environment/Position.h"
#include "context/base/DirectInterface.h"
#include "context/base/RuntimeControl.h"
#include "context/base/RuntimeEnvironment.h"
#include "context/base/SystemFeedbackComponent.h"
#include "context/base/SystemReportingComponent.h"

using namespace std;
using namespace core::base;
using namespace core::data;
using namespace context::base;

class RuntimeControlContainerMultipleAppsTestData : public core::data::SerializableData {
    public:
        RuntimeControlContainerMultipleAppsTestData() :
            m_int(0),
            m_id("") {}

        uint32_t m_int;
        string m_id;

        const string toString() const {
            stringstream sstr;
            sstr << m_id << " " << m_int;
            return sstr.str();
        }

        ostream& operator<<(ostream &out) const {
            SerializationFactory sf;

            Serializer &s = sf.getSerializer(out);

            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                    m_int);

            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('m', '_', 'i', 'd') >::RESULT,
                    m_id);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory sf;

            Deserializer &d = sf.getDeserializer(in);

            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('m', '_', 'i', 'd') >::RESULT,
                   m_id);

            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                   m_int);

            return in;
        }
};

class RuntimeControlContainerMultipleAppsTestModule : public ConferenceClientModule {
    public:
        RuntimeControlContainerMultipleAppsTestModule(const int32_t &argc, char **argv) :
            ConferenceClientModule(argc, argv, "RuntimeControlContainerMultipleAppsTestModule"),
            m_cycleCounter(0),
            m_config(),
            m_receivedData() {}

        virtual void setUp() {}

        virtual void tearDown() {}

        virtual ModuleState::MODULE_EXITCODE body() {
            m_config = getKeyValueConfiguration();

            m_config.getValue<string>("runtimecontrolcontainermultipleappstestmodule.key1");

            addDataStoreFor(Container::POSITION, m_receivedData);
            while (getModuleState() == ModuleState::RUNNING) {
                m_cycleCounter++;

                stringstream sstrId;
                sstrId << getIdentifier();

                RuntimeControlContainerMultipleAppsTestData tcctsd;
                tcctsd.m_int = m_cycleCounter;
                tcctsd.m_id = sstrId.str();
                Container c(Container::UNDEFINEDDATA, tcctsd);
                getConference().send(c);
            }

            return ModuleState::OKAY;
        }

        KeyValueConfiguration getConfiguration() {
            return m_config;
        }

        uint32_t getCycleCounter() const {
            return m_cycleCounter;
        }

        FIFOQueue& getReceivedData() {
            return m_receivedData;
        }

    private:
        uint32_t m_cycleCounter;
        KeyValueConfiguration m_config;
        FIFOQueue m_receivedData;
};

class RuntimeControlContainerMultipleAppsTestModuleForSampleData : public ConferenceClientModule {
    public:
        RuntimeControlContainerMultipleAppsTestModuleForSampleData(const int32_t &argc, char **argv) :
            ConferenceClientModule(argc, argv, "RuntimeControlContainerMultipleAppsTestModuleForSampleData"),
            m_cycleCounter(0),
            m_receivedData() {}

        virtual void setUp() {}

        virtual void tearDown() {}

        virtual ModuleState::MODULE_EXITCODE body() {
            addDataStoreFor(m_receivedData);
            while (getModuleState() == ModuleState::RUNNING) {
                m_cycleCounter++;
            }

            return ModuleState::OKAY;
        }

        uint32_t getCycleCounter() const {
            return m_cycleCounter;
        }

        FIFOQueue& getReceivedData() {
            return m_receivedData;
        }

    private:
        uint32_t m_cycleCounter;
        FIFOQueue m_receivedData;
};

////////////////////////////////////////////////////////////////////////////////

class RuntimeControlContainerMultipleAppsTestSystemPartReply : public SystemFeedbackComponent {
    public:
        RuntimeControlContainerMultipleAppsTestSystemPartReply(const float &freq) :
            m_freq(freq),
            m_receivedDataFIFO(),
            m_replyCounter(0) {}

        float getFrequency() const {
            return m_freq;

        }

        virtual void setup() {}

        virtual void tearDown() {}

        virtual void step(const core::wrapper::Time &t, SendContainerToSystemsUnderTest &sender) {
            clog << "Call to RuntimeControlContainerMultipleAppsTestSystemPartReply for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            const uint32_t SIZE = getFIFO().getSize();
            for (uint32_t i = 0; i < SIZE; i++) {
                Container c = getFIFO().leave();
                clog << "(RuntimeControlContainerMultipleAppsTestSystemPartReply) Sent at " << c.getSentTimeStamp().toString() << ", Received at " << c.getReceivedTimeStamp().toString() << endl;
                m_receivedDataFIFO.add(c);

                // Wait for adding containers.
                Thread::usleep(100);
            }

            core::data::environment::Position p;
            p.setPosition(core::data::environment::Point3(m_replyCounter, m_replyCounter+1, m_replyCounter+2));

            Container c(Container::POSITION, p);
            sender.sendToSystemsUnderTest(c);

            m_replyCounter++;
        }

        const float m_freq;
        FIFOQueue m_receivedDataFIFO;
        uint32_t m_replyCounter;
};

class RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation : public SystemFeedbackComponent {
    public:
        RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation(const float &freq) :
            m_freq(freq),
            m_receivedDataFIFO(),
            m_replyCounter(0) {}

        float getFrequency() const {
            return m_freq;
        }

        virtual void setup() {}

        virtual void tearDown() {}

        virtual void step(const core::wrapper::Time &t, SendContainerToSystemsUnderTest &sender) {
            clog << "Call to RuntimeControlContainerMultipleAppsTestSystemPartReply for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            const uint32_t SIZE = getFIFO().getSize();
            for (uint32_t i = 0; i < SIZE; i++) {
                Container c = getFIFO().leave();
                clog << "(RuntimeControlContainerMultipleAppsTestSystemPartReply) Sent at " << c.getSentTimeStamp().toString() << ", Received at " << c.getReceivedTimeStamp().toString() << endl;
                m_receivedDataFIFO.add(c);

                // Wait for adding containers.
                Thread::usleep(100);
            }

            core::data::environment::Position p;
            p.setRotation(core::data::environment::Point3(m_replyCounter, m_replyCounter+1, m_replyCounter+2));

            Container c(Container::POSITION, p);
            sender.sendToSystemsUnderTest(c);

            m_replyCounter++;
        }

        const float m_freq;
        FIFOQueue m_receivedDataFIFO;
        uint32_t m_replyCounter;
};

class RuntimeControlContainerMultipleAppsTestSystemReportingComponent : public SystemReportingComponent {
    public:
        RuntimeControlContainerMultipleAppsTestSystemReportingComponent() :
            m_counter(0) {}

        virtual void setup() {}

        virtual void tearDown() {}

        virtual void report(const core::wrapper::Time &t) {
            clog << "Call to RuntimeControlContainerMultipleAppsTestSystemReportingComponent for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            // Simply remove all entries.
            getFIFO().clear();

            m_counter++;
        }

        uint32_t m_counter;
};

////////////////////////////////////////////////////////////////////////////////

class RuntimeControlContainerMultipleAppsTest : public CxxTest::TestSuite {
    public:
        void testRuntimeControlContainerRegularRunReceivingSendingTwoAppsSameFreqOneSP() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            ////////////////////////////////////////////////////////////////////

            // Setup application.
            string argv0App1("runtimecontrolcontainermultipleappstestmodule");
            string argv1App1("--cid=100");
            int32_t argcApp1 = 2;
            char **argvApp1;
            argvApp1 = new char*[2];
            argvApp1[0] = const_cast<char*>(argv0App1.c_str());
            argvApp1[1] = const_cast<char*>(argv1App1.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp1(argcApp1, argvApp1);

            string argv0App2("runtimecontrolcontainermultipleappstestmodule");
            string argv1App2("--cid=100");
            int32_t argcApp2 = 2;
            char **argvApp2;
            argvApp2 = new char*[2];
            argvApp2[0] = const_cast<char*>(argv0App2.c_str());
            argvApp2[1] = const_cast<char*>(argv1App2.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp2(argcApp2, argvApp2);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeControlContainerMultipleAppsTestSystemReportingComponent reporter1;
            RuntimeControlContainerMultipleAppsTestSystemReportingComponent reporter2;

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(rtccmatmApp2);
            rte.add(rtccmatspr);
            rte.add(reporter1);
            rte.add(reporter2);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 25);
            uint32_t undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));

                    TS_ASSERT(((undefDataCnt/2)+1) == data.m_int);
                    undefDataCnt++;
                }
            }

            clog << "REPORTER1-SIZE: " << reporter1.m_counter << endl;
            TS_ASSERT(reporter1.m_counter == 30);

            clog << "REPORTER2-SIZE: " << reporter2.m_counter << endl;
            TS_ASSERT(reporter1.m_counter == 30);

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 9);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();
                core::data::environment::Point3 p = pos.getPosition();
                core::data::environment::Point3 ref(i+1, i+2, i+3);

                clog << "C1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            sstrConfigReceivedA1 << rtccmatmApp1.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            ////////////////////////////////////////////////////////////////////

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 = rtccmatmApp2.getReceivedData().getSize();
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 == 9);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2; i++) {
                Container c = rtccmatmApp2.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();
                core::data::environment::Point3 p = pos.getPosition();
                core::data::environment::Point3 ref(i+1, i+2, i+3);

                clog << "D1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfigReceivedA2;
            sstrConfigReceivedA2 << rtccmatmApp2.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA2.str() == sstrConfig.str());

            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 9);

            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp2.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp2.getCycleCounter() == 9);
        }

        void testRuntimeControlContainerRegularRunReceivingSendingTwoAppsOneReceivingDataFromOtherAppSameFreqOneSP() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "RuntimeControlContainerMultipleAppsTestModuleForSampleData.key3 = value3" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            ////////////////////////////////////////////////////////////////////

            // Setup application.
            string argv0App1("runtimecontrolcontainermultipleappstestmodule");
            string argv1App1("--cid=100");
            int32_t argcApp1 = 2;
            char **argvApp1;
            argvApp1 = new char*[2];
            argvApp1[0] = const_cast<char*>(argv0App1.c_str());
            argvApp1[1] = const_cast<char*>(argv1App1.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp1(argcApp1, argvApp1);

            string argv0App2("runtimecontrolcontainermultipleappstestmoduleforsampledata");
            string argv1App2("--cid=100");
            int32_t argcApp2 = 2;
            char **argvApp2;
            argvApp2 = new char*[2];
            argvApp2[0] = const_cast<char*>(argv0App2.c_str());
            argvApp2[1] = const_cast<char*>(argv1App2.c_str());

            RuntimeControlContainerMultipleAppsTestModuleForSampleData app2(argcApp2, argvApp2);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeControlContainerMultipleAppsTestSystemReportingComponent reporter1;
            RuntimeControlContainerMultipleAppsTestSystemReportingComponent reporter2;

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(app2);
            rte.add(rtccmatspr);
            rte.add(reporter1);
            rte.add(reporter2);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 17);
            uint32_t undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    undefDataCnt++;

                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", undefDataCnt: " << undefDataCnt << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));

                    TS_ASSERT(undefDataCnt == data.m_int);
                }
            }

            clog << "REPORTER1-SIZE: " << reporter1.m_counter << endl;
            TS_ASSERT(reporter1.m_counter == 30);

            clog << "REPORTER2-SIZE: " << reporter2.m_counter << endl;
            TS_ASSERT(reporter1.m_counter == 30);

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 9);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();
                core::data::environment::Point3 p = pos.getPosition();
                core::data::environment::Point3 ref(i+1, i+2, i+3);

                clog << "C1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            sstrConfigReceivedA1 << rtccmatmApp1.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            ////////////////////////////////////////////////////////////////////

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 = app2.getReceivedData().getSize();
            cerr << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2:" << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 == 18);
            uint32_t cntApp2Position = 0;
            uint32_t cntApp2SampleData = 0;
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2; i++) {
                Container c = app2.getReceivedData().leave();
                if (c.getDataType() == Container::POSITION) {
                    cntApp2Position++;
                    core::data::environment::Position pos = c.getData<core::data::environment::Position>();
                    core::data::environment::Point3 p = pos.getPosition();
                    core::data::environment::Point3 ref(cntApp2Position, cntApp2Position+1, cntApp2Position+2);

                    clog << "D1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp2Position * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp2Position * 1000 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    cntApp2SampleData++;
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();
                    clog << "E1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << ", data:" << data.m_int << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp2SampleData * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp2SampleData * 1000 * 1000));
                    TS_ASSERT(cntApp2SampleData == data.m_int);
                }
            }

            // Check if the received configuration is valid.
            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 9);

            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << app2.getCycleCounter() << endl;
            TS_ASSERT(app2.getCycleCounter() == 9);
        }

        void testRuntimeControlContainerRegularRunReceivingSendingTwoAppsA1twiceAsFastAsA2OneSP() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            ////////////////////////////////////////////////////////////////////

            // Setup application.
            string argv0App1("runtimecontrolcontainermultipleappstestmodule");
            string argv1App1("--cid=100");
            string argv2App1("--freq=2");
            string argv3App1("--id=1");
            int32_t argcApp1 = 4;
            char **argvApp1;
            argvApp1 = new char*[4];
            argvApp1[0] = const_cast<char*>(argv0App1.c_str());
            argvApp1[1] = const_cast<char*>(argv1App1.c_str());
            argvApp1[2] = const_cast<char*>(argv2App1.c_str());
            argvApp1[3] = const_cast<char*>(argv3App1.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp1(argcApp1, argvApp1);

            string argv0App2("runtimecontrolcontainermultipleappstestmodule");
            string argv1App2("--cid=100");
            string argv2App2("--id=2");
            int32_t argcApp2 = 3;
            char **argvApp2;
            argvApp2 = new char*[3];
            argvApp2[0] = const_cast<char*>(argv0App2.c_str());
            argvApp2[1] = const_cast<char*>(argv1App2.c_str());
            argvApp2[2] = const_cast<char*>(argv2App2.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp2(argcApp2, argvApp2);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(rtccmatmApp2);
            rte.add(rtccmatspr);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 34);
            uint32_t cntApp1 = 0;
            uint32_t cntApp2 = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << ", m_id:" << data.m_id << ", m_int: " << data.m_int << endl;

                if (data.m_id == "1") {
                    cntApp1++;

                    cerr << "cntApp1: " << cntApp1 << endl;
                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp1 * 500 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp1 * 500 * 1000));
                    TS_ASSERT(cntApp1 == data.m_int);
                }

                if (data.m_id == "2") {
                    cntApp2++;

                    cerr << "cntApp2: " << cntApp2 << endl;
                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp2 * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp2 * 1000 * 1000));
                    TS_ASSERT(cntApp2 == data.m_int);
                }
            }

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 9);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();
                core::data::environment::Point3 p = pos.getPosition();
                core::data::environment::Point3 ref(i+1, i+2, i+3);

                clog << "C1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            sstrConfigReceivedA1 << rtccmatmApp1.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            ////////////////////////////////////////////////////////////////////

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 = rtccmatmApp2.getReceivedData().getSize();
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 == 9);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2; i++) {
                Container c = rtccmatmApp2.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();
                core::data::environment::Point3 p = pos.getPosition();
                core::data::environment::Point3 ref(i+1, i+2, i+3);

                clog << "D1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfigReceivedA2;
            sstrConfigReceivedA2 << rtccmatmApp2.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA2.str() == sstrConfig.str());

            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 19);

            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp2.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp2.getCycleCounter() == 9);
        }

        void testRuntimeControlContainerRegularRunReceivingSendingOneAppTwoSystemPartsSameFreq() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            ////////////////////////////////////////////////////////////////////

            // Setup application.
            string argv0App1("runtimecontrolcontainermultipleappstestmodule");
            string argv1App1("--cid=100");
            int32_t argcApp1 = 2;
            char **argvApp1;
            argvApp1 = new char*[2];
            argvApp1[0] = const_cast<char*>(argv0App1.c_str());
            argvApp1[1] = const_cast<char*>(argv1App1.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp1(argcApp1, argvApp1);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation rtccmatsprRotation(1);

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(rtccmatspr);
            rte.add(rtccmatsprRotation);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 26);
            uint32_t undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    undefDataCnt++;
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));

                    TS_ASSERT(undefDataCnt == data.m_int);
                }
            }

            const uint32_t SIZE_SP2 = rtccmatsprRotation.m_receivedDataFIFO.getSize();
            clog << "SIZE_SP2: " << SIZE_SP2 << endl;
            TS_ASSERT(SIZE_SP2 == 27);
            undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatsprRotation.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    undefDataCnt++;
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));

                    TS_ASSERT(undefDataCnt == data.m_int);
                }
            }

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 18);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();

                core::data::environment::Point3 p;
                if (pos.getPosition().getZ() > 0) {
                    p = pos.getPosition();
                }
                if (pos.getRotation().getZ() > 0) {
                    p = pos.getRotation();
                }
                core::data::environment::Point3 ref((i/2)+1, (i/2)+2, (i/2)+3);

                clog << "C1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((i/2)+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((i/2)+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            sstrConfigReceivedA1 << rtccmatmApp1.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 9);
        }

        void testRuntimeControlContainerRegularRunReceivingSendingOneAppTwoSystemPartsSP2TwiceAsFastAsSP1() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            ////////////////////////////////////////////////////////////////////

            // Setup application.
            string argv0App1("runtimecontrolcontainermultipleappstestmodule");
            string argv1App1("--cid=100");
            int32_t argcApp1 = 2;
            char **argvApp1;
            argvApp1 = new char*[2];
            argvApp1[0] = const_cast<char*>(argv0App1.c_str());
            argvApp1[1] = const_cast<char*>(argv1App1.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp1(argcApp1, argvApp1);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation rtccmatsprRotation(2);

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(rtccmatspr);
            rte.add(rtccmatsprRotation);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 35);
            uint32_t undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    undefDataCnt++;
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));

                    TS_ASSERT(undefDataCnt == data.m_int);
                }
            }

            const uint32_t SIZE_SP2 = rtccmatsprRotation.m_receivedDataFIFO.getSize();
            clog << "SIZE_SP2: " << SIZE_SP2 << endl;
            TS_ASSERT(SIZE_SP2 == 38);
            undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatsprRotation.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    undefDataCnt++;
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));

                    TS_ASSERT(undefDataCnt == data.m_int);
                }
            }

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 28);
            uint32_t cntSP1 = 0;
            uint32_t cntSP2 = 0;
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();

                core::data::environment::Point3 p;
                if (pos.getPosition().getZ() > 0) {
                    cntSP1++;
                    p = pos.getPosition();
                    core::data::environment::Point3 ref(cntSP1, cntSP1+1, cntSP1+2);

                    clog << "C1a-i: " << i << ", cntSP1: " << cntSP1 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
                if (pos.getRotation().getZ() > 0) {
                    cntSP2++;
                    p = pos.getRotation();
                    core::data::environment::Point3 ref(cntSP2, cntSP2+1, cntSP2+2);

                    clog << "C1b-i: " << i << ", cntSP2: " << cntSP2 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            sstrConfigReceivedA1 << rtccmatmApp1.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 9);
        }

        void testRuntimeControlContainerRegularRunReceivingSendingTwoAppsSameFreqTwoSystemPartsSameFreq() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            ////////////////////////////////////////////////////////////////////

            // Setup application.
            string argv0App1("runtimecontrolcontainermultipleappstestmodule");
            string argv1App1("--cid=100");
            int32_t argcApp1 = 2;
            char **argvApp1;
            argvApp1 = new char*[2];
            argvApp1[0] = const_cast<char*>(argv0App1.c_str());
            argvApp1[1] = const_cast<char*>(argv1App1.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp1(argcApp1, argvApp1);

            string argv0App2("runtimecontrolcontainermultipleappstestmodule");
            string argv1App2("--cid=100");
            int32_t argcApp2 = 2;
            char **argvApp2;
            argvApp2 = new char*[2];
            argvApp2[0] = const_cast<char*>(argv0App2.c_str());
            argvApp2[1] = const_cast<char*>(argv1App2.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp2(argcApp2, argvApp2);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation rtccmatsprRotation(1);

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(rtccmatmApp2);
            rte.add(rtccmatspr);
            rte.add(rtccmatsprRotation);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 34);
            uint32_t undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));

                    TS_ASSERT(((undefDataCnt/2)+1) == data.m_int);
                    undefDataCnt++;
                }
            }

            const uint32_t SIZE_SP2 = rtccmatsprRotation.m_receivedDataFIFO.getSize();
            clog << "SIZE_SP2: " << SIZE_SP2 << endl;
            TS_ASSERT(SIZE_SP2 == 35);
            undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatsprRotation.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B2-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));

                    TS_ASSERT(((undefDataCnt/2)+1) == data.m_int);
                    undefDataCnt++;
                }
            }

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 18);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();

                core::data::environment::Point3 p;
                if (pos.getPosition().getZ() > 0) {
                    p = pos.getPosition();
                }
                if (pos.getRotation().getZ() > 0) {
                    p = pos.getRotation();
                }
                core::data::environment::Point3 ref((i/2)+1, (i/2)+2, (i/2)+3);

                clog << "C1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((i/2)+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((i/2)+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            sstrConfigReceivedA1 << rtccmatmApp1.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            ////////////////////////////////////////////////////////////////////

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 = rtccmatmApp2.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 == 18);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2; i++) {
                Container c = rtccmatmApp2.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();

                core::data::environment::Point3 p;
                if (pos.getPosition().getZ() > 0) {
                    p = pos.getPosition();
                }
                if (pos.getRotation().getZ() > 0) {
                    p = pos.getRotation();
                }
                core::data::environment::Point3 ref((i/2)+1, (i/2)+2, (i/2)+3);

                clog << "D1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((i/2)+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((i/2)+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfigReceivedA2;
            sstrConfigReceivedA2 << rtccmatmApp2.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA2.str() == sstrConfig.str());

            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 9);

            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp2.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp2.getCycleCounter() == 9);
        }

        void testRuntimeControlContainerRegularRunReceivingSendingTwoAppsA1twiceAsFastAsA2TwoSystemPartsSameFreq() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            ////////////////////////////////////////////////////////////////////

            // Setup application.
            string argv0App1("runtimecontrolcontainermultipleappstestmodule");
            string argv1App1("--cid=100");
            string argv2App1("--freq=2");
            string argv3App1("--id=1");
            int32_t argcApp1 = 4;
            char **argvApp1;
            argvApp1 = new char*[4];
            argvApp1[0] = const_cast<char*>(argv0App1.c_str());
            argvApp1[1] = const_cast<char*>(argv1App1.c_str());
            argvApp1[2] = const_cast<char*>(argv2App1.c_str());
            argvApp1[3] = const_cast<char*>(argv3App1.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp1(argcApp1, argvApp1);

            string argv0App2("runtimecontrolcontainermultipleappstestmodule");
            string argv1App2("--cid=100");
            string argv2App2("--id=2");
            int32_t argcApp2 = 3;
            char **argvApp2;
            argvApp2 = new char*[3];
            argvApp2[0] = const_cast<char*>(argv0App2.c_str());
            argvApp2[1] = const_cast<char*>(argv1App2.c_str());
            argvApp2[2] = const_cast<char*>(argv2App2.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp2(argcApp2, argvApp2);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation rtccmatsprRotation(1);

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(rtccmatmApp2);
            rte.add(rtccmatspr);
            rte.add(rtccmatsprRotation);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 43);
            uint32_t cntApp1 = 0;
            uint32_t cntApp2 = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << ", m_id:" << data.m_id << ", m_int: " << data.m_int << endl;

                    if (data.m_id == "1") {
                        cntApp1++;

                        cerr << "cntApp1: " << cntApp1 << endl;
                        TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp1 * 500 * 1000));
                        TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp1 * 500 * 1000));
                        TS_ASSERT(cntApp1 == data.m_int);
                    }

                    if (data.m_id == "2") {
                        cntApp2++;

                        cerr << "cntApp2: " << cntApp2 << endl;
                        TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp2 * 1000 * 1000));
                        TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp2 * 1000 * 1000));
                        TS_ASSERT(cntApp2 == data.m_int);
                    }
                }
            }

            const uint32_t SIZE_SP2 = rtccmatsprRotation.m_receivedDataFIFO.getSize();
            clog << "SIZE_SP2: " << SIZE_SP2 << endl;
            TS_ASSERT(SIZE_SP2 == 44);
            cntApp1 = 0;
            cntApp2 = 0;
            for(uint32_t i = 0; i < SIZE_SP2; i++) {
                Container c = rtccmatsprRotation.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B2-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << ", m_id:" << data.m_id << ", m_int: " << data.m_int << endl;

                    if (data.m_id == "1") {
                        cntApp1++;

                        cerr << "cntApp1: " << cntApp1 << endl;
                        TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp1 * 500 * 1000));
                        TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp1 * 500 * 1000));
                        TS_ASSERT(cntApp1 == data.m_int);
                    }

                    if (data.m_id == "2") {
                        cntApp2++;

                        cerr << "cntApp2: " << cntApp2 << endl;
                        TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp2 * 1000 * 1000));
                        TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp2 * 1000 * 1000));
                        TS_ASSERT(cntApp2 == data.m_int);
                    }
                }
            }

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 18);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();

                core::data::environment::Point3 p;
                if (pos.getPosition().getZ() > 0) {
                    p = pos.getPosition();
                }
                if (pos.getRotation().getZ() > 0) {
                    p = pos.getRotation();
                }
                core::data::environment::Point3 ref((i/2)+1, (i/2)+2, (i/2)+3);

                clog << "C1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((i/2)+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((i/2)+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            sstrConfigReceivedA1 << rtccmatmApp1.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            ////////////////////////////////////////////////////////////////////

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 = rtccmatmApp2.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 == 18);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2; i++) {
                Container c = rtccmatmApp2.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();

                core::data::environment::Point3 p;
                if (pos.getPosition().getZ() > 0) {
                    p = pos.getPosition();
                }
                if (pos.getRotation().getZ() > 0) {
                    p = pos.getRotation();
                }
                core::data::environment::Point3 ref((i/2)+1, (i/2)+2, (i/2)+3);

                clog << "D1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((i/2)+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((i/2)+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfigReceivedA2;
            sstrConfigReceivedA2 << rtccmatmApp2.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA2.str() == sstrConfig.str());

            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 19);

            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp2.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp2.getCycleCounter() == 9);
        }

        void testRuntimeControlContainerRegularRunReceivingSendingTwoAppsSameFreqTwoSystemPartsSP2TwiceAsFastAsSP1() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            ////////////////////////////////////////////////////////////////////

            // Setup application.
            string argv0App1("runtimecontrolcontainermultipleappstestmodule");
            string argv1App1("--cid=100");
            int32_t argcApp1 = 2;
            char **argvApp1;
            argvApp1 = new char*[2];
            argvApp1[0] = const_cast<char*>(argv0App1.c_str());
            argvApp1[1] = const_cast<char*>(argv1App1.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp1(argcApp1, argvApp1);

            string argv0App2("runtimecontrolcontainermultipleappstestmodule");
            string argv1App2("--cid=100");
            int32_t argcApp2 = 2;
            char **argvApp2;
            argvApp2 = new char*[2];
            argvApp2[0] = const_cast<char*>(argv0App2.c_str());
            argvApp2[1] = const_cast<char*>(argv1App2.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp2(argcApp2, argvApp2);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation rtccmatsprRotation(2);

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(rtccmatmApp2);
            rte.add(rtccmatspr);
            rte.add(rtccmatsprRotation);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 43);
            uint32_t undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));

                    TS_ASSERT(((undefDataCnt/2)+1) == data.m_int);
                    undefDataCnt++;
                }
            }

            const uint32_t SIZE_SP2 = rtccmatsprRotation.m_receivedDataFIFO.getSize();
            clog << "SIZE_SP2: " << SIZE_SP2 << endl;
            TS_ASSERT(SIZE_SP2 == 47);
            undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatsprRotation.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));

                    TS_ASSERT(((undefDataCnt/2)+1) == data.m_int);
                    undefDataCnt++;
                }
            }

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 28);
            uint32_t cntSP1 = 0;
            uint32_t cntSP2 = 0;
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();

                core::data::environment::Point3 p;
                if (pos.getPosition().getZ() > 0) {
                    cntSP1++;
                    p = pos.getPosition();
                    core::data::environment::Point3 ref(cntSP1, cntSP1+1, cntSP1+2);

                    clog << "C1a-i: " << i << ", cntSP1: " << cntSP1 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
                if (pos.getRotation().getZ() > 0) {
                    cntSP2++;
                    p = pos.getRotation();
                    core::data::environment::Point3 ref(cntSP2, cntSP2+1, cntSP2+2);

                    clog << "C1b-i: " << i << ", cntSP2: " << cntSP2 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            sstrConfigReceivedA1 << rtccmatmApp1.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            ////////////////////////////////////////////////////////////////////

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 = rtccmatmApp2.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 == 28);
            cntSP1 = 0;
            cntSP2 = 0;
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2; i++) {
                Container c = rtccmatmApp2.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();

                core::data::environment::Point3 p;
                if (pos.getPosition().getZ() > 0) {
                    cntSP1++;
                    p = pos.getPosition();
                    core::data::environment::Point3 ref(cntSP1, cntSP1+1, cntSP1+2);

                    clog << "D1a-i: " << i << ", cntSP1: " << cntSP1 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
                if (pos.getRotation().getZ() > 0) {
                    cntSP2++;
                    p = pos.getRotation();
                    core::data::environment::Point3 ref(cntSP2, cntSP2+1, cntSP2+2);

                    clog << "D1b-i: " << i << ", cntSP2: " << cntSP2 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
            }

            // Check if the received configuration is valid.
            stringstream sstrConfigReceivedA2;
            sstrConfigReceivedA2 << rtccmatmApp2.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA2.str() == sstrConfig.str());

            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 9);

            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp2.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp2.getCycleCounter() == 9);
        }

        void testRuntimeControlContainerRegularRunReceivingSendingTwoAppsA1TwiceAsFastAsA2FreqTwoSystemPartsSP2TwiceAsFastAsSP1() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            ////////////////////////////////////////////////////////////////////

            // Setup application.
            string argv0App1("runtimecontrolcontainermultipleappstestmodule");
            string argv1App1("--cid=100");
            string argv2App1("--freq=2");
            int32_t argcApp1 = 3;
            char **argvApp1;
            argvApp1 = new char*[3];
            argvApp1[0] = const_cast<char*>(argv0App1.c_str());
            argvApp1[1] = const_cast<char*>(argv1App1.c_str());
            argvApp1[2] = const_cast<char*>(argv2App1.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp1(argcApp1, argvApp1);

            string argv0App2("runtimecontrolcontainermultipleappstestmodule");
            string argv1App2("--cid=100");
            int32_t argcApp2 = 2;
            char **argvApp2;
            argvApp2 = new char*[2];
            argvApp2[0] = const_cast<char*>(argv0App2.c_str());
            argvApp2[1] = const_cast<char*>(argv1App2.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp2(argcApp2, argvApp2);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation rtccmatsprRotation(2);

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(rtccmatmApp2);
            rte.add(rtccmatspr);
            rte.add(rtccmatsprRotation);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 52);
            uint32_t cntApp1 = 0;
            uint32_t cntApp2 = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << ", m_id:" << data.m_id << ", m_int: " << data.m_int << endl;

                    if (data.m_id == "1") {
                        cntApp1++;

                        cerr << "cntApp1: " << cntApp1 << endl;
                        TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp1 * 500 * 1000));
                        TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp1 * 500 * 1000));
                        TS_ASSERT(cntApp1 == data.m_int);
                    }

                    if (data.m_id == "2") {
                        cntApp2++;

                        cerr << "cntApp2: " << cntApp2 << endl;
                        TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp2 * 1000 * 1000));
                        TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp2 * 1000 * 1000));
                        TS_ASSERT(cntApp2 == data.m_int);
                    }
                }
            }

            const uint32_t SIZE_SP2 = rtccmatsprRotation.m_receivedDataFIFO.getSize();
            clog << "SIZE_SP2: " << SIZE_SP2 << endl;
            TS_ASSERT(SIZE_SP2 == 56);
            cntApp1 = 0;
            cntApp2 = 0;
            for(uint32_t i = 0; i < SIZE_SP2; i++) {
                Container c = rtccmatsprRotation.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B2-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << ", m_id:" << data.m_id << ", m_int: " << data.m_int << endl;

                    if (data.m_id == "1") {
                        cntApp1++;

                        cerr << "cntApp1: " << cntApp1 << endl;
                        TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp1 * 500 * 1000));
                        TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp1 * 500 * 1000));
                        TS_ASSERT(cntApp1 == data.m_int);
                    }

                    if (data.m_id == "2") {
                        cntApp2++;

                        cerr << "cntApp2: " << cntApp2 << endl;
                        TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp2 * 1000 * 1000));
                        TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp2 * 1000 * 1000));
                        TS_ASSERT(cntApp2 == data.m_int);
                    }
                }
            }

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 28);
            uint32_t cntSP1 = 0;
            uint32_t cntSP2 = 0;
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();

                core::data::environment::Point3 p;
                if (pos.getPosition().getZ() > 0) {
                    cntSP1++;
                    p = pos.getPosition();
                    core::data::environment::Point3 ref(cntSP1, cntSP1+1, cntSP1+2);

                    clog << "C1a-i: " << i << ", cntSP1: " << cntSP1 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
                if (pos.getRotation().getZ() > 0) {
                    cntSP2++;
                    p = pos.getRotation();
                    core::data::environment::Point3 ref(cntSP2, cntSP2+1, cntSP2+2);

                    clog << "C1b-i: " << i << ", cntSP2: " << cntSP2 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            sstrConfigReceivedA1 << rtccmatmApp1.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            ////////////////////////////////////////////////////////////////////

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 = rtccmatmApp2.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 == 28);
            cntSP1 = 0;
            cntSP2 = 0;
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2; i++) {
                Container c = rtccmatmApp2.getReceivedData().leave();
                core::data::environment::Position pos = c.getData<core::data::environment::Position>();

                core::data::environment::Point3 p;
                if (pos.getPosition().getZ() > 0) {
                    cntSP1++;
                    p = pos.getPosition();
                    core::data::environment::Point3 ref(cntSP1, cntSP1+1, cntSP1+2);

                    clog << "D1a-i: " << i << ", cntSP1: " << cntSP1 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
                if (pos.getRotation().getZ() > 0) {
                    cntSP2++;
                    p = pos.getRotation();
                    core::data::environment::Point3 ref(cntSP2, cntSP2+1, cntSP2+2);

                    clog << "D1b-i: " << i << ", cntSP2: " << cntSP2 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
            }

            // Check if the received configuration is valid.
            stringstream sstrConfigReceivedA2;
            sstrConfigReceivedA2 << rtccmatmApp2.getConfiguration();
            TS_ASSERT(sstrConfigReceivedA2.str() == sstrConfig.str());

            // Check if the application was called 19 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 19);

            // Check if the application A2 was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp2.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp2.getCycleCounter() == 9);
        }
};

#endif /*CONTEXT_RUNTIMECONTROLCONTAINERMULTIPLEAPPSTESTSUITE_H_*/

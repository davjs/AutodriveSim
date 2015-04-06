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

#ifndef CORE_WRAPPER_TCPTESTSUITE_H_
#define CORE_WRAPPER_TCPTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include "core/platform.h"
#include "core/SharedPointer.h"


#include "mocks/ConnectionListenerMock.h"
#include "mocks/StringListenerMock.h"
#include "mocks/TCPAcceptorListenerMock.h"

#include "core/wrapper/StringListener.h"
#include "core/wrapper/NetworkLibraryProducts.h"

#ifndef WIN32
	#include "core/wrapper/POSIX/POSIXTCPFactoryWorker.h"
#endif
#ifdef WIN32
	#include "core/wrapper/WIN32/WIN32TCPFactoryWorker.h"
#endif

#include "core/wrapper/TCPAcceptorListener.h"
#include "core/wrapper/TCPConnection.h"
#include "core/wrapper/TCPAcceptor.h"
#include "core/wrapper/TCPFactory.h"

using namespace std;
using namespace core;
using namespace core::base;

template <typename worker> struct TCPAcceptorTests
{
        static void acceptTest()
        {
            mocks::TCPAcceptorListenerMock ah;

            SharedPointer<wrapper::TCPAcceptor> acceptor(worker::createTCPAcceptor(20000));
            acceptor->setAcceptorListener(&ah);
            acceptor->start();

            SharedPointer<wrapper::TCPConnection> connection(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection->start();

            TS_ASSERT(ah.CALLWAITER_onNewConnection.wait());
        }

        static void multipleAcceptTest()
        {
            mocks::TCPAcceptorListenerMock ah1;
            mocks::TCPAcceptorListenerMock ah2;

            SharedPointer<wrapper::TCPAcceptor> acceptor(worker::createTCPAcceptor(20000));
            acceptor->setAcceptorListener(&ah1);
            acceptor->start();

            SharedPointer<wrapper::TCPConnection> connection(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection->start();

            TS_ASSERT(ah1.CALLWAITER_onNewConnection.wait());

            acceptor->setAcceptorListener(&ah2);

            SharedPointer<wrapper::TCPConnection> connection2(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection->start();

            TS_ASSERT(ah2.CALLWAITER_onNewConnection.wait());
        }

        static void noAcceptTest() {
            mocks::TCPAcceptorListenerMock am1;
            mocks::TCPAcceptorListenerMock am2;

            SharedPointer<wrapper::TCPAcceptor> acceptor(worker::createTCPAcceptor(20000));
            acceptor->setAcceptorListener(&am1);
            acceptor->start();

            SharedPointer<wrapper::TCPConnection> connection(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection->start();

            TS_ASSERT(am1.CALLWAITER_onNewConnection.wait());

            acceptor->setAcceptorListener(&am2);
            acceptor->stop();
            bool exceptionCaught = false;
            clog << "Test:" << endl;
            wrapper::TCPConnection* connection2 = NULL;
            try {
                connection2 = worker::createTCPConnectionTo("127.0.0.1", 20000);
                connection2->start();
            } catch (string &/*s*/) {
                exceptionCaught = true;
                delete connection2;
            }

            TS_ASSERT(exceptionCaught);
            TS_ASSERT(!am2.CALLWAITER_onNewConnection.wasCalled());
        }

};

class TCPAcceptorTestsuite : public CxxTest::TestSuite
{
    public:
        void testAccept()
        {
            #ifdef WIN32
                clog << endl << "TCPAcceptorTestsuite::testAccept using NetworkLibraryWin32" << endl;
                TCPAcceptorTests
                <
                     core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryWin32>
                >::acceptTest();
            #endif

            #ifndef WIN32
                clog << endl << "TCPAcceptorTestsuite::testAccept using NetworkLibraryPosix" << endl;
                TCPAcceptorTests
                <
                    core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryPosix>
                >::acceptTest();
            #endif
        }

        void testMultipleAccept()
        {
            #ifdef WIN32
                clog << endl << "TCPAcceptorTestsuite::testMultipleAccept using NetworkLibraryWin32" << endl;
                TCPAcceptorTests
                <
                     core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryWin32>
                >::multipleAcceptTest();
            #endif

            #ifndef WIN32
                clog << endl << "TCPAcceptorTestsuite::testMultipleAccept using NetworkLibraryPosix" << endl;
                TCPAcceptorTests
                <
                    core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryPosix>
                >::multipleAcceptTest();
            #endif
        }

        void testNoAccept()
        {
            #ifdef WIN32
                clog << endl << "TCPAcceptorTestsuite::testNoAccept using NetworkLibraryWin32" << endl;
                TCPAcceptorTests
                <
                     core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryWin32>
                >::noAcceptTest();
            #endif

            #ifndef WIN32
                clog << endl << "TCPAcceptorTestsuite::testNoAccept using NetworkLibraryPosix" << endl;
                TCPAcceptorTests
                <
                    core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryPosix>
                >::noAcceptTest();
            #endif
        }
};

template <typename worker> struct TCPConnectionTests
{
    static void transferTest()
    {
        mocks::TCPAcceptorListenerMock am;

        auto_ptr<wrapper::TCPAcceptor> acceptor(worker::createTCPAcceptor(20000));
        acceptor->setAcceptorListener(&am);
        acceptor->start();

        auto_ptr<wrapper::TCPConnection> connection(worker::createTCPConnectionTo("127.0.0.1", 20000));
        connection->start();

        TS_ASSERT(am.CALLWAITER_onNewConnection.wait());
        am.getConnection()->start();

        //Prepare StringListenerMock for connected TCPConnection
        mocks::StringListenerMock stmConnection;
        stmConnection.VALUES_nextString.addItem("TRANSFER ACCEPTED->CONNECTED");
        stmConnection.VALUES_nextString.prepare();
        connection->setStringListener(&stmConnection);

        //Prepare StringListenerMock for accepted TCPConnection
        mocks::StringListenerMock stmAcceptedConnection;
        stmAcceptedConnection.VALUES_nextString.addItem("TRANSFER CONNECTED->ACCEPTED");
        stmAcceptedConnection.VALUES_nextString.prepare();
        am.getConnection()->setStringListener(&stmAcceptedConnection);

        cerr << "Sending from connected to accepted TCPConnection..." << endl;
        connection->send("TRANSFER CONNECTED->ACCEPTED");

        TS_ASSERT( stmAcceptedConnection.CALLWAITER_nextString.wait() );
        TS_ASSERT( stmAcceptedConnection.correctCalled() );
        TS_ASSERT( !stmConnection.CALLWAITER_nextString.wasCalled() );
        stmAcceptedConnection.CALLWAITER_nextString.reset();

        cerr << "Sending from accepted to connected TCPConnection..." << endl;
        am.getConnection()->send("TRANSFER ACCEPTED->CONNECTED");

        TS_ASSERT( stmConnection.CALLWAITER_nextString.wait() );
        TS_ASSERT( stmConnection.correctCalled() );
        TS_ASSERT( !stmAcceptedConnection.CALLWAITER_nextString.wasCalled() );
        stmAcceptedConnection.CALLWAITER_nextString.reset();
    }

    static void errorTest() {
        bool failed = true;
        try {
            mocks::TCPAcceptorListenerMock acceptorListenerMock1;

            auto_ptr<wrapper::TCPAcceptor> acceptor(worker::createTCPAcceptor(20000));
            acceptor->setAcceptorListener(&acceptorListenerMock1);
            acceptor->start();

            // 1. Case: Remove accepted part of connection.
            auto_ptr<wrapper::TCPConnection> connection1(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection1->start();

            TS_ASSERT(acceptorListenerMock1.CALLWAITER_onNewConnection.wait());
            acceptorListenerMock1.getConnection()->start();

            mocks::ConnectionListenerMock connectionListenerMock1;
            connection1->setConnectionListener(&connectionListenerMock1);
            delete acceptorListenerMock1.getConnection();
            acceptorListenerMock1.dontDeleteConnection();

            TS_ASSERT(connectionListenerMock1.CALLWAITER_handleConnectionError.wait());

            // 2. Case: Remove connecting part of connection.
            mocks::TCPAcceptorListenerMock acceptorListenerMock2;
            acceptor->setAcceptorListener(&acceptorListenerMock2);
            wrapper::TCPConnection* connection2(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection2->start();

            TS_ASSERT(acceptorListenerMock2.CALLWAITER_onNewConnection.wait());
            acceptorListenerMock2.getConnection()->start();

            mocks::ConnectionListenerMock connectionListenerMock2;
            acceptorListenerMock2.getConnection()->setConnectionListener(&connectionListenerMock2);
            delete connection2;

            TS_ASSERT(connectionListenerMock2.CALLWAITER_handleConnectionError.wait());
            failed = false;
        } catch (string &s) {
            TS_WARN(s);
            failed = true;
        } catch (...) {
            TS_WARN("Undefined error.");
            failed = true;
        }
        TS_ASSERT(!failed);
    }
};

class TCPConnectionTestSuite  : public CxxTest::TestSuite
{
    public:
        void testTransfer()
        {
            #ifdef WIN32
                clog << endl << "TCPConnectionTestSuite::testTransfer using NetworkLibraryWin32" << endl;
                TCPConnectionTests
                <
                     core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryWin32>
                >::transferTest();
            #endif

            #ifndef WIN32
                clog << endl << "TCPConnectionTestSuite::testTransfer using NetworkLibraryPosix" << endl;
                TCPConnectionTests
                <
                     core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryPosix>
                >::transferTest();
            #endif
        }

        void testError()
        {
            #ifdef WIN32
                clog << endl << "TCPConnectionTestSuite::testError using NetworkLibraryWin32" << endl;
                TCPConnectionTests
                <
                     core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryWin32>
                >::errorTest();
            #endif

            #ifndef WIN32
                clog << endl << "TCPConnectionTestSuite::testError using NetworkLibraryPosix" << endl;
                TCPConnectionTests
                <
                     core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryPosix>
                >::errorTest();
            #endif
        }
};

class TCPGathererTestSuite : public CxxTest::TestSuite, public wrapper::TCPConnection
{
    public:
		TCPGathererTestSuite() :
			m_sentData("") {}

        virtual void sendImplementation(const string& data)
        {
            m_sentData = data;
        }

        virtual void start()
        {}

        virtual void stop()
        {}

        /**
         * 1. Test Case: Received data corresponds to an entire packet.
         */
        void testNoGathering()
        {
            clog << endl << "TCPConnectionTestSuite::testNoGathering" << endl;
            const string testData = createTestData("The test data");

			mocks::StringListenerMock mockListener;
            setStringListener(&mockListener);
            mockListener.VALUES_nextString.addItem("The test data");
            mockListener.VALUES_nextString.prepare();

            receivedString(testData);

            TS_ASSERT( mockListener.CALLWAITER_nextString.wait() );
            TS_ASSERT( mockListener.correctCalled() );
        }

        /**
         * 2. Case: Data is split into two parts.
         */
        void testGathering()
        {
            clog << endl << "TCPConnectionTestSuite::testGathering" << endl;
            const string testData = createTestData("The test data");

            // Prepare StringListenerMock
            mocks::StringListenerMock mockListener;
            setStringListener(&mockListener);
            mockListener.VALUES_nextString.addItem("The test data");
            mockListener.VALUES_nextString.prepare();

            const string dataString1 = testData.substr(0, testData.length()/2);
            const string dataString2 = testData.substr(testData.length()/2);

            receivedString(dataString1);
            TS_ASSERT( !mockListener.CALLWAITER_nextString.wait() );

            receivedString(dataString2);
            TS_ASSERT( mockListener.CALLWAITER_nextString.wait() );
            TS_ASSERT( mockListener.correctCalled() );
        }

        /**
         * 3. Test case: Test data is split and mixed.
         */
        void testMixedGathering()
        {
            clog << endl << "TCPConnectionTestSuite::testMixedGathering" << endl;
            stringstream dataStream;

            const string data1("The first test data");
            const string data2("The second test data");

            const string testData1 = createTestData(data1);
            const string testData2 = createTestData(data2);

            // Prepare StringListenerMock
            mocks::StringListenerMock mockListener;
            setStringListener(&mockListener);
            mockListener.VALUES_nextString.addItem(data1);
            mockListener.VALUES_nextString.addItem(data2);
            mockListener.VALUES_nextString.prepare();

            const string dataString1 = testData1 + testData2.substr(0, testData2.length()/2);
            const string dataString2 = testData2.substr(testData2.length()/2);

            receivedString(dataString1);
            TS_ASSERT( mockListener.CALLWAITER_nextString.wait() );
            TS_ASSERT( mockListener.correctCalled());
            mockListener.CALLWAITER_nextString.reset();

            receivedString(dataString2);
            TS_ASSERT( mockListener.CALLWAITER_nextString.wait() );
            TS_ASSERT( mockListener.correctCalled() );
        }


	    unsigned long my_htonl(uint32_t n)
	    {
                unsigned char *s = (unsigned char *)&n;
                return (unsigned long)(s[0] << 24 | s[1] << 16 | s[2] << 8 | s[3]);
	    }

        string createTestData(const string& data)
        {
            const uint32_t dataSize = my_htonl(data.length());
            stringstream dataStream;
            dataStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32_t));
            dataStream << data;

            return dataStream.str();
        }

    private:
        string m_sentData;
};

#endif /*CORE_WRAPPER_TCPTESTSUITE_H_*/

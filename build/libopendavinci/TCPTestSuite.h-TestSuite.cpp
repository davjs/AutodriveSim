/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/XmlFilePrinter.h>

int main() {
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/TCPTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/TCPTestSuite.h"

static TCPAcceptorTestsuite suite_TCPAcceptorTestsuite;

static CxxTest::List Tests_TCPAcceptorTestsuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TCPAcceptorTestsuite( "/home/david/AutoDriveSim2/libopendavinci/testsuites/TCPTestSuite.h", 122, "TCPAcceptorTestsuite", suite_TCPAcceptorTestsuite, Tests_TCPAcceptorTestsuite );

static class TestDescription_TCPAcceptorTestsuite_testAccept : public CxxTest::RealTestDescription {
public:
 TestDescription_TCPAcceptorTestsuite_testAccept() : CxxTest::RealTestDescription( Tests_TCPAcceptorTestsuite, suiteDescription_TCPAcceptorTestsuite, 125, "testAccept" ) {}
 void runTest() { suite_TCPAcceptorTestsuite.testAccept(); }
} testDescription_TCPAcceptorTestsuite_testAccept;

static class TestDescription_TCPAcceptorTestsuite_testMultipleAccept : public CxxTest::RealTestDescription {
public:
 TestDescription_TCPAcceptorTestsuite_testMultipleAccept() : CxxTest::RealTestDescription( Tests_TCPAcceptorTestsuite, suiteDescription_TCPAcceptorTestsuite, 144, "testMultipleAccept" ) {}
 void runTest() { suite_TCPAcceptorTestsuite.testMultipleAccept(); }
} testDescription_TCPAcceptorTestsuite_testMultipleAccept;

static class TestDescription_TCPAcceptorTestsuite_testNoAccept : public CxxTest::RealTestDescription {
public:
 TestDescription_TCPAcceptorTestsuite_testNoAccept() : CxxTest::RealTestDescription( Tests_TCPAcceptorTestsuite, suiteDescription_TCPAcceptorTestsuite, 163, "testNoAccept" ) {}
 void runTest() { suite_TCPAcceptorTestsuite.testNoAccept(); }
} testDescription_TCPAcceptorTestsuite_testNoAccept;

static TCPConnectionTestSuite suite_TCPConnectionTestSuite;

static CxxTest::List Tests_TCPConnectionTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TCPConnectionTestSuite( "/home/david/AutoDriveSim2/libopendavinci/testsuites/TCPTestSuite.h", 277, "TCPConnectionTestSuite", suite_TCPConnectionTestSuite, Tests_TCPConnectionTestSuite );

static class TestDescription_TCPConnectionTestSuite_testTransfer : public CxxTest::RealTestDescription {
public:
 TestDescription_TCPConnectionTestSuite_testTransfer() : CxxTest::RealTestDescription( Tests_TCPConnectionTestSuite, suiteDescription_TCPConnectionTestSuite, 280, "testTransfer" ) {}
 void runTest() { suite_TCPConnectionTestSuite.testTransfer(); }
} testDescription_TCPConnectionTestSuite_testTransfer;

static class TestDescription_TCPConnectionTestSuite_testError : public CxxTest::RealTestDescription {
public:
 TestDescription_TCPConnectionTestSuite_testError() : CxxTest::RealTestDescription( Tests_TCPConnectionTestSuite, suiteDescription_TCPConnectionTestSuite, 299, "testError" ) {}
 void runTest() { suite_TCPConnectionTestSuite.testError(); }
} testDescription_TCPConnectionTestSuite_testError;

static TCPGathererTestSuite suite_TCPGathererTestSuite;

static CxxTest::List Tests_TCPGathererTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TCPGathererTestSuite( "/home/david/AutoDriveSim2/libopendavinci/testsuites/TCPTestSuite.h", 319, "TCPGathererTestSuite", suite_TCPGathererTestSuite, Tests_TCPGathererTestSuite );

static class TestDescription_TCPGathererTestSuite_testNoGathering : public CxxTest::RealTestDescription {
public:
 TestDescription_TCPGathererTestSuite_testNoGathering() : CxxTest::RealTestDescription( Tests_TCPGathererTestSuite, suiteDescription_TCPGathererTestSuite, 339, "testNoGathering" ) {}
 void runTest() { suite_TCPGathererTestSuite.testNoGathering(); }
} testDescription_TCPGathererTestSuite_testNoGathering;

static class TestDescription_TCPGathererTestSuite_testGathering : public CxxTest::RealTestDescription {
public:
 TestDescription_TCPGathererTestSuite_testGathering() : CxxTest::RealTestDescription( Tests_TCPGathererTestSuite, suiteDescription_TCPGathererTestSuite, 358, "testGathering" ) {}
 void runTest() { suite_TCPGathererTestSuite.testGathering(); }
} testDescription_TCPGathererTestSuite_testGathering;

static class TestDescription_TCPGathererTestSuite_testMixedGathering : public CxxTest::RealTestDescription {
public:
 TestDescription_TCPGathererTestSuite_testMixedGathering() : CxxTest::RealTestDescription( Tests_TCPGathererTestSuite, suiteDescription_TCPGathererTestSuite, 383, "testMixedGathering" ) {}
 void runTest() { suite_TCPGathererTestSuite.testMixedGathering(); }
} testDescription_TCPGathererTestSuite_testMixedGathering;

#include <cxxtest/Root.cpp>

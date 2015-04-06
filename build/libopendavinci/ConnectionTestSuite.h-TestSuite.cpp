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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/ConnectionTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/ConnectionTestSuite.h"

static ConnectionTestsuite suite_ConnectionTestsuite;

static CxxTest::List Tests_ConnectionTestsuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ConnectionTestsuite( "/home/david/AutoDriveSim2/libopendavinci/testsuites/ConnectionTestSuite.h", 51, "ConnectionTestsuite", suite_ConnectionTestsuite, Tests_ConnectionTestsuite );

static class TestDescription_ConnectionTestsuite_testAcceptAndConnect : public CxxTest::RealTestDescription {
public:
 TestDescription_ConnectionTestsuite_testAcceptAndConnect() : CxxTest::RealTestDescription( Tests_ConnectionTestsuite, suiteDescription_ConnectionTestsuite, 53, "testAcceptAndConnect" ) {}
 void runTest() { suite_ConnectionTestsuite.testAcceptAndConnect(); }
} testDescription_ConnectionTestsuite_testAcceptAndConnect;

static class TestDescription_ConnectionTestsuite_testErrorHandler : public CxxTest::RealTestDescription {
public:
 TestDescription_ConnectionTestsuite_testErrorHandler() : CxxTest::RealTestDescription( Tests_ConnectionTestsuite, suiteDescription_ConnectionTestsuite, 102, "testErrorHandler" ) {}
 void runTest() { suite_ConnectionTestsuite.testErrorHandler(); }
} testDescription_ConnectionTestsuite_testErrorHandler;

static class TestDescription_ConnectionTestsuite_testTransfer : public CxxTest::RealTestDescription {
public:
 TestDescription_ConnectionTestsuite_testTransfer() : CxxTest::RealTestDescription( Tests_ConnectionTestsuite, suiteDescription_ConnectionTestsuite, 133, "testTransfer" ) {}
 void runTest() { suite_ConnectionTestsuite.testTransfer(); }
} testDescription_ConnectionTestsuite_testTransfer;

#include <cxxtest/Root.cpp>

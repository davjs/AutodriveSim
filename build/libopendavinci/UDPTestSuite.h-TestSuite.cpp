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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/UDPTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/UDPTestSuite.h"

static UDPTestsuite suite_UDPTestsuite;

static CxxTest::List Tests_UDPTestsuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_UDPTestsuite( "/home/david/AutoDriveSim2/libopendavinci/testsuites/UDPTestSuite.h", 113, "UDPTestsuite", suite_UDPTestsuite, Tests_UDPTestsuite );

static class TestDescription_UDPTestsuite_testDataExchange : public CxxTest::RealTestDescription {
public:
 TestDescription_UDPTestsuite_testDataExchange() : CxxTest::RealTestDescription( Tests_UDPTestsuite, suiteDescription_UDPTestsuite, 116, "testDataExchange" ) {}
 void runTest() { suite_UDPTestsuite.testDataExchange(); }
} testDescription_UDPTestsuite_testDataExchange;

#include <cxxtest/Root.cpp>

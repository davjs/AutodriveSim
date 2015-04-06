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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/DMCPConnectionTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/DMCPConnectionTestSuite.h"

static DMCPConnectionTestsuite suite_DMCPConnectionTestsuite;

static CxxTest::List Tests_DMCPConnectionTestsuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DMCPConnectionTestsuite( "/home/david/AutoDriveSim2/libopendavinci/testsuites/DMCPConnectionTestSuite.h", 51, "DMCPConnectionTestsuite", suite_DMCPConnectionTestsuite, Tests_DMCPConnectionTestsuite );

static class TestDescription_DMCPConnectionTestsuite_testClientAndServer : public CxxTest::RealTestDescription {
public:
 TestDescription_DMCPConnectionTestsuite_testClientAndServer() : CxxTest::RealTestDescription( Tests_DMCPConnectionTestsuite, suiteDescription_DMCPConnectionTestsuite, 64, "testClientAndServer" ) {}
 void runTest() { suite_DMCPConnectionTestsuite.testClientAndServer(); }
} testDescription_DMCPConnectionTestsuite_testClientAndServer;

#include <cxxtest/Root.cpp>

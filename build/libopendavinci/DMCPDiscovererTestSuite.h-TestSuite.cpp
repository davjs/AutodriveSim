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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/DMCPDiscovererTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/DMCPDiscovererTestSuite.h"

static DMCPDiscovererTestsuite suite_DMCPDiscovererTestsuite;

static CxxTest::List Tests_DMCPDiscovererTestsuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DMCPDiscovererTestsuite( "/home/david/AutoDriveSim2/libopendavinci/testsuites/DMCPDiscovererTestSuite.h", 74, "DMCPDiscovererTestsuite", suite_DMCPDiscovererTestsuite, Tests_DMCPDiscovererTestsuite );

static class TestDescription_DMCPDiscovererTestsuite_testClientAndServer : public CxxTest::RealTestDescription {
public:
 TestDescription_DMCPDiscovererTestsuite_testClientAndServer() : CxxTest::RealTestDescription( Tests_DMCPDiscovererTestsuite, suiteDescription_DMCPDiscovererTestsuite, 78, "testClientAndServer" ) {}
 void runTest() { suite_DMCPDiscovererTestsuite.testClientAndServer(); }
} testDescription_DMCPDiscovererTestsuite_testClientAndServer;

#include <cxxtest/Root.cpp>

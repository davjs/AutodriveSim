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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/apps/driver/DriverTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/apps/driver/testsuites/DriverTestSuite.h"

static DriverTest suite_DriverTest;

static CxxTest::List Tests_DriverTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DriverTest( "/home/david/AutoDriveSim2/apps/driver/testsuites/DriverTestSuite.h", 49, "DriverTest", suite_DriverTest, Tests_DriverTest );

static class TestDescription_DriverTest_testDriverSuccessfullyCreated : public CxxTest::RealTestDescription {
public:
 TestDescription_DriverTest_testDriverSuccessfullyCreated() : CxxTest::RealTestDescription( Tests_DriverTest, suiteDescription_DriverTest, 83, "testDriverSuccessfullyCreated" ) {}
 void runTest() { suite_DriverTest.testDriverSuccessfullyCreated(); }
} testDescription_DriverTest_testDriverSuccessfullyCreated;

#include <cxxtest/Root.cpp>

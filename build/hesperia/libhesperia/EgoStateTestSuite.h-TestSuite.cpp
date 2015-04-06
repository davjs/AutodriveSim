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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/hesperia/libhesperia/EgoStateTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/EgoStateTestSuite.h"

static EgoStateTest suite_EgoStateTest;

static CxxTest::List Tests_EgoStateTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EgoStateTest( "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/EgoStateTestSuite.h", 35, "EgoStateTest", suite_EgoStateTest, Tests_EgoStateTest );

static class TestDescription_EgoStateTest_testEgoState : public CxxTest::RealTestDescription {
public:
 TestDescription_EgoStateTest_testEgoState() : CxxTest::RealTestDescription( Tests_EgoStateTest, suiteDescription_EgoStateTest, 37, "testEgoState" ) {}
 void runTest() { suite_EgoStateTest.testEgoState(); }
} testDescription_EgoStateTest_testEgoState;

#include <cxxtest/Root.cpp>

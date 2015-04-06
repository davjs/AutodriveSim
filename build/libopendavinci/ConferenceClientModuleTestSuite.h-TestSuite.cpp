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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/ConferenceClientModuleTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/ConferenceClientModuleTestSuite.h"

static ConferenceClientModuleTest suite_ConferenceClientModuleTest;

static CxxTest::List Tests_ConferenceClientModuleTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ConferenceClientModuleTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/ConferenceClientModuleTestSuite.h", 133, "ConferenceClientModuleTest", suite_ConferenceClientModuleTest, Tests_ConferenceClientModuleTest );

static class TestDescription_ConferenceClientModuleTest_testConferenceClientModule : public CxxTest::RealTestDescription {
public:
 TestDescription_ConferenceClientModuleTest_testConferenceClientModule() : CxxTest::RealTestDescription( Tests_ConferenceClientModuleTest, suiteDescription_ConferenceClientModuleTest, 152, "testConferenceClientModule" ) {}
 void runTest() { suite_ConferenceClientModuleTest.testConferenceClientModule(); }
} testDescription_ConferenceClientModuleTest_testConferenceClientModule;

#include <cxxtest/Root.cpp>

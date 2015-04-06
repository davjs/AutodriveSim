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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/ConferenceFactoryTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/ConferenceFactoryTestSuite.h"

static ConferenceFactoryTest suite_ConferenceFactoryTest;

static CxxTest::List Tests_ConferenceFactoryTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ConferenceFactoryTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/ConferenceFactoryTestSuite.h", 83, "ConferenceFactoryTest", suite_ConferenceFactoryTest, Tests_ConferenceFactoryTest );

static class TestDescription_ConferenceFactoryTest_testControlledContainerFactoryTestSuite : public CxxTest::RealTestDescription {
public:
 TestDescription_ConferenceFactoryTest_testControlledContainerFactoryTestSuite() : CxxTest::RealTestDescription( Tests_ConferenceFactoryTest, suiteDescription_ConferenceFactoryTest, 85, "testControlledContainerFactoryTestSuite" ) {}
 void runTest() { suite_ConferenceFactoryTest.testControlledContainerFactoryTestSuite(); }
} testDescription_ConferenceFactoryTest_testControlledContainerFactoryTestSuite;

#include <cxxtest/Root.cpp>

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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/ClockTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/ClockTestSuite.h"

static ClockTest suite_ClockTest;

static CxxTest::List Tests_ClockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ClockTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/ClockTestSuite.h", 34, "ClockTest", suite_ClockTest, Tests_ClockTest );

static class TestDescription_ClockTest_testClock : public CxxTest::RealTestDescription {
public:
 TestDescription_ClockTest_testClock() : CxxTest::RealTestDescription( Tests_ClockTest, suiteDescription_ClockTest, 36, "testClock" ) {}
 void runTest() { suite_ClockTest.testClock(); }
} testDescription_ClockTest_testClock;

static class TestDescription_ClockTest_testCopyClock : public CxxTest::RealTestDescription {
public:
 TestDescription_ClockTest_testCopyClock() : CxxTest::RealTestDescription( Tests_ClockTest, suiteDescription_ClockTest, 80, "testCopyClock" ) {}
 void runTest() { suite_ClockTest.testCopyClock(); }
} testDescription_ClockTest_testCopyClock;

#include <cxxtest/Root.cpp>

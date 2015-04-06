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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/TimeFactoryTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/TimeFactoryTestSuite.h"

static TimeFactoryTest suite_TimeFactoryTest;

static CxxTest::List Tests_TimeFactoryTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TimeFactoryTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/TimeFactoryTestSuite.h", 49, "TimeFactoryTest", suite_TimeFactoryTest, Tests_TimeFactoryTest );

static class TestDescription_TimeFactoryTest_testCopyControlledTime : public CxxTest::RealTestDescription {
public:
 TestDescription_TimeFactoryTest_testCopyControlledTime() : CxxTest::RealTestDescription( Tests_TimeFactoryTest, suiteDescription_TimeFactoryTest, 51, "testCopyControlledTime" ) {}
 void runTest() { suite_TimeFactoryTest.testCopyControlledTime(); }
} testDescription_TimeFactoryTest_testCopyControlledTime;

static class TestDescription_TimeFactoryTest_testControlledTimeFactoryTestSuite : public CxxTest::RealTestDescription {
public:
 TestDescription_TimeFactoryTest_testControlledTimeFactoryTestSuite() : CxxTest::RealTestDescription( Tests_TimeFactoryTest, suiteDescription_TimeFactoryTest, 64, "testControlledTimeFactoryTestSuite" ) {}
 void runTest() { suite_TimeFactoryTest.testControlledTimeFactoryTestSuite(); }
} testDescription_TimeFactoryTest_testControlledTimeFactoryTestSuite;

#include <cxxtest/Root.cpp>

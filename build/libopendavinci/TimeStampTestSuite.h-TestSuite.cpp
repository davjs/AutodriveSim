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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/TimeStampTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/TimeStampTestSuite.h"

static TimeStampTest suite_TimeStampTest;

static CxxTest::List Tests_TimeStampTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TimeStampTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/TimeStampTestSuite.h", 34, "TimeStampTest", suite_TimeStampTest, Tests_TimeStampTest );

static class TestDescription_TimeStampTest_testAdd1 : public CxxTest::RealTestDescription {
public:
 TestDescription_TimeStampTest_testAdd1() : CxxTest::RealTestDescription( Tests_TimeStampTest, suiteDescription_TimeStampTest, 36, "testAdd1" ) {}
 void runTest() { suite_TimeStampTest.testAdd1(); }
} testDescription_TimeStampTest_testAdd1;

static class TestDescription_TimeStampTest_testAdd2 : public CxxTest::RealTestDescription {
public:
 TestDescription_TimeStampTest_testAdd2() : CxxTest::RealTestDescription( Tests_TimeStampTest, suiteDescription_TimeStampTest, 45, "testAdd2" ) {}
 void runTest() { suite_TimeStampTest.testAdd2(); }
} testDescription_TimeStampTest_testAdd2;

static class TestDescription_TimeStampTest_testSub1 : public CxxTest::RealTestDescription {
public:
 TestDescription_TimeStampTest_testSub1() : CxxTest::RealTestDescription( Tests_TimeStampTest, suiteDescription_TimeStampTest, 54, "testSub1" ) {}
 void runTest() { suite_TimeStampTest.testSub1(); }
} testDescription_TimeStampTest_testSub1;

static class TestDescription_TimeStampTest_testSub2 : public CxxTest::RealTestDescription {
public:
 TestDescription_TimeStampTest_testSub2() : CxxTest::RealTestDescription( Tests_TimeStampTest, suiteDescription_TimeStampTest, 63, "testSub2" ) {}
 void runTest() { suite_TimeStampTest.testSub2(); }
} testDescription_TimeStampTest_testSub2;

static class TestDescription_TimeStampTest_testTimeStamp28042009 : public CxxTest::RealTestDescription {
public:
 TestDescription_TimeStampTest_testTimeStamp28042009() : CxxTest::RealTestDescription( Tests_TimeStampTest, suiteDescription_TimeStampTest, 72, "testTimeStamp28042009" ) {}
 void runTest() { suite_TimeStampTest.testTimeStamp28042009(); }
} testDescription_TimeStampTest_testTimeStamp28042009;

#include <cxxtest/Root.cpp>

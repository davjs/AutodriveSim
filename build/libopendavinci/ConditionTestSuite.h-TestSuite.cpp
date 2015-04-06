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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/ConditionTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/ConditionTestSuite.h"

static ConditionTest suite_ConditionTest;

static CxxTest::List Tests_ConditionTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ConditionTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/ConditionTestSuite.h", 105, "ConditionTest", suite_ConditionTest, Tests_ConditionTest );

static class TestDescription_ConditionTest_testLocking : public CxxTest::RealTestDescription {
public:
 TestDescription_ConditionTest_testLocking() : CxxTest::RealTestDescription( Tests_ConditionTest, suiteDescription_ConditionTest, 107, "testLocking" ) {}
 void runTest() { suite_ConditionTest.testLocking(); }
} testDescription_ConditionTest_testLocking;

static class TestDescription_ConditionTest_testWakeOne : public CxxTest::RealTestDescription {
public:
 TestDescription_ConditionTest_testWakeOne() : CxxTest::RealTestDescription( Tests_ConditionTest, suiteDescription_ConditionTest, 120, "testWakeOne" ) {}
 void runTest() { suite_ConditionTest.testWakeOne(); }
} testDescription_ConditionTest_testWakeOne;

static class TestDescription_ConditionTest_testWakeAll : public CxxTest::RealTestDescription {
public:
 TestDescription_ConditionTest_testWakeAll() : CxxTest::RealTestDescription( Tests_ConditionTest, suiteDescription_ConditionTest, 156, "testWakeAll" ) {}
 void runTest() { suite_ConditionTest.testWakeAll(); }
} testDescription_ConditionTest_testWakeAll;

static class TestDescription_ConditionTest_testTimeCondition : public CxxTest::RealTestDescription {
public:
 TestDescription_ConditionTest_testTimeCondition() : CxxTest::RealTestDescription( Tests_ConditionTest, suiteDescription_ConditionTest, 196, "testTimeCondition" ) {}
 void runTest() { suite_ConditionTest.testTimeCondition(); }
} testDescription_ConditionTest_testTimeCondition;

#include <cxxtest/Root.cpp>

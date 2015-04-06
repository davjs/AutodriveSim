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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/RuntimeControlContainerTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/RuntimeControlContainerTestSuite.h"

static RuntimeControlContainerTest suite_RuntimeControlContainerTest;

static CxxTest::List Tests_RuntimeControlContainerTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RuntimeControlContainerTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/RuntimeControlContainerTestSuite.h", 210, "RuntimeControlContainerTest", suite_RuntimeControlContainerTest, Tests_RuntimeControlContainerTest );

static class TestDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingNotSending : public CxxTest::RealTestDescription {
public:
 TestDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingNotSending() : CxxTest::RealTestDescription( Tests_RuntimeControlContainerTest, suiteDescription_RuntimeControlContainerTest, 212, "testRuntimeControlContainerRegularRunReceivingNotSending" ) {}
 void runTest() { suite_RuntimeControlContainerTest.testRuntimeControlContainerRegularRunReceivingNotSending(); }
} testDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingNotSending;

static class TestDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingSending : public CxxTest::RealTestDescription {
public:
 TestDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingSending() : CxxTest::RealTestDescription( Tests_RuntimeControlContainerTest, suiteDescription_RuntimeControlContainerTest, 276, "testRuntimeControlContainerRegularRunReceivingSending" ) {}
 void runTest() { suite_RuntimeControlContainerTest.testRuntimeControlContainerRegularRunReceivingSending(); }
} testDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingSending;

static class TestDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingSendingAppTwiceAsFastAsSC : public CxxTest::RealTestDescription {
public:
 TestDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingSendingAppTwiceAsFastAsSC() : CxxTest::RealTestDescription( Tests_RuntimeControlContainerTest, suiteDescription_RuntimeControlContainerTest, 354, "testRuntimeControlContainerRegularRunReceivingSendingAppTwiceAsFastAsSC" ) {}
 void runTest() { suite_RuntimeControlContainerTest.testRuntimeControlContainerRegularRunReceivingSendingAppTwiceAsFastAsSC(); }
} testDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingSendingAppTwiceAsFastAsSC;

static class TestDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingSendingAppHalfAsFastAsSC : public CxxTest::RealTestDescription {
public:
 TestDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingSendingAppHalfAsFastAsSC() : CxxTest::RealTestDescription( Tests_RuntimeControlContainerTest, suiteDescription_RuntimeControlContainerTest, 432, "testRuntimeControlContainerRegularRunReceivingSendingAppHalfAsFastAsSC" ) {}
 void runTest() { suite_RuntimeControlContainerTest.testRuntimeControlContainerRegularRunReceivingSendingAppHalfAsFastAsSC(); }
} testDescription_RuntimeControlContainerTest_testRuntimeControlContainerRegularRunReceivingSendingAppHalfAsFastAsSC;

#include <cxxtest/Root.cpp>

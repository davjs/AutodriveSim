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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/RuntimeControlTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/RuntimeControlTestSuite.h"

static RuntimeControlTest suite_RuntimeControlTest;

static CxxTest::List Tests_RuntimeControlTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RuntimeControlTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/RuntimeControlTestSuite.h", 104, "RuntimeControlTest", suite_RuntimeControlTest, Tests_RuntimeControlTest );

static class TestDescription_RuntimeControlTest_testRuntimeControlRegularRun : public CxxTest::RealTestDescription {
public:
 TestDescription_RuntimeControlTest_testRuntimeControlRegularRun() : CxxTest::RealTestDescription( Tests_RuntimeControlTest, suiteDescription_RuntimeControlTest, 106, "testRuntimeControlRegularRun" ) {}
 void runTest() { suite_RuntimeControlTest.testRuntimeControlRegularRun(); }
} testDescription_RuntimeControlTest_testRuntimeControlRegularRun;

static class TestDescription_RuntimeControlTest_testRuntimeControlSpecializedConfigurationRegularRun : public CxxTest::RealTestDescription {
public:
 TestDescription_RuntimeControlTest_testRuntimeControlSpecializedConfigurationRegularRun() : CxxTest::RealTestDescription( Tests_RuntimeControlTest, suiteDescription_RuntimeControlTest, 166, "testRuntimeControlSpecializedConfigurationRegularRun" ) {}
 void runTest() { suite_RuntimeControlTest.testRuntimeControlSpecializedConfigurationRegularRun(); }
} testDescription_RuntimeControlTest_testRuntimeControlSpecializedConfigurationRegularRun;

static class TestDescription_RuntimeControlTest_testRuntimeControlCorruptConfigurationRun : public CxxTest::RealTestDescription {
public:
 TestDescription_RuntimeControlTest_testRuntimeControlCorruptConfigurationRun() : CxxTest::RealTestDescription( Tests_RuntimeControlTest, suiteDescription_RuntimeControlTest, 219, "testRuntimeControlCorruptConfigurationRun" ) {}
 void runTest() { suite_RuntimeControlTest.testRuntimeControlCorruptConfigurationRun(); }
} testDescription_RuntimeControlTest_testRuntimeControlCorruptConfigurationRun;

static class TestDescription_RuntimeControlTest_testRuntimeControlRegularRunNoSetupCalled : public CxxTest::RealTestDescription {
public:
 TestDescription_RuntimeControlTest_testRuntimeControlRegularRunNoSetupCalled() : CxxTest::RealTestDescription( Tests_RuntimeControlTest, suiteDescription_RuntimeControlTest, 265, "testRuntimeControlRegularRunNoSetupCalled" ) {}
 void runTest() { suite_RuntimeControlTest.testRuntimeControlRegularRunNoSetupCalled(); }
} testDescription_RuntimeControlTest_testRuntimeControlRegularRunNoSetupCalled;

#include <cxxtest/Root.cpp>

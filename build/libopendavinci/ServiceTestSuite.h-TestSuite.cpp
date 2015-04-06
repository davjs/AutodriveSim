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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/ServiceTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/ServiceTestSuite.h"

static ServiceTest suite_ServiceTest;

static CxxTest::List Tests_ServiceTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ServiceTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/ServiceTestSuite.h", 97, "ServiceTest", suite_ServiceTest, Tests_ServiceTest );

static class TestDescription_ServiceTest_testService : public CxxTest::RealTestDescription {
public:
 TestDescription_ServiceTest_testService() : CxxTest::RealTestDescription( Tests_ServiceTest, suiteDescription_ServiceTest, 116, "testService" ) {}
 void runTest() { suite_ServiceTest.testService(); }
} testDescription_ServiceTest_testService;

static class TestDescription_ServiceTest_testSeveralServices : public CxxTest::RealTestDescription {
public:
 TestDescription_ServiceTest_testSeveralServices() : CxxTest::RealTestDescription( Tests_ServiceTest, suiteDescription_ServiceTest, 135, "testSeveralServices" ) {}
 void runTest() { suite_ServiceTest.testSeveralServices(); }
} testDescription_ServiceTest_testSeveralServices;

#include <cxxtest/Root.cpp>

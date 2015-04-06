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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/tools/spy/SpyTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/tools/spy/testsuites/SpyTestSuite.h"

static SpyTest suite_SpyTest;

static CxxTest::List Tests_SpyTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SpyTest( "/home/david/AutoDriveSim2/tools/spy/testsuites/SpyTestSuite.h", 36, "SpyTest", suite_SpyTest, Tests_SpyTest );

static class TestDescription_SpyTest_testSpySuccessfullyCreated : public CxxTest::RealTestDescription {
public:
 TestDescription_SpyTest_testSpySuccessfullyCreated() : CxxTest::RealTestDescription( Tests_SpyTest, suiteDescription_SpyTest, 70, "testSpySuccessfullyCreated" ) {}
 void runTest() { suite_SpyTest.testSpySuccessfullyCreated(); }
} testDescription_SpyTest_testSpySuccessfullyCreated;

#include <cxxtest/Root.cpp>

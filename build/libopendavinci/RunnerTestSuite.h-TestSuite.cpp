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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/RunnerTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/RunnerTestSuite.h"

static RunnerTest suite_RunnerTest;

static CxxTest::List Tests_RunnerTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RunnerTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/RunnerTestSuite.h", 45, "RunnerTest", suite_RunnerTest, Tests_RunnerTest );

static class TestDescription_RunnerTest_testFrequencies : public CxxTest::RealTestDescription {
public:
 TestDescription_RunnerTest_testFrequencies() : CxxTest::RealTestDescription( Tests_RunnerTest, suiteDescription_RunnerTest, 47, "testFrequencies" ) {}
 void runTest() { suite_RunnerTest.testFrequencies(); }
} testDescription_RunnerTest_testFrequencies;

#include <cxxtest/Root.cpp>

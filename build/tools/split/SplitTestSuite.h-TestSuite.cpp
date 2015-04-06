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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/tools/split/SplitTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/tools/split/testsuites/SplitTestSuite.h"

static SplitTest suite_SplitTest;

static CxxTest::List Tests_SplitTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SplitTest( "/home/david/AutoDriveSim2/tools/split/testsuites/SplitTestSuite.h", 86, "SplitTest", suite_SplitTest, Tests_SplitTest );

static class TestDescription_SplitTest_testSplitSuccessfullySplit : public CxxTest::RealTestDescription {
public:
 TestDescription_SplitTest_testSplitSuccessfullySplit() : CxxTest::RealTestDescription( Tests_SplitTest, suiteDescription_SplitTest, 153, "testSplitSuccessfullySplit" ) {}
 void runTest() { suite_SplitTest.testSplitSuccessfullySplit(); }
} testDescription_SplitTest_testSplitSuccessfullySplit;

static class TestDescription_SplitTest_testSplitWrongRange : public CxxTest::RealTestDescription {
public:
 TestDescription_SplitTest_testSplitWrongRange() : CxxTest::RealTestDescription( Tests_SplitTest, suiteDescription_SplitTest, 268, "testSplitWrongRange" ) {}
 void runTest() { suite_SplitTest.testSplitWrongRange(); }
} testDescription_SplitTest_testSplitWrongRange;

#include <cxxtest/Root.cpp>

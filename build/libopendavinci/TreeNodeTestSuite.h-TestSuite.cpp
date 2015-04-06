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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/TreeNodeTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/TreeNodeTestSuite.h"

static TreeNodeTest suite_TreeNodeTest;

static CxxTest::List Tests_TreeNodeTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TreeNodeTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/TreeNodeTestSuite.h", 32, "TreeNodeTest", suite_TreeNodeTest, Tests_TreeNodeTest );

static class TestDescription_TreeNodeTest_testSimpleTree : public CxxTest::RealTestDescription {
public:
 TestDescription_TreeNodeTest_testSimpleTree() : CxxTest::RealTestDescription( Tests_TreeNodeTest, suiteDescription_TreeNodeTest, 51, "testSimpleTree" ) {}
 void runTest() { suite_TreeNodeTest.testSimpleTree(); }
} testDescription_TreeNodeTest_testSimpleTree;

#include <cxxtest/Root.cpp>

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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/ControlFlowTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/ControlFlowTestSuite.h"

static ControlFlowTest suite_ControlFlowTest;

static CxxTest::List Tests_ControlFlowTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ControlFlowTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/ControlFlowTestSuite.h", 262, "ControlFlowTest", suite_ControlFlowTest, Tests_ControlFlowTest );

static class TestDescription_ControlFlowTest_testControlledContainerFactoryTestSuite : public CxxTest::RealTestDescription {
public:
 TestDescription_ControlFlowTest_testControlledContainerFactoryTestSuite() : CxxTest::RealTestDescription( Tests_ControlFlowTest, suiteDescription_ControlFlowTest, 281, "testControlledContainerFactoryTestSuite" ) {}
 void runTest() { suite_ControlFlowTest.testControlledContainerFactoryTestSuite(); }
} testDescription_ControlFlowTest_testControlledContainerFactoryTestSuite;

#include <cxxtest/Root.cpp>

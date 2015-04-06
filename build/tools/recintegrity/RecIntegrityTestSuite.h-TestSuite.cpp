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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/tools/recintegrity/RecIntegrityTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/tools/recintegrity/testsuites/RecIntegrityTestSuite.h"

static RecIntegrityTest suite_RecIntegrityTest;

static CxxTest::List Tests_RecIntegrityTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RecIntegrityTest( "/home/david/AutoDriveSim2/tools/recintegrity/testsuites/RecIntegrityTestSuite.h", 49, "RecIntegrityTest", suite_RecIntegrityTest, Tests_RecIntegrityTest );

static class TestDescription_RecIntegrityTest_testRecIntegritySuccessfullyCreated : public CxxTest::RealTestDescription {
public:
 TestDescription_RecIntegrityTest_testRecIntegritySuccessfullyCreated() : CxxTest::RealTestDescription( Tests_RecIntegrityTest, suiteDescription_RecIntegrityTest, 83, "testRecIntegritySuccessfullyCreated" ) {}
 void runTest() { suite_RecIntegrityTest.testRecIntegritySuccessfullyCreated(); }
} testDescription_RecIntegrityTest_testRecIntegritySuccessfullyCreated;

#include <cxxtest/Root.cpp>

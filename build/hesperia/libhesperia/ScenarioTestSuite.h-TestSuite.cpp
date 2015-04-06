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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/hesperia/libhesperia/ScenarioTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/ScenarioTestSuite.h"

static ScenarioTest suite_ScenarioTest;

static CxxTest::List Tests_ScenarioTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ScenarioTest( "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/ScenarioTestSuite.h", 58, "ScenarioTest", suite_ScenarioTest, Tests_ScenarioTest );

static class TestDescription_ScenarioTest_testIDVertex3 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScenarioTest_testIDVertex3() : CxxTest::RealTestDescription( Tests_ScenarioTest, suiteDescription_ScenarioTest, 60, "testIDVertex3" ) {}
 void runTest() { suite_ScenarioTest.testIDVertex3(); }
} testDescription_ScenarioTest_testIDVertex3;

static class TestDescription_ScenarioTest_testParsingCorruptSCNGrammar : public CxxTest::RealTestDescription {
public:
 TestDescription_ScenarioTest_testParsingCorruptSCNGrammar() : CxxTest::RealTestDescription( Tests_ScenarioTest, suiteDescription_ScenarioTest, 74, "testParsingCorruptSCNGrammar" ) {}
 void runTest() { suite_ScenarioTest.testParsingCorruptSCNGrammar(); }
} testDescription_ScenarioTest_testParsingCorruptSCNGrammar;

static class TestDescription_ScenarioTest_testParsingSCNGrammar : public CxxTest::RealTestDescription {
public:
 TestDescription_ScenarioTest_testParsingSCNGrammar() : CxxTest::RealTestDescription( Tests_ScenarioTest, suiteDescription_ScenarioTest, 90, "testParsingSCNGrammar" ) {}
 void runTest() { suite_ScenarioTest.testParsingSCNGrammar(); }
} testDescription_ScenarioTest_testParsingSCNGrammar;

#include <cxxtest/Root.cpp>

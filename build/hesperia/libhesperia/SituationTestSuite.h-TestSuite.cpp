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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/hesperia/libhesperia/SituationTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/SituationTestSuite.h"

static SituationTest suite_SituationTest;

static CxxTest::List Tests_SituationTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SituationTest( "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/SituationTestSuite.h", 54, "SituationTest", suite_SituationTest, Tests_SituationTest );

static class TestDescription_SituationTest_testParsingCorruptSITGrammar : public CxxTest::RealTestDescription {
public:
 TestDescription_SituationTest_testParsingCorruptSITGrammar() : CxxTest::RealTestDescription( Tests_SituationTest, suiteDescription_SituationTest, 56, "testParsingCorruptSITGrammar" ) {}
 void runTest() { suite_SituationTest.testParsingCorruptSITGrammar(); }
} testDescription_SituationTest_testParsingCorruptSITGrammar;

static class TestDescription_SituationTest_testParsingSITGrammar : public CxxTest::RealTestDescription {
public:
 TestDescription_SituationTest_testParsingSITGrammar() : CxxTest::RealTestDescription( Tests_SituationTest, suiteDescription_SituationTest, 73, "testParsingSITGrammar" ) {}
 void runTest() { suite_SituationTest.testParsingSITGrammar(); }
} testDescription_SituationTest_testParsingSITGrammar;

#include <cxxtest/Root.cpp>

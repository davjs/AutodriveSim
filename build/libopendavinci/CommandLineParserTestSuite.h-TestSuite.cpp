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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/CommandLineParserTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/CommandLineParserTestSuite.h"

static CommandLineParserTestSuite suite_CommandLineParserTestSuite;

static CxxTest::List Tests_CommandLineParserTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CommandLineParserTestSuite( "/home/david/AutoDriveSim2/libopendavinci/testsuites/CommandLineParserTestSuite.h", 34, "CommandLineParserTestSuite", suite_CommandLineParserTestSuite, Tests_CommandLineParserTestSuite );

static class TestDescription_CommandLineParserTestSuite_testParse : public CxxTest::RealTestDescription {
public:
 TestDescription_CommandLineParserTestSuite_testParse() : CxxTest::RealTestDescription( Tests_CommandLineParserTestSuite, suiteDescription_CommandLineParserTestSuite, 36, "testParse" ) {}
 void runTest() { suite_CommandLineParserTestSuite.testParse(); }
} testDescription_CommandLineParserTestSuite_testParse;

static class TestDescription_CommandLineParserTestSuite_testParseSeveralArgumentFromSameKey : public CxxTest::RealTestDescription {
public:
 TestDescription_CommandLineParserTestSuite_testParseSeveralArgumentFromSameKey() : CxxTest::RealTestDescription( Tests_CommandLineParserTestSuite, suiteDescription_CommandLineParserTestSuite, 64, "testParseSeveralArgumentFromSameKey" ) {}
 void runTest() { suite_CommandLineParserTestSuite.testParseSeveralArgumentFromSameKey(); }
} testDescription_CommandLineParserTestSuite_testParseSeveralArgumentFromSameKey;

static class TestDescription_CommandLineParserTestSuite_testGetInvalidArgument : public CxxTest::RealTestDescription {
public:
 TestDescription_CommandLineParserTestSuite_testGetInvalidArgument() : CxxTest::RealTestDescription( Tests_CommandLineParserTestSuite, suiteDescription_CommandLineParserTestSuite, 104, "testGetInvalidArgument" ) {}
 void runTest() { suite_CommandLineParserTestSuite.testGetInvalidArgument(); }
} testDescription_CommandLineParserTestSuite_testGetInvalidArgument;

static class TestDescription_CommandLineParserTestSuite_testParseIncompleteArgument : public CxxTest::RealTestDescription {
public:
 TestDescription_CommandLineParserTestSuite_testParseIncompleteArgument() : CxxTest::RealTestDescription( Tests_CommandLineParserTestSuite, suiteDescription_CommandLineParserTestSuite, 118, "testParseIncompleteArgument" ) {}
 void runTest() { suite_CommandLineParserTestSuite.testParseIncompleteArgument(); }
} testDescription_CommandLineParserTestSuite_testParseIncompleteArgument;

#include <cxxtest/Root.cpp>

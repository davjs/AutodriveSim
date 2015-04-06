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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/StringToolboxTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/StringToolboxTestSuite.h"

static StringToolboxTest suite_StringToolboxTest;

static CxxTest::List Tests_StringToolboxTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_StringToolboxTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/StringToolboxTestSuite.h", 31, "StringToolboxTest", suite_StringToolboxTest, Tests_StringToolboxTest );

static class TestDescription_StringToolboxTest_testTrim : public CxxTest::RealTestDescription {
public:
 TestDescription_StringToolboxTest_testTrim() : CxxTest::RealTestDescription( Tests_StringToolboxTest, suiteDescription_StringToolboxTest, 33, "testTrim" ) {}
 void runTest() { suite_StringToolboxTest.testTrim(); }
} testDescription_StringToolboxTest_testTrim;

static class TestDescription_StringToolboxTest_testCompareIgnoreCase : public CxxTest::RealTestDescription {
public:
 TestDescription_StringToolboxTest_testCompareIgnoreCase() : CxxTest::RealTestDescription( Tests_StringToolboxTest, suiteDescription_StringToolboxTest, 60, "testCompareIgnoreCase" ) {}
 void runTest() { suite_StringToolboxTest.testCompareIgnoreCase(); }
} testDescription_StringToolboxTest_testCompareIgnoreCase;

static class TestDescription_StringToolboxTest_testSplit : public CxxTest::RealTestDescription {
public:
 TestDescription_StringToolboxTest_testSplit() : CxxTest::RealTestDescription( Tests_StringToolboxTest, suiteDescription_StringToolboxTest, 83, "testSplit" ) {}
 void runTest() { suite_StringToolboxTest.testSplit(); }
} testDescription_StringToolboxTest_testSplit;

#include <cxxtest/Root.cpp>

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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/StringProtocolTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/StringProtocolTestSuite.h"

static StringProtocolTest suite_StringProtocolTest;

static CxxTest::List Tests_StringProtocolTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_StringProtocolTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/StringProtocolTestSuite.h", 34, "StringProtocolTest", suite_StringProtocolTest, Tests_StringProtocolTest );

static class TestDescription_StringProtocolTest_testStringProtocolSend : public CxxTest::RealTestDescription {
public:
 TestDescription_StringProtocolTest_testStringProtocolSend() : CxxTest::RealTestDescription( Tests_StringProtocolTest, suiteDescription_StringProtocolTest, 52, "testStringProtocolSend" ) {}
 void runTest() { suite_StringProtocolTest.testStringProtocolSend(); }
} testDescription_StringProtocolTest_testStringProtocolSend;

static class TestDescription_StringProtocolTest_testStringProtocolReceive : public CxxTest::RealTestDescription {
public:
 TestDescription_StringProtocolTest_testStringProtocolReceive() : CxxTest::RealTestDescription( Tests_StringProtocolTest, suiteDescription_StringProtocolTest, 73, "testStringProtocolReceive" ) {}
 void runTest() { suite_StringProtocolTest.testStringProtocolReceive(); }
} testDescription_StringProtocolTest_testStringProtocolReceive;

#include <cxxtest/Root.cpp>

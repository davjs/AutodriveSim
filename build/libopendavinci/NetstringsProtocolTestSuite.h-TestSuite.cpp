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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/NetstringsProtocolTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/NetstringsProtocolTestSuite.h"

static NetstringsProtocolTest suite_NetstringsProtocolTest;

static CxxTest::List Tests_NetstringsProtocolTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_NetstringsProtocolTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/NetstringsProtocolTestSuite.h", 34, "NetstringsProtocolTest", suite_NetstringsProtocolTest, Tests_NetstringsProtocolTest );

static class TestDescription_NetstringsProtocolTest_testNetstringsProtocolSend : public CxxTest::RealTestDescription {
public:
 TestDescription_NetstringsProtocolTest_testNetstringsProtocolSend() : CxxTest::RealTestDescription( Tests_NetstringsProtocolTest, suiteDescription_NetstringsProtocolTest, 52, "testNetstringsProtocolSend" ) {}
 void runTest() { suite_NetstringsProtocolTest.testNetstringsProtocolSend(); }
} testDescription_NetstringsProtocolTest_testNetstringsProtocolSend;

static class TestDescription_NetstringsProtocolTest_testNetstringsProtocolReceive : public CxxTest::RealTestDescription {
public:
 TestDescription_NetstringsProtocolTest_testNetstringsProtocolReceive() : CxxTest::RealTestDescription( Tests_NetstringsProtocolTest, suiteDescription_NetstringsProtocolTest, 70, "testNetstringsProtocolReceive" ) {}
 void runTest() { suite_NetstringsProtocolTest.testNetstringsProtocolReceive(); }
} testDescription_NetstringsProtocolTest_testNetstringsProtocolReceive;

static class TestDescription_NetstringsProtocolTest_testNetstringsProtocolPartialReceive1 : public CxxTest::RealTestDescription {
public:
 TestDescription_NetstringsProtocolTest_testNetstringsProtocolPartialReceive1() : CxxTest::RealTestDescription( Tests_NetstringsProtocolTest, suiteDescription_NetstringsProtocolTest, 89, "testNetstringsProtocolPartialReceive1" ) {}
 void runTest() { suite_NetstringsProtocolTest.testNetstringsProtocolPartialReceive1(); }
} testDescription_NetstringsProtocolTest_testNetstringsProtocolPartialReceive1;

static class TestDescription_NetstringsProtocolTest_testNetstringsProtocolPartialReceive2 : public CxxTest::RealTestDescription {
public:
 TestDescription_NetstringsProtocolTest_testNetstringsProtocolPartialReceive2() : CxxTest::RealTestDescription( Tests_NetstringsProtocolTest, suiteDescription_NetstringsProtocolTest, 107, "testNetstringsProtocolPartialReceive2" ) {}
 void runTest() { suite_NetstringsProtocolTest.testNetstringsProtocolPartialReceive2(); }
} testDescription_NetstringsProtocolTest_testNetstringsProtocolPartialReceive2;

#include <cxxtest/Root.cpp>

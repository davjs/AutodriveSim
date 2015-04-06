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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/QueueTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/QueueTestSuite.h"

static QueueTest suite_QueueTest;

static CxxTest::List Tests_QueueTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_QueueTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/QueueTestSuite.h", 231, "QueueTest", suite_QueueTest, Tests_QueueTest );

static class TestDescription_QueueTest_testLIFO : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testLIFO() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 233, "testLIFO" ) {}
 void runTest() { suite_QueueTest.testLIFO(); }
} testDescription_QueueTest_testLIFO;

static class TestDescription_QueueTest_testFIFO : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testFIFO() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 254, "testFIFO" ) {}
 void runTest() { suite_QueueTest.testFIFO(); }
} testDescription_QueueTest_testFIFO;

static class TestDescription_QueueTest_testBufferedFIFOAsRegularFIFO : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testBufferedFIFOAsRegularFIFO() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 274, "testBufferedFIFOAsRegularFIFO" ) {}
 void runTest() { suite_QueueTest.testBufferedFIFOAsRegularFIFO(); }
} testDescription_QueueTest_testBufferedFIFOAsRegularFIFO;

static class TestDescription_QueueTest_testBufferedFIFO : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testBufferedFIFO() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 294, "testBufferedFIFO" ) {}
 void runTest() { suite_QueueTest.testBufferedFIFO(); }
} testDescription_QueueTest_testBufferedFIFO;

static class TestDescription_QueueTest_testFixedSizeBufferedFIFO : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testFixedSizeBufferedFIFO() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 365, "testFixedSizeBufferedFIFO" ) {}
 void runTest() { suite_QueueTest.testFixedSizeBufferedFIFO(); }
} testDescription_QueueTest_testFixedSizeBufferedFIFO;

static class TestDescription_QueueTest_testBufferedLIFOAsRegularLIFO : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testBufferedLIFOAsRegularLIFO() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 455, "testBufferedLIFOAsRegularLIFO" ) {}
 void runTest() { suite_QueueTest.testBufferedLIFOAsRegularLIFO(); }
} testDescription_QueueTest_testBufferedLIFOAsRegularLIFO;

static class TestDescription_QueueTest_testBufferedLIFO : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testBufferedLIFO() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 475, "testBufferedLIFO" ) {}
 void runTest() { suite_QueueTest.testBufferedLIFO(); }
} testDescription_QueueTest_testBufferedLIFO;

static class TestDescription_QueueTest_testFixedSizeBufferedLIFO : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testFixedSizeBufferedLIFO() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 546, "testFixedSizeBufferedLIFO" ) {}
 void runTest() { suite_QueueTest.testFixedSizeBufferedLIFO(); }
} testDescription_QueueTest_testFixedSizeBufferedLIFO;

#include <cxxtest/Root.cpp>

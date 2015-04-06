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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/SharedMemoryTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/SharedMemoryTestSuite.h"

static SharedMemoryTest suite_SharedMemoryTest;

static CxxTest::List Tests_SharedMemoryTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SharedMemoryTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/SharedMemoryTestSuite.h", 32, "SharedMemoryTest", suite_SharedMemoryTest, Tests_SharedMemoryTest );

static class TestDescription_SharedMemoryTest_testSharedData1 : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedMemoryTest_testSharedData1() : CxxTest::RealTestDescription( Tests_SharedMemoryTest, suiteDescription_SharedMemoryTest, 34, "testSharedData1" ) {}
 void runTest() { suite_SharedMemoryTest.testSharedData1(); }
} testDescription_SharedMemoryTest_testSharedData1;

static class TestDescription_SharedMemoryTest_testSharedData2 : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedMemoryTest_testSharedData2() : CxxTest::RealTestDescription( Tests_SharedMemoryTest, suiteDescription_SharedMemoryTest, 46, "testSharedData2" ) {}
 void runTest() { suite_SharedMemoryTest.testSharedData2(); }
} testDescription_SharedMemoryTest_testSharedData2;

static class TestDescription_SharedMemoryTest_testSharedData3 : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedMemoryTest_testSharedData3() : CxxTest::RealTestDescription( Tests_SharedMemoryTest, suiteDescription_SharedMemoryTest, 58, "testSharedData3" ) {}
 void runTest() { suite_SharedMemoryTest.testSharedData3(); }
} testDescription_SharedMemoryTest_testSharedData3;

static class TestDescription_SharedMemoryTest_testSharedMemory : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedMemoryTest_testSharedMemory() : CxxTest::RealTestDescription( Tests_SharedMemoryTest, suiteDescription_SharedMemoryTest, 72, "testSharedMemory" ) {}
 void runTest() { suite_SharedMemoryTest.testSharedMemory(); }
} testDescription_SharedMemoryTest_testSharedMemory;

#include <cxxtest/Root.cpp>

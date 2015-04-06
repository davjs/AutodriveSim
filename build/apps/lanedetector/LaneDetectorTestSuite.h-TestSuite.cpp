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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/apps/lanedetector/LaneDetectorTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/apps/lanedetector/testsuites/LaneDetectorTestSuite.h"

static LaneDetectorTest suite_LaneDetectorTest;

static CxxTest::List Tests_LaneDetectorTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_LaneDetectorTest( "/home/david/AutoDriveSim2/apps/lanedetector/testsuites/LaneDetectorTestSuite.h", 66, "LaneDetectorTest", suite_LaneDetectorTest, Tests_LaneDetectorTest );

static class TestDescription_LaneDetectorTest_testLaneDetectorSuccessfullyCreated : public CxxTest::RealTestDescription {
public:
 TestDescription_LaneDetectorTest_testLaneDetectorSuccessfullyCreated() : CxxTest::RealTestDescription( Tests_LaneDetectorTest, suiteDescription_LaneDetectorTest, 100, "testLaneDetectorSuccessfullyCreated" ) {}
 void runTest() { suite_LaneDetectorTest.testLaneDetectorSuccessfullyCreated(); }
} testDescription_LaneDetectorTest_testLaneDetectorSuccessfullyCreated;

static class TestDescription_LaneDetectorTest_testLaneDetectorProcessingMethod : public CxxTest::RealTestDescription {
public:
 TestDescription_LaneDetectorTest_testLaneDetectorProcessingMethod() : CxxTest::RealTestDescription( Tests_LaneDetectorTest, suiteDescription_LaneDetectorTest, 104, "testLaneDetectorProcessingMethod" ) {}
 void runTest() { suite_LaneDetectorTest.testLaneDetectorProcessingMethod(); }
} testDescription_LaneDetectorTest_testLaneDetectorProcessingMethod;

static class TestDescription_LaneDetectorTest_testLaneDetectorProcessingMethodInvalidSharedMemory : public CxxTest::RealTestDescription {
public:
 TestDescription_LaneDetectorTest_testLaneDetectorProcessingMethodInvalidSharedMemory() : CxxTest::RealTestDescription( Tests_LaneDetectorTest, suiteDescription_LaneDetectorTest, 131, "testLaneDetectorProcessingMethodInvalidSharedMemory" ) {}
 void runTest() { suite_LaneDetectorTest.testLaneDetectorProcessingMethodInvalidSharedMemory(); }
} testDescription_LaneDetectorTest_testLaneDetectorProcessingMethodInvalidSharedMemory;

#include <cxxtest/Root.cpp>

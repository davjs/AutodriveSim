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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/apps/lanedetector/LaneDetectorReplayTestsuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/apps/lanedetector/testsuites/LaneDetectorReplayTestsuite.h"

static LaneDetectorReplayTestSuite suite_LaneDetectorReplayTestSuite;

static CxxTest::List Tests_LaneDetectorReplayTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_LaneDetectorReplayTestSuite( "/home/david/AutoDriveSim2/apps/lanedetector/testsuites/LaneDetectorReplayTestsuite.h", 92, "LaneDetectorReplayTestSuite", suite_LaneDetectorReplayTestSuite, Tests_LaneDetectorReplayTestSuite );

static class TestDescription_LaneDetectorReplayTestSuite_testReplayRecording : public CxxTest::RealTestDescription {
public:
 TestDescription_LaneDetectorReplayTestSuite_testReplayRecording() : CxxTest::RealTestDescription( Tests_LaneDetectorReplayTestSuite, suiteDescription_LaneDetectorReplayTestSuite, 95, "testReplayRecording" ) {}
 void runTest() { suite_LaneDetectorReplayTestSuite.testReplayRecording(); }
} testDescription_LaneDetectorReplayTestSuite_testReplayRecording;

#include <cxxtest/Root.cpp>

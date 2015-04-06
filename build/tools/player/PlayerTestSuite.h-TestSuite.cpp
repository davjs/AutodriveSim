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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/tools/player/PlayerTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/tools/player/testsuites/PlayerTestSuite.h"

static PlayerModuleTest suite_PlayerModuleTest;

static CxxTest::List Tests_PlayerModuleTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_PlayerModuleTest( "/home/david/AutoDriveSim2/tools/player/testsuites/PlayerTestSuite.h", 102, "PlayerModuleTest", suite_PlayerModuleTest, Tests_PlayerModuleTest );

static class TestDescription_PlayerModuleTest_testPlayerCommand : public CxxTest::RealTestDescription {
public:
 TestDescription_PlayerModuleTest_testPlayerCommand() : CxxTest::RealTestDescription( Tests_PlayerModuleTest, suiteDescription_PlayerModuleTest, 121, "testPlayerCommand" ) {}
 void runTest() { suite_PlayerModuleTest.testPlayerCommand(); }
} testDescription_PlayerModuleTest_testPlayerCommand;

static class TestDescription_PlayerModuleTest_testRealtimeReplayNoRewind : public CxxTest::RealTestDescription {
public:
 TestDescription_PlayerModuleTest_testRealtimeReplayNoRewind() : CxxTest::RealTestDescription( Tests_PlayerModuleTest, suiteDescription_PlayerModuleTest, 158, "testRealtimeReplayNoRewind" ) {}
 void runTest() { suite_PlayerModuleTest.testRealtimeReplayNoRewind(); }
} testDescription_PlayerModuleTest_testRealtimeReplayNoRewind;

static class TestDescription_PlayerModuleTest_testDoubleRealtimeReplayNoRewind : public CxxTest::RealTestDescription {
public:
 TestDescription_PlayerModuleTest_testDoubleRealtimeReplayNoRewind() : CxxTest::RealTestDescription( Tests_PlayerModuleTest, suiteDescription_PlayerModuleTest, 281, "testDoubleRealtimeReplayNoRewind" ) {}
 void runTest() { suite_PlayerModuleTest.testDoubleRealtimeReplayNoRewind(); }
} testDescription_PlayerModuleTest_testDoubleRealtimeReplayNoRewind;

static class TestDescription_PlayerModuleTest_testHalfRealtimeReplayNoRewind : public CxxTest::RealTestDescription {
public:
 TestDescription_PlayerModuleTest_testHalfRealtimeReplayNoRewind() : CxxTest::RealTestDescription( Tests_PlayerModuleTest, suiteDescription_PlayerModuleTest, 416, "testHalfRealtimeReplayNoRewind" ) {}
 void runTest() { suite_PlayerModuleTest.testHalfRealtimeReplayNoRewind(); }
} testDescription_PlayerModuleTest_testHalfRealtimeReplayNoRewind;

static class TestDescription_PlayerModuleTest_testRealtimeReplayAutoRewind : public CxxTest::RealTestDescription {
public:
 TestDescription_PlayerModuleTest_testRealtimeReplayAutoRewind() : CxxTest::RealTestDescription( Tests_PlayerModuleTest, suiteDescription_PlayerModuleTest, 550, "testRealtimeReplayAutoRewind" ) {}
 void runTest() { suite_PlayerModuleTest.testRealtimeReplayAutoRewind(); }
} testDescription_PlayerModuleTest_testRealtimeReplayAutoRewind;

static class TestDescription_PlayerModuleTest_testRealtimeReplayNoRewindRemoteControl : public CxxTest::RealTestDescription {
public:
 TestDescription_PlayerModuleTest_testRealtimeReplayNoRewindRemoteControl() : CxxTest::RealTestDescription( Tests_PlayerModuleTest, suiteDescription_PlayerModuleTest, 696, "testRealtimeReplayNoRewindRemoteControl" ) {}
 void runTest() { suite_PlayerModuleTest.testRealtimeReplayNoRewindRemoteControl(); }
} testDescription_PlayerModuleTest_testRealtimeReplayNoRewindRemoteControl;

#include <cxxtest/Root.cpp>

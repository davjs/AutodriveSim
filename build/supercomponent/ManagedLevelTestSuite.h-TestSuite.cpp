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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/supercomponent/ManagedLevelTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/supercomponent/testsuites/ManagedLevelTestSuite.h"

static ManagedLevelTest suite_ManagedLevelTest;

static CxxTest::List Tests_ManagedLevelTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ManagedLevelTest( "/home/david/AutoDriveSim2/supercomponent/testsuites/ManagedLevelTestSuite.h", 299, "ManagedLevelTest", suite_ManagedLevelTest, Tests_ManagedLevelTest );

static class TestDescription_ManagedLevelTest_testManagedLevelNone : public CxxTest::RealTestDescription {
public:
 TestDescription_ManagedLevelTest_testManagedLevelNone() : CxxTest::RealTestDescription( Tests_ManagedLevelTest, suiteDescription_ManagedLevelTest, 302, "testManagedLevelNone" ) {}
 void runTest() { suite_ManagedLevelTest.testManagedLevelNone(); }
} testDescription_ManagedLevelTest_testManagedLevelNone;

static class TestDescription_ManagedLevelTest_testManagedLevelNone_stop_supercomponent_yields_stop_client : public CxxTest::RealTestDescription {
public:
 TestDescription_ManagedLevelTest_testManagedLevelNone_stop_supercomponent_yields_stop_client() : CxxTest::RealTestDescription( Tests_ManagedLevelTest, suiteDescription_ManagedLevelTest, 367, "testManagedLevelNone_stop_supercomponent_yields_stop_client" ) {}
 void runTest() { suite_ManagedLevelTest.testManagedLevelNone_stop_supercomponent_yields_stop_client(); }
} testDescription_ManagedLevelTest_testManagedLevelNone_stop_supercomponent_yields_stop_client;

static class TestDescription_ManagedLevelTest_testManagedLevelPulseShift_SenderReceiver_random_sleep_to_require_pulse_time_ack : public CxxTest::RealTestDescription {
public:
 TestDescription_ManagedLevelTest_testManagedLevelPulseShift_SenderReceiver_random_sleep_to_require_pulse_time_ack() : CxxTest::RealTestDescription( Tests_ManagedLevelTest, suiteDescription_ManagedLevelTest, 963, "testManagedLevelPulseShift_SenderReceiver_random_sleep_to_require_pulse_time_ack" ) {}
 void runTest() { suite_ManagedLevelTest.testManagedLevelPulseShift_SenderReceiver_random_sleep_to_require_pulse_time_ack(); }
} testDescription_ManagedLevelTest_testManagedLevelPulseShift_SenderReceiver_random_sleep_to_require_pulse_time_ack;

static class TestDescription_ManagedLevelTest_testManagedLevelPulseTimeAck_SenderReceiver : public CxxTest::RealTestDescription {
public:
 TestDescription_ManagedLevelTest_testManagedLevelPulseTimeAck_SenderReceiver() : CxxTest::RealTestDescription( Tests_ManagedLevelTest, suiteDescription_ManagedLevelTest, 1060, "testManagedLevelPulseTimeAck_SenderReceiver" ) {}
 void runTest() { suite_ManagedLevelTest.testManagedLevelPulseTimeAck_SenderReceiver(); }
} testDescription_ManagedLevelTest_testManagedLevelPulseTimeAck_SenderReceiver;

static class TestDescription_ManagedLevelTest_testManagedLevelPulseTime : public CxxTest::RealTestDescription {
public:
 TestDescription_ManagedLevelTest_testManagedLevelPulseTime() : CxxTest::RealTestDescription( Tests_ManagedLevelTest, suiteDescription_ManagedLevelTest, 1217, "testManagedLevelPulseTime" ) {}
 void runTest() { suite_ManagedLevelTest.testManagedLevelPulseTime(); }
} testDescription_ManagedLevelTest_testManagedLevelPulseTime;

#include <cxxtest/Root.cpp>

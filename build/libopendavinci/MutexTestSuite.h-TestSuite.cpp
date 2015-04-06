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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/MutexTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/MutexTestSuite.h"

static MutexTest suite_MutexTest;

static CxxTest::List Tests_MutexTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MutexTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/MutexTestSuite.h", 47, "MutexTest", suite_MutexTest, Tests_MutexTest );

static class TestDescription_MutexTest_testTryLock : public CxxTest::RealTestDescription {
public:
 TestDescription_MutexTest_testTryLock() : CxxTest::RealTestDescription( Tests_MutexTest, suiteDescription_MutexTest, 49, "testTryLock" ) {}
 void runTest() { suite_MutexTest.testTryLock(); }
} testDescription_MutexTest_testTryLock;

static class TestDescription_MutexTest_testLockAndUnlock : public CxxTest::RealTestDescription {
public:
 TestDescription_MutexTest_testLockAndUnlock() : CxxTest::RealTestDescription( Tests_MutexTest, suiteDescription_MutexTest, 55, "testLockAndUnlock" ) {}
 void runTest() { suite_MutexTest.testLockAndUnlock(); }
} testDescription_MutexTest_testLockAndUnlock;

#include <cxxtest/Root.cpp>

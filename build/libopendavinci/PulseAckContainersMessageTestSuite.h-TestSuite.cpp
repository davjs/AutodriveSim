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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/PulseAckContainersMessageTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/PulseAckContainersMessageTestSuite.h"

static PulseAckContainersTest suite_PulseAckContainersTest;

static CxxTest::List Tests_PulseAckContainersTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_PulseAckContainersTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/PulseAckContainersMessageTestSuite.h", 36, "PulseAckContainersTest", suite_PulseAckContainersTest, Tests_PulseAckContainersTest );

static class TestDescription_PulseAckContainersTest_testPulseEmpty : public CxxTest::RealTestDescription {
public:
 TestDescription_PulseAckContainersTest_testPulseEmpty() : CxxTest::RealTestDescription( Tests_PulseAckContainersTest, suiteDescription_PulseAckContainersTest, 38, "testPulseEmpty" ) {}
 void runTest() { suite_PulseAckContainersTest.testPulseEmpty(); }
} testDescription_PulseAckContainersTest_testPulseEmpty;

static class TestDescription_PulseAckContainersTest_testPulseContainers : public CxxTest::RealTestDescription {
public:
 TestDescription_PulseAckContainersTest_testPulseContainers() : CxxTest::RealTestDescription( Tests_PulseAckContainersTest, suiteDescription_PulseAckContainersTest, 51, "testPulseContainers" ) {}
 void runTest() { suite_PulseAckContainersTest.testPulseContainers(); }
} testDescription_PulseAckContainersTest_testPulseContainers;

static class TestDescription_PulseAckContainersTest_testPulseContainersSetValues : public CxxTest::RealTestDescription {
public:
 TestDescription_PulseAckContainersTest_testPulseContainersSetValues() : CxxTest::RealTestDescription( Tests_PulseAckContainersTest, suiteDescription_PulseAckContainersTest, 97, "testPulseContainersSetValues" ) {}
 void runTest() { suite_PulseAckContainersTest.testPulseContainersSetValues(); }
} testDescription_PulseAckContainersTest_testPulseContainersSetValues;

static class TestDescription_PulseAckContainersTest_testPulseAckContainersEmpty : public CxxTest::RealTestDescription {
public:
 TestDescription_PulseAckContainersTest_testPulseAckContainersEmpty() : CxxTest::RealTestDescription( Tests_PulseAckContainersTest, suiteDescription_PulseAckContainersTest, 142, "testPulseAckContainersEmpty" ) {}
 void runTest() { suite_PulseAckContainersTest.testPulseAckContainersEmpty(); }
} testDescription_PulseAckContainersTest_testPulseAckContainersEmpty;

static class TestDescription_PulseAckContainersTest_testPulseAckContainers : public CxxTest::RealTestDescription {
public:
 TestDescription_PulseAckContainersTest_testPulseAckContainers() : CxxTest::RealTestDescription( Tests_PulseAckContainersTest, suiteDescription_PulseAckContainersTest, 155, "testPulseAckContainers" ) {}
 void runTest() { suite_PulseAckContainersTest.testPulseAckContainers(); }
} testDescription_PulseAckContainersTest_testPulseAckContainers;

static class TestDescription_PulseAckContainersTest_testPulseAckContainers_from_list : public CxxTest::RealTestDescription {
public:
 TestDescription_PulseAckContainersTest_testPulseAckContainers_from_list() : CxxTest::RealTestDescription( Tests_PulseAckContainersTest, suiteDescription_PulseAckContainersTest, 201, "testPulseAckContainers_from_list" ) {}
 void runTest() { suite_PulseAckContainersTest.testPulseAckContainers_from_list(); }
} testDescription_PulseAckContainersTest_testPulseAckContainers_from_list;

#include <cxxtest/Root.cpp>

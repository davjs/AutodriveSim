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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/ContainerTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/ContainerTestSuite.h"

static ContainerTest suite_ContainerTest;

static CxxTest::List Tests_ContainerTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ContainerTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/ContainerTestSuite.h", 33, "ContainerTest", suite_ContainerTest, Tests_ContainerTest );

static class TestDescription_ContainerTest_testContainerData : public CxxTest::RealTestDescription {
public:
 TestDescription_ContainerTest_testContainerData() : CxxTest::RealTestDescription( Tests_ContainerTest, suiteDescription_ContainerTest, 35, "testContainerData" ) {}
 void runTest() { suite_ContainerTest.testContainerData(); }
} testDescription_ContainerTest_testContainerData;

static class TestDescription_ContainerTest_testContainerDataUserType : public CxxTest::RealTestDescription {
public:
 TestDescription_ContainerTest_testContainerDataUserType() : CxxTest::RealTestDescription( Tests_ContainerTest, suiteDescription_ContainerTest, 51, "testContainerDataUserType" ) {}
 void runTest() { suite_ContainerTest.testContainerDataUserType(); }
} testDescription_ContainerTest_testContainerDataUserType;

#include <cxxtest/Root.cpp>

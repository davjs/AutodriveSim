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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/apps/VCR/VCRTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/apps/VCR/testsuites/VCRTestSuite.h"

static VCRTest suite_VCRTest;

static CxxTest::List Tests_VCRTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_VCRTest( "/home/david/AutoDriveSim2/apps/VCR/testsuites/VCRTestSuite.h", 66, "VCRTest", suite_VCRTest, Tests_VCRTest );

static class TestDescription_VCRTest_testVCRSuccessfullyCreated : public CxxTest::RealTestDescription {
public:
 TestDescription_VCRTest_testVCRSuccessfullyCreated() : CxxTest::RealTestDescription( Tests_VCRTest, suiteDescription_VCRTest, 100, "testVCRSuccessfullyCreated" ) {}
 void runTest() { suite_VCRTest.testVCRSuccessfullyCreated(); }
} testDescription_VCRTest_testVCRSuccessfullyCreated;

static class TestDescription_VCRTest_testVCRProcessingMethod : public CxxTest::RealTestDescription {
public:
 TestDescription_VCRTest_testVCRProcessingMethod() : CxxTest::RealTestDescription( Tests_VCRTest, suiteDescription_VCRTest, 104, "testVCRProcessingMethod" ) {}
 void runTest() { suite_VCRTest.testVCRProcessingMethod(); }
} testDescription_VCRTest_testVCRProcessingMethod;

static class TestDescription_VCRTest_testVCRProcessingMethodInvalidSharedMemory : public CxxTest::RealTestDescription {
public:
 TestDescription_VCRTest_testVCRProcessingMethodInvalidSharedMemory() : CxxTest::RealTestDescription( Tests_VCRTest, suiteDescription_VCRTest, 131, "testVCRProcessingMethodInvalidSharedMemory" ) {}
 void runTest() { suite_VCRTest.testVCRProcessingMethodInvalidSharedMemory(); }
} testDescription_VCRTest_testVCRProcessingMethodInvalidSharedMemory;

#include <cxxtest/Root.cpp>

/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/XmlFilePrinter.h>

int main() {
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libdata/msv_SteeringDataTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libdata/testsuites/msv_SteeringDataTestSuite.h"

static msv_SteeringData_TestSuite suite_msv_SteeringData_TestSuite;

static CxxTest::List Tests_msv_SteeringData_TestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_msv_SteeringData_TestSuite( "/home/david/AutoDriveSim2/libdata/testsuites/msv_SteeringDataTestSuite.h", 25, "msv_SteeringData_TestSuite", suite_msv_SteeringData_TestSuite, Tests_msv_SteeringData_TestSuite );

static class TestDescription_msv_SteeringData_TestSuite_testCreateObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_SteeringData_TestSuite_testCreateObject() : CxxTest::RealTestDescription( Tests_msv_SteeringData_TestSuite, suiteDescription_msv_SteeringData_TestSuite, 28, "testCreateObject" ) {}
 void runTest() { suite_msv_SteeringData_TestSuite.testCreateObject(); }
} testDescription_msv_SteeringData_TestSuite_testCreateObject;

static class TestDescription_msv_SteeringData_TestSuite_testCreateAndCopyObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_SteeringData_TestSuite_testCreateAndCopyObject() : CxxTest::RealTestDescription( Tests_msv_SteeringData_TestSuite, suiteDescription_msv_SteeringData_TestSuite, 39, "testCreateAndCopyObject" ) {}
 void runTest() { suite_msv_SteeringData_TestSuite.testCreateAndCopyObject(); }
} testDescription_msv_SteeringData_TestSuite_testCreateAndCopyObject;

static class TestDescription_msv_SteeringData_TestSuite_testCreateAndAssignObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_SteeringData_TestSuite_testCreateAndAssignObject() : CxxTest::RealTestDescription( Tests_msv_SteeringData_TestSuite, suiteDescription_msv_SteeringData_TestSuite, 60, "testCreateAndAssignObject" ) {}
 void runTest() { suite_msv_SteeringData_TestSuite.testCreateAndAssignObject(); }
} testDescription_msv_SteeringData_TestSuite_testCreateAndAssignObject;

static class TestDescription_msv_SteeringData_TestSuite_testCreateAndSerializeObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_SteeringData_TestSuite_testCreateAndSerializeObject() : CxxTest::RealTestDescription( Tests_msv_SteeringData_TestSuite, suiteDescription_msv_SteeringData_TestSuite, 81, "testCreateAndSerializeObject" ) {}
 void runTest() { suite_msv_SteeringData_TestSuite.testCreateAndSerializeObject(); }
} testDescription_msv_SteeringData_TestSuite_testCreateAndSerializeObject;

#include <cxxtest/Root.cpp>

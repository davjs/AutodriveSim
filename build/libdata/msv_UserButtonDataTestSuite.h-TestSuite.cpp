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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libdata/msv_UserButtonDataTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libdata/testsuites/msv_UserButtonDataTestSuite.h"

static msv_UserButtonData_TestSuite suite_msv_UserButtonData_TestSuite;

static CxxTest::List Tests_msv_UserButtonData_TestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_msv_UserButtonData_TestSuite( "/home/david/AutoDriveSim2/libdata/testsuites/msv_UserButtonDataTestSuite.h", 25, "msv_UserButtonData_TestSuite", suite_msv_UserButtonData_TestSuite, Tests_msv_UserButtonData_TestSuite );

static class TestDescription_msv_UserButtonData_TestSuite_testCreateObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_UserButtonData_TestSuite_testCreateObject() : CxxTest::RealTestDescription( Tests_msv_UserButtonData_TestSuite, suiteDescription_msv_UserButtonData_TestSuite, 28, "testCreateObject" ) {}
 void runTest() { suite_msv_UserButtonData_TestSuite.testCreateObject(); }
} testDescription_msv_UserButtonData_TestSuite_testCreateObject;

static class TestDescription_msv_UserButtonData_TestSuite_testCreateAndCopyObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_UserButtonData_TestSuite_testCreateAndCopyObject() : CxxTest::RealTestDescription( Tests_msv_UserButtonData_TestSuite, suiteDescription_msv_UserButtonData_TestSuite, 39, "testCreateAndCopyObject" ) {}
 void runTest() { suite_msv_UserButtonData_TestSuite.testCreateAndCopyObject(); }
} testDescription_msv_UserButtonData_TestSuite_testCreateAndCopyObject;

static class TestDescription_msv_UserButtonData_TestSuite_testCreateAndAssignObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_UserButtonData_TestSuite_testCreateAndAssignObject() : CxxTest::RealTestDescription( Tests_msv_UserButtonData_TestSuite, suiteDescription_msv_UserButtonData_TestSuite, 60, "testCreateAndAssignObject" ) {}
 void runTest() { suite_msv_UserButtonData_TestSuite.testCreateAndAssignObject(); }
} testDescription_msv_UserButtonData_TestSuite_testCreateAndAssignObject;

static class TestDescription_msv_UserButtonData_TestSuite_testCreateAndSerializeObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_UserButtonData_TestSuite_testCreateAndSerializeObject() : CxxTest::RealTestDescription( Tests_msv_UserButtonData_TestSuite, suiteDescription_msv_UserButtonData_TestSuite, 81, "testCreateAndSerializeObject" ) {}
 void runTest() { suite_msv_UserButtonData_TestSuite.testCreateAndSerializeObject(); }
} testDescription_msv_UserButtonData_TestSuite_testCreateAndSerializeObject;

#include <cxxtest/Root.cpp>

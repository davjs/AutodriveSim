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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libdata/msv_SensorBoardDataTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libdata/testsuites/msv_SensorBoardDataTestSuite.h"

static msv_SensorBoardData_TestSuite suite_msv_SensorBoardData_TestSuite;

static CxxTest::List Tests_msv_SensorBoardData_TestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_msv_SensorBoardData_TestSuite( "/home/david/AutoDriveSim2/libdata/testsuites/msv_SensorBoardDataTestSuite.h", 25, "msv_SensorBoardData_TestSuite", suite_msv_SensorBoardData_TestSuite, Tests_msv_SensorBoardData_TestSuite );

static class TestDescription_msv_SensorBoardData_TestSuite_testCreateObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_SensorBoardData_TestSuite_testCreateObject() : CxxTest::RealTestDescription( Tests_msv_SensorBoardData_TestSuite, suiteDescription_msv_SensorBoardData_TestSuite, 28, "testCreateObject" ) {}
 void runTest() { suite_msv_SensorBoardData_TestSuite.testCreateObject(); }
} testDescription_msv_SensorBoardData_TestSuite_testCreateObject;

static class TestDescription_msv_SensorBoardData_TestSuite_testCreateAndCopyObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_SensorBoardData_TestSuite_testCreateAndCopyObject() : CxxTest::RealTestDescription( Tests_msv_SensorBoardData_TestSuite, suiteDescription_msv_SensorBoardData_TestSuite, 112, "testCreateAndCopyObject" ) {}
 void runTest() { suite_msv_SensorBoardData_TestSuite.testCreateAndCopyObject(); }
} testDescription_msv_SensorBoardData_TestSuite_testCreateAndCopyObject;

static class TestDescription_msv_SensorBoardData_TestSuite_testCreateAndAssignObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_SensorBoardData_TestSuite_testCreateAndAssignObject() : CxxTest::RealTestDescription( Tests_msv_SensorBoardData_TestSuite, suiteDescription_msv_SensorBoardData_TestSuite, 218, "testCreateAndAssignObject" ) {}
 void runTest() { suite_msv_SensorBoardData_TestSuite.testCreateAndAssignObject(); }
} testDescription_msv_SensorBoardData_TestSuite_testCreateAndAssignObject;

static class TestDescription_msv_SensorBoardData_TestSuite_testCreateAndSerializeObject : public CxxTest::RealTestDescription {
public:
 TestDescription_msv_SensorBoardData_TestSuite_testCreateAndSerializeObject() : CxxTest::RealTestDescription( Tests_msv_SensorBoardData_TestSuite, suiteDescription_msv_SensorBoardData_TestSuite, 325, "testCreateAndSerializeObject" ) {}
 void runTest() { suite_msv_SensorBoardData_TestSuite.testCreateAndSerializeObject(); }
} testDescription_msv_SensorBoardData_TestSuite_testCreateAndSerializeObject;

#include <cxxtest/Root.cpp>

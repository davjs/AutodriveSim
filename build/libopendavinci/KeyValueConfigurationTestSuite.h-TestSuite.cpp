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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/KeyValueConfigurationTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/KeyValueConfigurationTestSuite.h"

static ConfigurationTest suite_ConfigurationTest;

static CxxTest::List Tests_ConfigurationTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ConfigurationTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/KeyValueConfigurationTestSuite.h", 35, "ConfigurationTest", suite_ConfigurationTest, Tests_ConfigurationTest );

static class TestDescription_ConfigurationTest_testReadSimpleData : public CxxTest::RealTestDescription {
public:
 TestDescription_ConfigurationTest_testReadSimpleData() : CxxTest::RealTestDescription( Tests_ConfigurationTest, suiteDescription_ConfigurationTest, 37, "testReadSimpleData" ) {}
 void runTest() { suite_ConfigurationTest.testReadSimpleData(); }
} testDescription_ConfigurationTest_testReadSimpleData;

static class TestDescription_ConfigurationTest_testReadSimpleDataCopyConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_ConfigurationTest_testReadSimpleDataCopyConstructor() : CxxTest::RealTestDescription( Tests_ConfigurationTest, suiteDescription_ConfigurationTest, 72, "testReadSimpleDataCopyConstructor" ) {}
 void runTest() { suite_ConfigurationTest.testReadSimpleDataCopyConstructor(); }
} testDescription_ConfigurationTest_testReadSimpleDataCopyConstructor;

static class TestDescription_ConfigurationTest_testReadSimpleDataAssignmentOperator : public CxxTest::RealTestDescription {
public:
 TestDescription_ConfigurationTest_testReadSimpleDataAssignmentOperator() : CxxTest::RealTestDescription( Tests_ConfigurationTest, suiteDescription_ConfigurationTest, 109, "testReadSimpleDataAssignmentOperator" ) {}
 void runTest() { suite_ConfigurationTest.testReadSimpleDataAssignmentOperator(); }
} testDescription_ConfigurationTest_testReadSimpleDataAssignmentOperator;

static class TestDescription_ConfigurationTest_testReadCommentedData : public CxxTest::RealTestDescription {
public:
 TestDescription_ConfigurationTest_testReadCommentedData() : CxxTest::RealTestDescription( Tests_ConfigurationTest, suiteDescription_ConfigurationTest, 147, "testReadCommentedData" ) {}
 void runTest() { suite_ConfigurationTest.testReadCommentedData(); }
} testDescription_ConfigurationTest_testReadCommentedData;

static class TestDescription_ConfigurationTest_testReadCommentedDataCaseInsensitive : public CxxTest::RealTestDescription {
public:
 TestDescription_ConfigurationTest_testReadCommentedDataCaseInsensitive() : CxxTest::RealTestDescription( Tests_ConfigurationTest, suiteDescription_ConfigurationTest, 187, "testReadCommentedDataCaseInsensitive" ) {}
 void runTest() { suite_ConfigurationTest.testReadCommentedDataCaseInsensitive(); }
} testDescription_ConfigurationTest_testReadCommentedDataCaseInsensitive;

static class TestDescription_ConfigurationTest_testReadCommentedDataSubset : public CxxTest::RealTestDescription {
public:
 TestDescription_ConfigurationTest_testReadCommentedDataSubset() : CxxTest::RealTestDescription( Tests_ConfigurationTest, suiteDescription_ConfigurationTest, 219, "testReadCommentedDataSubset" ) {}
 void runTest() { suite_ConfigurationTest.testReadCommentedDataSubset(); }
} testDescription_ConfigurationTest_testReadCommentedDataSubset;

#include <cxxtest/Root.cpp>

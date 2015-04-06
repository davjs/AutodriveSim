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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/supercomponent/SupercomponentClientModuleTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/supercomponent/testsuites/SupercomponentClientModuleTestSuite.h"

static SupercomponentClientModuleTest suite_SupercomponentClientModuleTest;

static CxxTest::List Tests_SupercomponentClientModuleTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SupercomponentClientModuleTest( "/home/david/AutoDriveSim2/supercomponent/testsuites/SupercomponentClientModuleTestSuite.h", 117, "SupercomponentClientModuleTest", suite_SupercomponentClientModuleTest, Tests_SupercomponentClientModuleTest );

static class TestDescription_SupercomponentClientModuleTest_testServerInformation : public CxxTest::RealTestDescription {
public:
 TestDescription_SupercomponentClientModuleTest_testServerInformation() : CxxTest::RealTestDescription( Tests_SupercomponentClientModuleTest, suiteDescription_SupercomponentClientModuleTest, 136, "testServerInformation" ) {}
 void runTest() { suite_SupercomponentClientModuleTest.testServerInformation(); }
} testDescription_SupercomponentClientModuleTest_testServerInformation;

static class TestDescription_SupercomponentClientModuleTest_testRegularConfiguration : public CxxTest::RealTestDescription {
public:
 TestDescription_SupercomponentClientModuleTest_testRegularConfiguration() : CxxTest::RealTestDescription( Tests_SupercomponentClientModuleTest, suiteDescription_SupercomponentClientModuleTest, 160, "testRegularConfiguration" ) {}
 void runTest() { suite_SupercomponentClientModuleTest.testRegularConfiguration(); }
} testDescription_SupercomponentClientModuleTest_testRegularConfiguration;

static class TestDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithID : public CxxTest::RealTestDescription {
public:
 TestDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithID() : CxxTest::RealTestDescription( Tests_SupercomponentClientModuleTest, suiteDescription_SupercomponentClientModuleTest, 241, "testConfigurationForModuleWithID" ) {}
 void runTest() { suite_SupercomponentClientModuleTest.testConfigurationForModuleWithID(); }
} testDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithID;

static class TestDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithIDEmptyConfiguration : public CxxTest::RealTestDescription {
public:
 TestDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithIDEmptyConfiguration() : CxxTest::RealTestDescription( Tests_SupercomponentClientModuleTest, suiteDescription_SupercomponentClientModuleTest, 318, "testConfigurationForModuleWithIDEmptyConfiguration" ) {}
 void runTest() { suite_SupercomponentClientModuleTest.testConfigurationForModuleWithIDEmptyConfiguration(); }
} testDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithIDEmptyConfiguration;

#include <cxxtest/Root.cpp>

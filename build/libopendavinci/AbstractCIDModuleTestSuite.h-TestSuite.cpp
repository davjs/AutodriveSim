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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/AbstractCIDModuleTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/AbstractCIDModuleTestSuite.h"

static AbstractCIDModuleTest suite_AbstractCIDModuleTest;

static CxxTest::List Tests_AbstractCIDModuleTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AbstractCIDModuleTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/AbstractCIDModuleTestSuite.h", 94, "AbstractCIDModuleTest", suite_AbstractCIDModuleTest, Tests_AbstractCIDModuleTest );

static class TestDescription_AbstractCIDModuleTest_testAbstractCIDModule : public CxxTest::RealTestDescription {
public:
 TestDescription_AbstractCIDModuleTest_testAbstractCIDModule() : CxxTest::RealTestDescription( Tests_AbstractCIDModuleTest, suiteDescription_AbstractCIDModuleTest, 96, "testAbstractCIDModule" ) {}
 void runTest() { suite_AbstractCIDModuleTest.testAbstractCIDModule(); }
} testDescription_AbstractCIDModuleTest_testAbstractCIDModule;

static class TestDescription_AbstractCIDModuleTest_testAbstractCIDModuleCID : public CxxTest::RealTestDescription {
public:
 TestDescription_AbstractCIDModuleTest_testAbstractCIDModuleCID() : CxxTest::RealTestDescription( Tests_AbstractCIDModuleTest, suiteDescription_AbstractCIDModuleTest, 122, "testAbstractCIDModuleCID" ) {}
 void runTest() { suite_AbstractCIDModuleTest.testAbstractCIDModuleCID(); }
} testDescription_AbstractCIDModuleTest_testAbstractCIDModuleCID;

static class TestDescription_AbstractCIDModuleTest_testAbstractCIDModuleWrongCID1 : public CxxTest::RealTestDescription {
public:
 TestDescription_AbstractCIDModuleTest_testAbstractCIDModuleWrongCID1() : CxxTest::RealTestDescription( Tests_AbstractCIDModuleTest, suiteDescription_AbstractCIDModuleTest, 141, "testAbstractCIDModuleWrongCID1" ) {}
 void runTest() { suite_AbstractCIDModuleTest.testAbstractCIDModuleWrongCID1(); }
} testDescription_AbstractCIDModuleTest_testAbstractCIDModuleWrongCID1;

static class TestDescription_AbstractCIDModuleTest_testAbstractCIDModuleWrongCID2 : public CxxTest::RealTestDescription {
public:
 TestDescription_AbstractCIDModuleTest_testAbstractCIDModuleWrongCID2() : CxxTest::RealTestDescription( Tests_AbstractCIDModuleTest, suiteDescription_AbstractCIDModuleTest, 167, "testAbstractCIDModuleWrongCID2" ) {}
 void runTest() { suite_AbstractCIDModuleTest.testAbstractCIDModuleWrongCID2(); }
} testDescription_AbstractCIDModuleTest_testAbstractCIDModuleWrongCID2;

static class TestDescription_AbstractCIDModuleTest_testKillAbstractCIDModule : public CxxTest::RealTestDescription {
public:
 TestDescription_AbstractCIDModuleTest_testKillAbstractCIDModule() : CxxTest::RealTestDescription( Tests_AbstractCIDModuleTest, suiteDescription_AbstractCIDModuleTest, 192, "testKillAbstractCIDModule" ) {}
 void runTest() { suite_AbstractCIDModuleTest.testKillAbstractCIDModule(); }
} testDescription_AbstractCIDModuleTest_testKillAbstractCIDModule;

static class TestDescription_AbstractCIDModuleTest_testExceptionAbstractCIDModule : public CxxTest::RealTestDescription {
public:
 TestDescription_AbstractCIDModuleTest_testExceptionAbstractCIDModule() : CxxTest::RealTestDescription( Tests_AbstractCIDModuleTest, suiteDescription_AbstractCIDModuleTest, 238, "testExceptionAbstractCIDModule" ) {}
 void runTest() { suite_AbstractCIDModuleTest.testExceptionAbstractCIDModule(); }
} testDescription_AbstractCIDModuleTest_testExceptionAbstractCIDModule;

#include <cxxtest/Root.cpp>

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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/SharedPointerTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/SharedPointerTestSuite.h"

static SharedPointerTest suite_SharedPointerTest;

static CxxTest::List Tests_SharedPointerTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SharedPointerTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/SharedPointerTestSuite.h", 45, "SharedPointerTest", suite_SharedPointerTest, Tests_SharedPointerTest );

static class TestDescription_SharedPointerTest_testCreateSharedPointer : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedPointerTest_testCreateSharedPointer() : CxxTest::RealTestDescription( Tests_SharedPointerTest, suiteDescription_SharedPointerTest, 47, "testCreateSharedPointer" ) {}
 void runTest() { suite_SharedPointerTest.testCreateSharedPointer(); }
} testDescription_SharedPointerTest_testCreateSharedPointer;

static class TestDescription_SharedPointerTest_testCreateDestroySharedPointer : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedPointerTest_testCreateDestroySharedPointer() : CxxTest::RealTestDescription( Tests_SharedPointerTest, suiteDescription_SharedPointerTest, 61, "testCreateDestroySharedPointer" ) {}
 void runTest() { suite_SharedPointerTest.testCreateDestroySharedPointer(); }
} testDescription_SharedPointerTest_testCreateDestroySharedPointer;

static class TestDescription_SharedPointerTest_testCreateDestroySharedPointerUsingCopyConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedPointerTest_testCreateDestroySharedPointerUsingCopyConstructor() : CxxTest::RealTestDescription( Tests_SharedPointerTest, suiteDescription_SharedPointerTest, 78, "testCreateDestroySharedPointerUsingCopyConstructor" ) {}
 void runTest() { suite_SharedPointerTest.testCreateDestroySharedPointerUsingCopyConstructor(); }
} testDescription_SharedPointerTest_testCreateDestroySharedPointerUsingCopyConstructor;

static class TestDescription_SharedPointerTest_testCreateDestroySharedPointerUsingAssignmentOperator : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedPointerTest_testCreateDestroySharedPointerUsingAssignmentOperator() : CxxTest::RealTestDescription( Tests_SharedPointerTest, suiteDescription_SharedPointerTest, 101, "testCreateDestroySharedPointerUsingAssignmentOperator" ) {}
 void runTest() { suite_SharedPointerTest.testCreateDestroySharedPointerUsingAssignmentOperator(); }
} testDescription_SharedPointerTest_testCreateDestroySharedPointerUsingAssignmentOperator;

static class TestDescription_SharedPointerTest_testCreateAndKeepSharedPointerUsingCopyConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedPointerTest_testCreateAndKeepSharedPointerUsingCopyConstructor() : CxxTest::RealTestDescription( Tests_SharedPointerTest, suiteDescription_SharedPointerTest, 124, "testCreateAndKeepSharedPointerUsingCopyConstructor" ) {}
 void runTest() { suite_SharedPointerTest.testCreateAndKeepSharedPointerUsingCopyConstructor(); }
} testDescription_SharedPointerTest_testCreateAndKeepSharedPointerUsingCopyConstructor;

static class TestDescription_SharedPointerTest_testCreateAndKeepSharedPointerUsingAssignmentOperator : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedPointerTest_testCreateAndKeepSharedPointerUsingAssignmentOperator() : CxxTest::RealTestDescription( Tests_SharedPointerTest, suiteDescription_SharedPointerTest, 151, "testCreateAndKeepSharedPointerUsingAssignmentOperator" ) {}
 void runTest() { suite_SharedPointerTest.testCreateAndKeepSharedPointerUsingAssignmentOperator(); }
} testDescription_SharedPointerTest_testCreateAndKeepSharedPointerUsingAssignmentOperator;

static class TestDescription_SharedPointerTest_testSharedPointerInsideSTL : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedPointerTest_testSharedPointerInsideSTL() : CxxTest::RealTestDescription( Tests_SharedPointerTest, suiteDescription_SharedPointerTest, 179, "testSharedPointerInsideSTL" ) {}
 void runTest() { suite_SharedPointerTest.testSharedPointerInsideSTL(); }
} testDescription_SharedPointerTest_testSharedPointerInsideSTL;

static class TestDescription_SharedPointerTest_testSharedPointerInsideSTLAndCopy : public CxxTest::RealTestDescription {
public:
 TestDescription_SharedPointerTest_testSharedPointerInsideSTLAndCopy() : CxxTest::RealTestDescription( Tests_SharedPointerTest, suiteDescription_SharedPointerTest, 214, "testSharedPointerInsideSTLAndCopy" ) {}
 void runTest() { suite_SharedPointerTest.testSharedPointerInsideSTLAndCopy(); }
} testDescription_SharedPointerTest_testSharedPointerInsideSTLAndCopy;

#include <cxxtest/Root.cpp>

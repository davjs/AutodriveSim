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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/hesperia/libhesperia/QuaternionTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/QuaternionTestSuite.h"

static QuaternionTest suite_QuaternionTest;

static CxxTest::List Tests_QuaternionTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_QuaternionTest( "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/QuaternionTestSuite.h", 39, "QuaternionTest", suite_QuaternionTest, Tests_QuaternionTest );

static class TestDescription_QuaternionTest_testGetterSetter : public CxxTest::RealTestDescription {
public:
 TestDescription_QuaternionTest_testGetterSetter() : CxxTest::RealTestDescription( Tests_QuaternionTest, suiteDescription_QuaternionTest, 42, "testGetterSetter" ) {}
 void runTest() { suite_QuaternionTest.testGetterSetter(); }
} testDescription_QuaternionTest_testGetterSetter;

static class TestDescription_QuaternionTest_testSerialization : public CxxTest::RealTestDescription {
public:
 TestDescription_QuaternionTest_testSerialization() : CxxTest::RealTestDescription( Tests_QuaternionTest, suiteDescription_QuaternionTest, 60, "testSerialization" ) {}
 void runTest() { suite_QuaternionTest.testSerialization(); }
} testDescription_QuaternionTest_testSerialization;

static class TestDescription_QuaternionTest_testMultiply : public CxxTest::RealTestDescription {
public:
 TestDescription_QuaternionTest_testMultiply() : CxxTest::RealTestDescription( Tests_QuaternionTest, suiteDescription_QuaternionTest, 99, "testMultiply" ) {}
 void runTest() { suite_QuaternionTest.testMultiply(); }
} testDescription_QuaternionTest_testMultiply;

static class TestDescription_QuaternionTest_testInverse : public CxxTest::RealTestDescription {
public:
 TestDescription_QuaternionTest_testInverse() : CxxTest::RealTestDescription( Tests_QuaternionTest, suiteDescription_QuaternionTest, 130, "testInverse" ) {}
 void runTest() { suite_QuaternionTest.testInverse(); }
} testDescription_QuaternionTest_testInverse;

static class TestDescription_QuaternionTest_testConjugate : public CxxTest::RealTestDescription {
public:
 TestDescription_QuaternionTest_testConjugate() : CxxTest::RealTestDescription( Tests_QuaternionTest, suiteDescription_QuaternionTest, 145, "testConjugate" ) {}
 void runTest() { suite_QuaternionTest.testConjugate(); }
} testDescription_QuaternionTest_testConjugate;

static class TestDescription_QuaternionTest_testFromAxis : public CxxTest::RealTestDescription {
public:
 TestDescription_QuaternionTest_testFromAxis() : CxxTest::RealTestDescription( Tests_QuaternionTest, suiteDescription_QuaternionTest, 160, "testFromAxis" ) {}
 void runTest() { suite_QuaternionTest.testFromAxis(); }
} testDescription_QuaternionTest_testFromAxis;

#include <cxxtest/Root.cpp>

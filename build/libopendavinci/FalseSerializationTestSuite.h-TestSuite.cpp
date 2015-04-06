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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/FalseSerializationTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/FalseSerializationTestSuite.h"

static FalseSerializationTest suite_FalseSerializationTest;

static CxxTest::List Tests_FalseSerializationTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FalseSerializationTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/FalseSerializationTestSuite.h", 107, "FalseSerializationTest", suite_FalseSerializationTest, Tests_FalseSerializationTest );

static class TestDescription_FalseSerializationTest_testSerializationDeserialization : public CxxTest::RealTestDescription {
public:
 TestDescription_FalseSerializationTest_testSerializationDeserialization() : CxxTest::RealTestDescription( Tests_FalseSerializationTest, suiteDescription_FalseSerializationTest, 109, "testSerializationDeserialization" ) {}
 void runTest() { suite_FalseSerializationTest.testSerializationDeserialization(); }
} testDescription_FalseSerializationTest_testSerializationDeserialization;

static class TestDescription_FalseSerializationTest_testTimeStamp35 : public CxxTest::RealTestDescription {
public:
 TestDescription_FalseSerializationTest_testTimeStamp35() : CxxTest::RealTestDescription( Tests_FalseSerializationTest, suiteDescription_FalseSerializationTest, 128, "testTimeStamp35" ) {}
 void runTest() { suite_FalseSerializationTest.testTimeStamp35(); }
} testDescription_FalseSerializationTest_testTimeStamp35;

#include <cxxtest/Root.cpp>

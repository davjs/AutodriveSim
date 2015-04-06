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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/SerializationTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/SerializationTestSuite.h"

static SerializationTest suite_SerializationTest;

static CxxTest::List Tests_SerializationTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SerializationTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/SerializationTestSuite.h", 131, "SerializationTest", suite_SerializationTest, Tests_SerializationTest );

static class TestDescription_SerializationTest_testSerializationDeserialization : public CxxTest::RealTestDescription {
public:
 TestDescription_SerializationTest_testSerializationDeserialization() : CxxTest::RealTestDescription( Tests_SerializationTest, suiteDescription_SerializationTest, 133, "testSerializationDeserialization" ) {}
 void runTest() { suite_SerializationTest.testSerializationDeserialization(); }
} testDescription_SerializationTest_testSerializationDeserialization;

static class TestDescription_SerializationTest_testArraySerialisation : public CxxTest::RealTestDescription {
public:
 TestDescription_SerializationTest_testArraySerialisation() : CxxTest::RealTestDescription( Tests_SerializationTest, suiteDescription_SerializationTest, 156, "testArraySerialisation" ) {}
 void runTest() { suite_SerializationTest.testArraySerialisation(); }
} testDescription_SerializationTest_testArraySerialisation;

#include <cxxtest/Root.cpp>

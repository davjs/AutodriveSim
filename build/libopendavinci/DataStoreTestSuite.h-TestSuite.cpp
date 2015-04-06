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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/DataStoreTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/DataStoreTestSuite.h"

static DataStoreTest suite_DataStoreTest;

static CxxTest::List Tests_DataStoreTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DataStoreTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/DataStoreTestSuite.h", 172, "DataStoreTest", suite_DataStoreTest, Tests_DataStoreTest );

static class TestDescription_DataStoreTest_testDataStore : public CxxTest::RealTestDescription {
public:
 TestDescription_DataStoreTest_testDataStore() : CxxTest::RealTestDescription( Tests_DataStoreTest, suiteDescription_DataStoreTest, 175, "testDataStore" ) {}
 void runTest() { suite_DataStoreTest.testDataStore(); }
} testDescription_DataStoreTest_testDataStore;

static class TestDescription_DataStoreTest_testMassData : public CxxTest::RealTestDescription {
public:
 TestDescription_DataStoreTest_testMassData() : CxxTest::RealTestDescription( Tests_DataStoreTest, suiteDescription_DataStoreTest, 196, "testMassData" ) {}
 void runTest() { suite_DataStoreTest.testMassData(); }
} testDescription_DataStoreTest_testMassData;

static class TestDescription_DataStoreTest_testSerializationDeserialization : public CxxTest::RealTestDescription {
public:
 TestDescription_DataStoreTest_testSerializationDeserialization() : CxxTest::RealTestDescription( Tests_DataStoreTest, suiteDescription_DataStoreTest, 241, "testSerializationDeserialization" ) {}
 void runTest() { suite_DataStoreTest.testSerializationDeserialization(); }
} testDescription_DataStoreTest_testSerializationDeserialization;

static class TestDescription_DataStoreTest_testDataStoreForDataExchange : public CxxTest::RealTestDescription {
public:
 TestDescription_DataStoreTest_testDataStoreForDataExchange() : CxxTest::RealTestDescription( Tests_DataStoreTest, suiteDescription_DataStoreTest, 270, "testDataStoreForDataExchange" ) {}
 void runTest() { suite_DataStoreTest.testDataStoreForDataExchange(); }
} testDescription_DataStoreTest_testDataStoreForDataExchange;

static class TestDescription_DataStoreTest_testSerializationDeserializationWithFileBackend : public CxxTest::RealTestDescription {
public:
 TestDescription_DataStoreTest_testSerializationDeserializationWithFileBackend() : CxxTest::RealTestDescription( Tests_DataStoreTest, suiteDescription_DataStoreTest, 315, "testSerializationDeserializationWithFileBackend" ) {}
 void runTest() { suite_DataStoreTest.testSerializationDeserializationWithFileBackend(); }
} testDescription_DataStoreTest_testSerializationDeserializationWithFileBackend;

#include <cxxtest/Root.cpp>

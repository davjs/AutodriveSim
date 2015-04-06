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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/hesperia/libhesperia/ContouredObjectTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/ContouredObjectTestSuite.h"

static ContouredObjectTest suite_ContouredObjectTest;

static CxxTest::List Tests_ContouredObjectTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ContouredObjectTest( "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/ContouredObjectTestSuite.h", 36, "ContouredObjectTest", suite_ContouredObjectTest, Tests_ContouredObjectTest );

static class TestDescription_ContouredObjectTest_testPointShapedObject : public CxxTest::RealTestDescription {
public:
 TestDescription_ContouredObjectTest_testPointShapedObject() : CxxTest::RealTestDescription( Tests_ContouredObjectTest, suiteDescription_ContouredObjectTest, 38, "testPointShapedObject" ) {}
 void runTest() { suite_ContouredObjectTest.testPointShapedObject(); }
} testDescription_ContouredObjectTest_testPointShapedObject;

#include <cxxtest/Root.cpp>

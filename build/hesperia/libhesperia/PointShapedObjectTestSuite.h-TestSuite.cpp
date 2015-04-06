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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/hesperia/libhesperia/PointShapedObjectTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/PointShapedObjectTestSuite.h"

static PointShapedObjectTest suite_PointShapedObjectTest;

static CxxTest::List Tests_PointShapedObjectTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_PointShapedObjectTest( "/home/david/AutoDriveSim2/hesperia/libhesperia/testsuites/PointShapedObjectTestSuite.h", 35, "PointShapedObjectTest", suite_PointShapedObjectTest, Tests_PointShapedObjectTest );

static class TestDescription_PointShapedObjectTest_testPointShapedObject : public CxxTest::RealTestDescription {
public:
 TestDescription_PointShapedObjectTest_testPointShapedObject() : CxxTest::RealTestDescription( Tests_PointShapedObjectTest, suiteDescription_PointShapedObjectTest, 37, "testPointShapedObject" ) {}
 void runTest() { suite_PointShapedObjectTest.testPointShapedObject(); }
} testDescription_PointShapedObjectTest_testPointShapedObject;

#include <cxxtest/Root.cpp>

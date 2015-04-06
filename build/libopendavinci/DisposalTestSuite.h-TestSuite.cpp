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
 return CxxTest::XmlFilePrinter("/home/david/AutoDriveSim2/build/libopendavinci/DisposalTestSuite.h-TestSuite.cpp-TestSuiteReport.xml").run();
}
#include "/home/david/AutoDriveSim2/libopendavinci/testsuites/DisposalTestSuite.h"

static DisposalTest suite_DisposalTest;

static CxxTest::List Tests_DisposalTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DisposalTest( "/home/david/AutoDriveSim2/libopendavinci/testsuites/DisposalTestSuite.h", 39, "DisposalTest", suite_DisposalTest, Tests_DisposalTest );

static class TestDescription_DisposalTest_testDisposal : public CxxTest::RealTestDescription {
public:
 TestDescription_DisposalTest_testDisposal() : CxxTest::RealTestDescription( Tests_DisposalTest, suiteDescription_DisposalTest, 41, "testDisposal" ) {}
 void runTest() { suite_DisposalTest.testDisposal(); }
} testDescription_DisposalTest_testDisposal;

#include <cxxtest/Root.cpp>

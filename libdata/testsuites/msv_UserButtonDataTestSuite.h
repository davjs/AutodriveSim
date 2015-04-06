/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef MSV_USERBUTTONDATA_TESTSUITE_H
#define MSV_USERBUTTONDATA_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"
#include "core/StringToolbox.h"

#include "GeneratedHeaders_Data.h"


class msv_UserButtonData_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace msv;
	
			UserButtonData obj1;
			TS_ASSERT_DELTA(obj1.getDuration(), 0.0, 1e-5);
	
			obj1.setDuration(1.0);
	
			TS_ASSERT_DELTA(obj1.getDuration(), 1.0, 1e-5);
		}
	
		void testCreateAndCopyObject() {
			using namespace msv;
	
			UserButtonData obj1;
			TS_ASSERT_DELTA(obj1.getDuration(), 0.0, 1e-5);
	
			UserButtonData obj2(obj1);
			TS_ASSERT_DELTA(obj1.getDuration(), obj2.getDuration(), 1e-5);
	
			obj1.setDuration(1.0);
	
			TS_ASSERT_DELTA(obj1.getDuration(), 1.0, 1e-5);
	
			UserButtonData obj3(obj1);
			TS_ASSERT_DELTA(obj1.getDuration(), obj3.getDuration(), 1e-5);
	
			TS_ASSERT_DELTA(obj3.getDuration(), 1.0, 1e-5);
	
			TS_ASSERT(core::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace msv;
	
			UserButtonData obj1;
			TS_ASSERT_DELTA(obj1.getDuration(), 0.0, 1e-5);
	
			UserButtonData obj2;
			TS_ASSERT_DELTA(obj2.getDuration(), 0.0, 1e-5);
	
			obj1.setDuration(1.0);
	
			TS_ASSERT_DELTA(obj1.getDuration(), 1.0, 1e-5);
	
			obj2 = obj1;
			TS_ASSERT_DELTA(obj1.getDuration(), obj2.getDuration(), 1e-5);
	
			TS_ASSERT_DELTA(obj2.getDuration(), 1.0, 1e-5);
	
			TS_ASSERT(core::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace msv;
	
			UserButtonData obj1;
			TS_ASSERT_DELTA(obj1.getDuration(), 0.0, 1e-5);
	
			UserButtonData obj2;
			TS_ASSERT_DELTA(obj2.getDuration(), 0.0, 1e-5);
	
			obj1.setDuration(1.0);
	
			TS_ASSERT_DELTA(obj1.getDuration(), 1.0, 1e-5);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT_DELTA(obj1.getDuration(), obj2.getDuration(), 1e-5);
	
			TS_ASSERT_DELTA(obj2.getDuration(), 1.0, 1e-5);
	
			TS_ASSERT(core::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*MSV_USERBUTTONDATA_TESTSUITE_H*/

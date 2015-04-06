/**
 * hesperia - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef HESPERIA_QUATERNIONTESTSUITE_H_
#define HESPERIA_QUATERNIONTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <cmath>
#include <string>
#include <sstream>

#include "core/data/Constants.h"
#include "core/data/environment/Matrix3x3.h"
#include "core/data/environment/Point3.h"
#include "hesperia/data/environment/Quaternion.h"

using namespace std;
using namespace core::data;
using namespace core::data::environment;
using namespace hesperia::data::environment;

class QuaternionTest : public CxxTest::TestSuite {
    public:

        void testGetterSetter() {
            Quaternion q;
            TS_ASSERT_DELTA(q.getW(), 1, 1e-5);
            TS_ASSERT_DELTA(q.getX(), 0, 1e-5);
            TS_ASSERT_DELTA(q.getY(), 0, 1e-5);
            TS_ASSERT_DELTA(q.getZ(), 0, 1e-5);

            q.setW(-1.1);
            q.setX(1.1);
            q.setY(2.2);
            q.setZ(3.3);

            TS_ASSERT_DELTA(q.getW(), -1.1, 1e-5);
            TS_ASSERT_DELTA(q.getX(), 1.1, 1e-5);
            TS_ASSERT_DELTA(q.getY(), 2.2, 1e-5);
            TS_ASSERT_DELTA(q.getZ(), 3.3, 1e-5);
        }

        void testSerialization() {
            Quaternion q;
            TS_ASSERT_DELTA(q.getW(), 1, 1e-5);
            TS_ASSERT_DELTA(q.getX(), 0, 1e-5);
            TS_ASSERT_DELTA(q.getY(), 0, 1e-5);
            TS_ASSERT_DELTA(q.getZ(), 0, 1e-5);

            q.setW(-1.123456789);
            q.setX(1.1);
            q.setY(2.2);
            q.setZ(3.3);

            TS_ASSERT_DELTA(q.getW(), -1.123456789, 1e-9);
            TS_ASSERT_DELTA(q.getX(), 1.1, 1e-5);
            TS_ASSERT_DELTA(q.getY(), 2.2, 1e-5);
            TS_ASSERT_DELTA(q.getZ(), 3.3, 1e-5);

            stringstream s;
            s << q;

            Quaternion q2;

            TS_ASSERT_DELTA(q2.getW(), 1, 1e-5);
            TS_ASSERT_DELTA(q2.getX(), 0, 1e-5);
            TS_ASSERT_DELTA(q2.getY(), 0, 1e-5);
            TS_ASSERT_DELTA(q2.getZ(), 0, 1e-5);

            TS_ASSERT(q != q2);

            s >> q2;

            TS_ASSERT_DELTA(q.getW(), -1.123456789, 1e-9);
            TS_ASSERT_DELTA(q.getX(), 1.1, 1e-5);
            TS_ASSERT_DELTA(q.getY(), 2.2, 1e-5);
            TS_ASSERT_DELTA(q.getZ(), 3.3, 1e-5);

            TS_ASSERT(q == q2);
        }

        void testMultiply() {
            Quaternion q(1, 2, 3, 4);
            TS_ASSERT_DELTA(q.getW(), 1, 1e-5);
            TS_ASSERT_DELTA(q.getX(), 2, 1e-5);
            TS_ASSERT_DELTA(q.getY(), 3, 1e-5);
            TS_ASSERT_DELTA(q.getZ(), 4, 1e-5);

            Quaternion q2(5, 6, 7, 8);
            TS_ASSERT_DELTA(q2.getW(), 5, 1e-5);
            TS_ASSERT_DELTA(q2.getX(), 6, 1e-5);
            TS_ASSERT_DELTA(q2.getY(), 7, 1e-5);
            TS_ASSERT_DELTA(q2.getZ(), 8, 1e-5);

            Quaternion q3;
            TS_ASSERT_DELTA(q3.getW(), 1, 1e-5);
            TS_ASSERT_DELTA(q3.getX(), 0, 1e-5);
            TS_ASSERT_DELTA(q3.getY(), 0, 1e-5);
            TS_ASSERT_DELTA(q3.getZ(), 0, 1e-5);

            q3 = q * q2;

            q *= q2;

            TS_ASSERT(q != q2);
            TS_ASSERT(q3 != q2);
            TS_ASSERT(q == q3);

            TS_ASSERT(q.toString() == "(-60; 12i; 30j; 24k)");
            TS_ASSERT(q3.toString() == "(-60; 12i; 30j; 24k)");
        }

        void testInverse() {
            Quaternion q(1, 2, 3, 4);
            TS_ASSERT_DELTA(q.getW(), 1, 1e-5);
            TS_ASSERT_DELTA(q.getX(), 2, 1e-5);
            TS_ASSERT_DELTA(q.getY(), 3, 1e-5);
            TS_ASSERT_DELTA(q.getZ(), 4, 1e-5);

            q.inverse();

            TS_ASSERT_DELTA(q.getW(), 0.182574, 1e-6);
            TS_ASSERT_DELTA(q.getX(), -0.365148, 1e-6);
            TS_ASSERT_DELTA(q.getY(), -0.547723, 1e-6);
            TS_ASSERT_DELTA(q.getZ(), -0.730297, 1e-6);
        }

        void testConjugate() {
            Quaternion q(1, 2, 3, 4);
            TS_ASSERT_DELTA(q.getW(), 1, 1e-5);
            TS_ASSERT_DELTA(q.getX(), 2, 1e-5);
            TS_ASSERT_DELTA(q.getY(), 3, 1e-5);
            TS_ASSERT_DELTA(q.getZ(), 4, 1e-5);

            q.conjugate();

            TS_ASSERT_DELTA(q.getW(), 1, 1e-5);
            TS_ASSERT_DELTA(q.getX(), -2, 1e-5);
            TS_ASSERT_DELTA(q.getY(), -3, 1e-5);
            TS_ASSERT_DELTA(q.getZ(), -4, 1e-5);
        }

        void testFromAxis() {
            Quaternion q;
            TS_ASSERT_DELTA(q.getW(), 1, 1e-5);
            TS_ASSERT_DELTA(q.getX(), 0, 1e-5);
            TS_ASSERT_DELTA(q.getY(), 0, 1e-5);
            TS_ASSERT_DELTA(q.getZ(), 0, 1e-5);

            const Point3 dir(1, 0, 0);
            q.transform(90.0/180.0 * Constants::PI, dir);

            TS_ASSERT_DELTA(q.getW(), 0.707107, 1e-6);
            TS_ASSERT_DELTA(q.getX(), -0.707107, 1e-6);
            TS_ASSERT_DELTA(q.getY(), 0, 1e-6);
            TS_ASSERT_DELTA(q.getZ(), 0, 1e-6);

            Matrix3x3 m = q.transformToMatrix3x3();

            TS_ASSERT_DELTA(m.getXX(), 1, 1e-5);
            TS_ASSERT_DELTA(m.getXY(), 0, 1e-5);
            TS_ASSERT_DELTA(m.getXZ(), 0, 1e-5);

            TS_ASSERT_DELTA(m.getYX(), 0, 1e-5);
            TS_ASSERT_DELTA(m.getYY(), 0, 1e-5);
            TS_ASSERT_DELTA(m.getYZ(), -1, 1e-5);

            TS_ASSERT_DELTA(m.getZX(), 0, 1e-5);
            TS_ASSERT_DELTA(m.getZY(), 1, 1e-5);
            TS_ASSERT_DELTA(m.getZZ(), 0, 1e-5);
        }
};

#endif /*HESPERIA_QUATERNIONTESTSUITE_H_*/

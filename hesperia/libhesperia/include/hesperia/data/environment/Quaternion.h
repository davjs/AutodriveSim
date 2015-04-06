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

#ifndef HESPERIA_DATA_ENVIRONMENT_QUATERNION_H_
#define HESPERIA_DATA_ENVIRONMENT_QUATERNION_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/data/SerializableData.h"
#include "core/data/environment/Matrix3x3.h"
#include "core/data/environment/Point3.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;

            using namespace core::data::environment;

            /**
             * This class represents a quaternion.
             */
            class OPENDAVINCI_API Quaternion : public core::data::SerializableData {
                private:
                    const static double EPSILON;

                public:
                    Quaternion();

                    /**
                     * Constructor for the Quaternion's components.
                     *
                     * @param w
                     * @param x
                     * @param y
                     * @param z
                     */
                    Quaternion(const double &w, const double &x, const double &y, const double &z);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Quaternion(const Quaternion &obj);

                    virtual ~Quaternion();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Quaternion& operator=(const Quaternion &obj);

                    /**
                     * This method returns the w component.
                     *
                     * @return w-component.
                     */
                    double getW() const;

                    /**
                     * This method sets the w component.
                     *
                     * @param w.
                     */
                    void setW(const double &w);

                    /**
                     * This method returns the x component.
                     *
                     * @return x-component.
                     */
                    double getX() const;

                    /**
                     * This method sets the x component.
                     *
                     * @param x.
                     */
                    void setX(const double &x);

                    /**
                     * This method returns the y component.
                     *
                     * @return y-component.
                     */
                    double getY() const;

                    /**
                     * This method sets the y component.
                     *
                     * @param y.
                     */
                    void setY(const double &y);

                    /**
                     * This method returns the z component.
                     *
                     * @return z-component.
                     */
                    double getZ() const;

                    /**
                     * This method sets the z component.
                     *
                     * @param z.
                     */
                    void setZ(const double &z);

                    /**
                     * This operator multiplies this Quaternion with another Quaternion
                     * and returns a new instance.
                     *
                     * @param q Another Quaternion.
                     * @return New object.
                     */
                    Quaternion operator*(const Quaternion &q) const;

                    /**
                     * This operator multiplies this Quaternion with another Quaternion
                     * and returns a the modified instance.
                     *
                     * @param q Another Quaternion.
                     * @return Modified instance.
                     */
                    Quaternion& operator*=(const Quaternion &q);

                    /**
                     * This method returns the conjugate Quaternion.
                     *
                     * @return Modified instance.
                     */
                    Quaternion& conjugate();

                    /**
                     * This method returns the inverse Quaternion.
                     *
                     * @return Modified instance.
                     */
                    Quaternion& inverse();

                    /**
                     * This method normalizes the Quaternion.
                     *
                     * @return Modified instance.
                     */
                    Quaternion& normalize();

                    /**
                     * This method sets this Quaternion from a
                     * given rotation around the given axis.
                     *
                     * @param angle Angle in RAD.
                     * @param dir Direction of the axis.
                     * @return Modified instance.
                     */
                    Quaternion& transform(const double &angle, const Point3 &dir);

                    /**
                     * This method returns a 3x3 matrix representation of this Quaternion.
                     *
                     * @return Matrix3x3 describing the combined rotations.
                     */
                    Matrix3x3 transformToMatrix3x3() const;

                    /**
                     * This method returns a 4x4 matrix representation of this Quaternion
                     * into an existing one-dimensional array.
                     *
                     * @param matrix4x4 One-dimensional array for copying data.
                     */
                    void transformToMatrix4x4(double *matrix4x4) const;

                    /**
                     * This operator compares the other matrix with
                     * this instance and returns true iff both are identical,
                     * i.e. delta < 1e-10;
                     *
                     * @return true iff delta for every attribute is smaller than 1e-10
                     */
                    bool operator==(const Quaternion &other) const;

                    /**
                     * This operator is the counterpart of operator==.
                     *
                     * @return false iff delta for every attribute is smaller than 1e-10
                     */
                    bool operator!=(const Quaternion &other) const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    double m_w;
                    double m_x;
                    double m_y;
                    double m_z;
            };

        }
    }
} // hesperia::data::environment

#endif /*HESPERIA_DATA_ENVIRONMENT_QUATERNION_H_*/

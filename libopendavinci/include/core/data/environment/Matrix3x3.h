/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_DATA_ENVIRONMENT_MATRIX3X3_H_
#define OPENDAVINCI_DATA_ENVIRONMENT_MATRIX3X3_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/SerializableData.h"

namespace core {
    namespace data {
        namespace environment {

            using namespace std;

            /**
             * This class represents a 3x3 matrix and some not optimized
             * methods for computation.
             */
            class OPENDAVINCI_API Matrix3x3 : public core::data::SerializableData {
                private:
                    const static double EPSILON;

                public:
                    Matrix3x3();

                    /**
                     * Constructor.
                     *
                     * @param xx
                     * @param xy
                     * @param xz
                     *
                     * @param yx
                     * @param yy
                     * @param yz
                     *
                     * @param zx
                     * @param zy
                     * @param zz
                     */
                    Matrix3x3(const double &xx, const double &xy, const double &xz,
                              const double &yx, const double &yy, const double &yz,
                              const double &zx, const double &zy, const double &zz);

                    /**
                     * Constructor.
                     *
                     * @param s String containing the data "(xx; xy; xz; yx; yy; yz; zx; zy; zz)".
                     */
                    Matrix3x3(const string &s);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Matrix3x3(const Matrix3x3 &obj);

                    virtual ~Matrix3x3();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Matrix3x3& operator=(const Matrix3x3 &obj);

                    /**
                     * This method returns the x coordinate.
                     *
                     * @return x-coordinate.
                     */
                    double getXX() const;

                    /**
                     * This method sets the xx coordinate.
                     *
                     * @param xx.
                     */
                    void setXX(const double &xx);

                    /**
                     * This method returns the xy coordinate.
                     *
                     * @return xy-coordinate.
                     */
                    double getXY() const;

                    /**
                     * This method sets the xy coordinate.
                     *
                     * @param xy.
                     */
                    void setXY(const double &xy);

                    /**
                     * This method returns the xz coordinate.
                     *
                     * @return xz-coordinate.
                     */
                    double getXZ() const;

                    /**
                     * This method sets the xz coordinate.
                     *
                     * @param xz.
                     */
                    void setXZ(const double &xz);

                    /**
                     * This method returns the yx coordinate.
                     *
                     * @return yx-coordinate.
                     */
                    double getYX() const;

                    /**
                     * This method sets the yx coordinate.
                     *
                     * @param yx.
                     */
                    void setYX(const double &yx);

                    /**
                     * This method returns the yy coordinate.
                     *
                     * @return yy-coordinate.
                     */
                    double getYY() const;

                    /**
                     * This method sets the yy coordinate.
                     *
                     * @param yy.
                     */
                    void setYY(const double &yy);

                    /**
                     * This method returns the yz coordinate.
                     *
                     * @return yz-coordinate.
                     */
                    double getYZ() const;

                    /**
                     * This method sets the yz coordinate.
                     *
                     * @param yz.
                     */
                    void setYZ(const double &yz);

                    /**
                     * This method returns the zx coordinate.
                     *
                     * @return zx-coordinate.
                     */
                    double getZX() const;

                    /**
                     * This method sets the zx coordinate.
                     *
                     * @param zx.
                     */
                    void setZX(const double &zx);

                    /**
                     * This method returns the zy coordinate.
                     *
                     * @return zy-coordinate.
                     */
                    double getZY() const;

                    /**
                     * This method sets the zy coordinate.
                     *
                     * @param zy.
                     */
                    void setZY(const double &zy);

                    /**
                     * This method returns the zz coordinate.
                     *
                     * @return zz-coordinate.
                     */
                    double getZZ() const;

                    /**
                     * This method sets the zz coordinate.
                     *
                     * @param zz.
                     */
                    void setZZ(const double &zz);

                    /**
                     * This operator adds the other matrix with this instance
                     * to a new object of this class.
                     *
                     * @param other Other coordinate.
                     * @return New object.
                     */
                    Matrix3x3 operator+(const Matrix3x3 &other) const;

                    /**
                     * This operator adds the other matrix to this instance.
                     *
                     * @param other Other coordinate.
                     * @return Modified instance.
                     */
                    Matrix3x3& operator+=(const Matrix3x3 &other);

                    /**
                     * This operator subtracts the other matrix with this
                     * instance to a new object of this class.
                     *
                     * @param other Other coordinate.
                     * @return New object.
                     */
                    Matrix3x3 operator-(const Matrix3x3 &other) const;

                    /**
                     * This operator subtracts the other matrix from this instance.
                     *
                     * @param other Other coordinate.
                     * @return Modified instance.
                     */
                    Matrix3x3& operator-=(const Matrix3x3 &other);

                    /**
                     * This operator scales this matrix and returns
                     * a new instance.
                     *
                     * @param a Scaling factor.
                     * @return New object.
                     */
                    Matrix3x3 operator*(const double &a) const;

                    /**
                     * This operator scales this matrix and returns
                     * a the modified instance.
                     *
                     * @param a Scaling factor.
                     * @return Modified instance.
                     */
                    Matrix3x3& operator*=(const double &a);

                    /**
                     * This operator multiplies this matrix with anouther matrix
                     * and returns a new instance.
                     *
                     * @param m Another matrix.
                     * @return New object.
                     */
                    Matrix3x3 operator*(const Matrix3x3 &m) const;

                    /**
                     * This operator multiplies this matrix with anouther matrix
                     * and returns a the modified instance.
                     *
                     * @param m Another matrix.
                     * @return Modified instance.
                     */
                    Matrix3x3& operator*=(const Matrix3x3 &m);

                    /**
                     * This operator compares the other matrix with
                     * this instance and returns true iff both are identical,
                     * i.e. delta < 1e-10;
                     *
                     * @return true iff delta for every attribute is smaller than 1e-10
                     */
                    bool operator==(const Matrix3x3 &other) const;

                    /**
                     * This operator is the counterpart of operator==.
                     *
                     * @return false iff delta for every attribute is smaller than 1e-10
                     */
                    bool operator!=(const Matrix3x3 &other) const;

                    /**
                     * This method transposes this matrix.
                     *
                     * @return Reference to this instance.
                     */
                    Matrix3x3& transpose();

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    double m_xx;
                    double m_xy;
                    double m_xz;

                    double m_yx;
                    double m_yy;
                    double m_yz;

                    double m_zx;
                    double m_zy;
                    double m_zz;
            };

        }
    }
} // core::data::environment

#endif /*OPENDAVINCI_DATA_ENVIRONMENT_MATRIX3X3_H_*/

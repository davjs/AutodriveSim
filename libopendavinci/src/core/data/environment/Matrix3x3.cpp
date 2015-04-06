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

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "core/data/environment/Matrix3x3.h"

namespace core {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace core::base;

            const double Matrix3x3::EPSILON = 1e-10;

            Matrix3x3::Matrix3x3() :
                    m_xx(0),
                    m_xy(0),
                    m_xz(0),
                    m_yx(0),
                    m_yy(0),
                    m_yz(0),
                    m_zx(0),
                    m_zy(0),
                    m_zz(0) {}

            Matrix3x3::Matrix3x3(const double &xx, const double &xy, const double &xz,
                                 const double &yx, const double &yy, const double &yz,
                                 const double &zx, const double &zy, const double &zz) :
                    m_xx(xx),
                    m_xy(xy),
                    m_xz(xz),
                    m_yx(yx),
                    m_yy(yy),
                    m_yz(yz),
                    m_zx(zx),
                    m_zy(zy),
                    m_zz(zz) {}

            Matrix3x3::Matrix3x3(const string &s) :
                    m_xx(0),
                    m_xy(0),
                    m_xz(0),
                    m_yx(0),
                    m_yy(0),
                    m_yz(0),
                    m_zx(0),
                    m_zy(0),
                    m_zz(0) {
                string trimmedString(s);
                core::StringToolbox::trim(trimmedString);
                stringstream sstr(trimmedString);
                char ignore;

                sstr >> ignore; // '('
                sstr >> m_xx;

                sstr >> ignore; // ';'
                sstr >> m_xy;

                sstr >> ignore; // ';'
                sstr >> m_xz;

                sstr >> ignore; // ';'
                sstr >> m_yx;

                sstr >> ignore; // ';'
                sstr >> m_yy;

                sstr >> ignore; // ';'
                sstr >> m_yz;

                sstr >> ignore; // ';'
                sstr >> m_zx;

                sstr >> ignore; // ';'
                sstr >> m_zy;

                sstr >> ignore; // ';'
                sstr >> m_zz;
            }

            Matrix3x3::Matrix3x3(const Matrix3x3 &obj) :
                    SerializableData(),
                    m_xx(obj.m_xx),
                    m_xy(obj.m_xy),
                    m_xz(obj.m_xz),
                    m_yx(obj.m_yx),
                    m_yy(obj.m_yy),
                    m_yz(obj.m_yz),
                    m_zx(obj.m_zx),
                    m_zy(obj.m_zy),
                    m_zz(obj.m_zz) {}

            Matrix3x3::~Matrix3x3() {}

            Matrix3x3& Matrix3x3::operator=(const Matrix3x3 &obj) {
                m_xx = obj.m_xx;
                m_xy = obj.m_xy;
                m_xz = obj.m_xz;
                m_yx = obj.m_yx;
                m_yy = obj.m_yy;
                m_yz = obj.m_yz;
                m_zx = obj.m_zx;
                m_zy = obj.m_zy;
                m_zz = obj.m_zz;

                return (*this);
            }

            double Matrix3x3::getXX() const {
                return m_xx;
            }

            void Matrix3x3::setXX(const double &xx) {
                m_xx = xx;
            }

            double Matrix3x3::getXY() const {
                return m_xy;
            }

            void Matrix3x3::setXY(const double &xy) {
                m_xy = xy;
            }

            double Matrix3x3::getXZ() const {
                return m_xz;
            }

            void Matrix3x3::setXZ(const double &xz) {
                m_xz = xz;
            }

            double Matrix3x3::getYX() const {
                return m_yx;
            }

            void Matrix3x3::setYX(const double &yx) {
                m_yx = yx;
            }

            double Matrix3x3::getYY() const {
                return m_yy;
            }

            void Matrix3x3::setYY(const double &yy) {
                m_yy = yy;
            }

            double Matrix3x3::getYZ() const {
                return m_yz;
            }

            void Matrix3x3::setYZ(const double &yz) {
                m_yz = yz;
            }

            double Matrix3x3::getZX() const {
                return m_zx;
            }

            void Matrix3x3::setZX(const double &zx) {
                m_zx = zx;
            }

            double Matrix3x3::getZY() const {
                return m_zy;
            }

            void Matrix3x3::setZY(const double &zy) {
                m_zy = zy;
            }

            double Matrix3x3::getZZ() const {
                return m_zz;
            }

            void Matrix3x3::setZZ(const double &zz) {
                m_zz = zz;
            }

            Matrix3x3 Matrix3x3::operator+(const Matrix3x3 &other) const {
                Matrix3x3 m(getXX() + other.getXX(), getXY() + other.getXY(), getXZ() + other.getXZ(),
                            getYX() + other.getYX(), getYY() + other.getYY(), getYZ() + other.getYZ(),
                            getZX() + other.getZX(), getZY() + other.getZY(), getZZ() + other.getZZ());

                return m;
            }

            Matrix3x3& Matrix3x3::operator+=(const Matrix3x3 &other) {
                m_xx += other.getXX();
                m_xy += other.getXY();
                m_xz += other.getXZ();

                m_yx += other.getYX();
                m_yy += other.getYY();
                m_yz += other.getYZ();

                m_zx += other.getZX();
                m_zy += other.getZY();
                m_zz += other.getZZ();

                return (*this);
            }

            Matrix3x3 Matrix3x3::operator-(const Matrix3x3 &other) const {
                Matrix3x3 m(getXX() - other.getXX(), getXY() - other.getXY(), getXZ() - other.getXZ(),
                            getYX() - other.getYX(), getYY() - other.getYY(), getYZ() - other.getYZ(),
                            getZX() - other.getZX(), getZY() - other.getZY(), getZZ() - other.getZZ());

                return m;
            }

            Matrix3x3& Matrix3x3::operator-=(const Matrix3x3 &other) {
                m_xx -= other.getXX();
                m_xy -= other.getXY();
                m_xz -= other.getXZ();

                m_yx -= other.getYX();
                m_yy -= other.getYY();
                m_yz -= other.getYZ();

                m_zx -= other.getZX();
                m_zy -= other.getZY();
                m_zz -= other.getZZ();

                return (*this);
            }

            Matrix3x3 Matrix3x3::operator*(const double &a) const {
                Matrix3x3 m(getXX() * a, getXY() * a, getXZ() * a,
                            getYX() * a, getYY() * a, getYZ() * a,
                            getZX() * a, getZY() * a, getZZ() * a);

                return m;
            }

            Matrix3x3& Matrix3x3::operator*=(const double &a) {
                m_xx *= a;
                m_xy *= a;
                m_xz *= a;

                m_yx *= a;
                m_yy *= a;
                m_yz *= a;

                m_zx *= a;
                m_zy *= a;
                m_zz *= a;

                return (*this);
            }

            Matrix3x3 Matrix3x3::operator*(const Matrix3x3 &m) const {
                Matrix3x3 matrix;

                matrix.setXX(m_xx * m.getXX() + m_xy * m.getYX() + m_xz * m.getZX());
                matrix.setXY(m_xx * m.getXY() + m_xy * m.getYY() + m_xz * m.getZY());
                matrix.setXZ(m_xx * m.getXZ() + m_xy * m.getYZ() + m_xz * m.getZZ());

                matrix.setYX(m_yx * m.getXX() + m_yy * m.getYX() + m_yz * m.getZX());
                matrix.setYY(m_yx * m.getXY() + m_yy * m.getYY() + m_yz * m.getZY());
                matrix.setYZ(m_yx * m.getXZ() + m_yy * m.getYZ() + m_yz * m.getZZ());

                matrix.setZX(m_zx * m.getXX() + m_zy * m.getYX() + m_zz * m.getZX());
                matrix.setZY(m_zx * m.getXY() + m_zy * m.getYY() + m_zz * m.getZY());
                matrix.setZZ(m_zx * m.getXZ() + m_zy * m.getYZ() + m_zz * m.getZZ());

                return matrix;
            }

            Matrix3x3& Matrix3x3::operator*=(const Matrix3x3 &m) {
                Matrix3x3 matrix;

                matrix = (*this) * m;

                // Assign the temporary matrix to this instance and return *this;
                return operator=(matrix);
            }

            bool Matrix3x3::operator==(const Matrix3x3 &other) const {
                Matrix3x3 m = (*this) - other;

                return ( fabs(m.getXX()) < Matrix3x3::EPSILON ) &&
                       ( fabs(m.getXY()) < Matrix3x3::EPSILON ) &&
                       ( fabs(m.getXZ()) < Matrix3x3::EPSILON ) &&
                       ( fabs(m.getYX()) < Matrix3x3::EPSILON ) &&
                       ( fabs(m.getYY()) < Matrix3x3::EPSILON ) &&
                       ( fabs(m.getYZ()) < Matrix3x3::EPSILON ) &&
                       ( fabs(m.getZX()) < Matrix3x3::EPSILON ) &&
                       ( fabs(m.getZY()) < Matrix3x3::EPSILON ) &&
                       ( fabs(m.getZZ()) < Matrix3x3::EPSILON );
            }

            bool Matrix3x3::operator!=(const Matrix3x3 &other) const {
                return !((*this) == other);
            }

            Matrix3x3& Matrix3x3::transpose() {
                Matrix3x3 m(*this);

                m_xx = m.getXX();
                m_xy = m.getYX();
                m_xz = m.getZX();

                m_yx = m.getXY();
                m_yy = m.getYY();
                m_yz = m.getZY();

                m_zx = m.getXZ();
                m_zy = m.getYZ();
                m_zz = m.getZZ();

                return (*this);
            }

            const string Matrix3x3::toString() const {
                stringstream s;
                s << "(" << m_xx << "; " << m_xy << "; " << m_xz << "; " << m_yx << "; " << m_yy << "; " << m_yz << "; " << m_zx << "; " << m_zy << "; " << m_zz << ")";
                return s.str();
            }

            ostream& Matrix3x3::operator<<(ostream &out) const {
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                stringstream rawData;
                rawData.precision(10);

                rawData << m_xx << endl << m_xy << endl << m_xz << endl
                << m_yx << endl << m_yy << endl << m_yz << endl
                << m_zx << endl << m_zy << endl << m_zz;

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                        rawData.str());

                return out;
            }

            istream& Matrix3x3::operator>>(istream &in) {
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                string data;

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                       data);

                stringstream rawData;
                rawData.precision(10);
                rawData.str(data);

                rawData >> m_xx >> m_xy >> m_xz
                >> m_yx >> m_yy >> m_yz
                >> m_zx >> m_zy >> m_zz;

                return in;
            }

        }
    }
} // core::data::environment

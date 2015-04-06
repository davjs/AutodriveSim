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

#include <cmath>
#include <iomanip>
#include <sstream>

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "hesperia/data/environment/Quaternion.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace core::base;
            using namespace core::data::environment;

            const double Quaternion::EPSILON = 1e-10;

            Quaternion::Quaternion() :
                m_w(1),
                m_x(0),
                m_y(0),
                m_z(0) {}

            Quaternion::Quaternion(const double &w, const double &x, const double &y, const double &z) :
                m_w(w),
                m_x(x),
                m_y(y),
                m_z(z) {}

            Quaternion::Quaternion(const Quaternion &obj) :
                m_w(obj.getW()),
                m_x(obj.getX()),
                m_y(obj.getY()),
                m_z(obj.getZ()) {}

            Quaternion::~Quaternion() {}

            Quaternion& Quaternion::operator=(const Quaternion &obj) {
                setW(obj.getW());
                setX(obj.getX());
                setY(obj.getY());
                setZ(obj.getZ());

                return (*this);
            }

            double Quaternion::getW() const {
                return m_w;
            }

            void Quaternion::setW(const double &w) {
                m_w = w;
            }

            double Quaternion::getX() const {
                return m_x;
            }

            void Quaternion::setX(const double &x) {
                m_x = x;
            }

            double Quaternion::getY() const {
                return m_y;
            }

            void Quaternion::setY(const double &y) {
                m_y = y;
            }

            double Quaternion::getZ() const {
                return m_z;
            }

            void Quaternion::setZ(const double &z) {
                m_z = z;
            }

            Quaternion Quaternion::operator*(const Quaternion &q) const {
                Quaternion result;

                const double w = getW()*q.getW() - getX()*q.getX() - getY()*q.getY() - getZ()*q.getZ();
                const double x = getW()*q.getX() + getX()*q.getW() + getY()*q.getZ() - getZ()*q.getY();
                const double y = getW()*q.getY() + getY()*q.getW() + getZ()*q.getX() - getX()*q.getZ();
                const double z = getW()*q.getZ() + getZ()*q.getW() + getX()*q.getY() - getY()*q.getX();

                return Quaternion(w, x, y, z);
            }

            Quaternion& Quaternion::operator*=(const Quaternion &q) {
                Quaternion result;

                result = (*this) * q;

                // Assign the temporary Quaternion to this instance and return *this;
                return operator=(result);
            }

            Quaternion& Quaternion::conjugate() {
                setX( (-1) * getX());
                setY( (-1) * getY());
                setZ( (-1) * getZ());

                return (*this);
            }

            Quaternion& Quaternion::inverse() {
                double normal = sqrt(getW()*getW() + getX()*getX() + getY()*getY() + getZ()*getZ());
                if (normal < Quaternion::EPSILON) {
                    normal = 1.0;
                }

                const double reciprocal = 1.0/normal;

                setW(reciprocal * getW());
                setX(reciprocal * (-1) * getX());
                setY(reciprocal * (-1) * getY());
                setZ(reciprocal * (-1) * getZ());

                return (*this);
            }

            Quaternion& Quaternion::normalize() {
                const double normal = sqrt(getW()*getW() + getX()*getX() + getY()*getY() + getZ()*getZ());
                if (normal < Quaternion::EPSILON) {
                    setW(1.0);
                    setX(0);
                    setY(0);
                    setZ(0);
                }
                else {
                    const double reciprocal = 1.0/normal;

                    setW(reciprocal * getW());
                    setX(reciprocal * getX());
                    setY(reciprocal * getY());
                    setZ(reciprocal * getZ());
                }
                return (*this);
            }

            Quaternion& Quaternion::transform(const double &angle, const Point3 &dir) {
                double length = dir.length();
                if (length > Quaternion::EPSILON) {
                    Point3 p(dir);
                    p.normalize();

                    const double omega = -0.5 * angle; // TODO: Eigentlich positiv!!
                    const double sinOmega = sin(omega);

                    setW(cos(omega));
                    setX(sinOmega * p.getX());
                    setY(sinOmega * p.getY());
                    setZ(sinOmega * p.getZ());
                }
                else {
                    setW(1.0);
                    setX(0);
                    setY(0);
                    setZ(0);
                }
                normalize();

                return (*this);
            }

            Matrix3x3 Quaternion::transformToMatrix3x3() const {
                Matrix3x3 result;

                result.setXX(1.0 - 2*(getY()*getY() + getZ()*getZ()));
                result.setXY(2*(getX()*getY() + getZ()*getW()));
                result.setXZ(2*(getX()*getZ() - getY()*getW()));

                result.setYX(2*(getX()*getY() - getZ()*getW()));
                result.setYY(1.0 - 2*(getX()*getX() + getZ()*getZ()));
                result.setYZ(2*(getZ()*getY() + getX()*getW()));

                result.setZX(2*(getX()*getZ() + getY()*getW()));
                result.setZY(2*(getY()*getZ() - getX()*getW()));
                result.setZZ(1.0 - 2*(getX()*getX() + getY()*getY()));

                return result;
            }

            void Quaternion::transformToMatrix4x4(double *matrix4x4) const {
                if (matrix4x4 != NULL) {
                    Matrix3x3 result = transformToMatrix3x3();

                    matrix4x4[0] = result.getXX();
                    matrix4x4[1] = result.getXY();
                    matrix4x4[2] = result.getXZ();
                    matrix4x4[3] = 0;

                    // Second row
                    matrix4x4[4] = result.getYX();
                    matrix4x4[5] = result.getYY();
                    matrix4x4[6] = result.getYZ();
                    matrix4x4[7] = 0;

                    // Third row
                    matrix4x4[8] = result.getZX();
                    matrix4x4[9] = result.getZY();
                    matrix4x4[10] = result.getZZ();
                    matrix4x4[11] = 0.;

                    // Fourth row
                    matrix4x4[12] = 0;
                    matrix4x4[13] = 0;
                    matrix4x4[14] = 0;
                    matrix4x4[15] = 1;
                }
            }

            bool Quaternion::operator==(const Quaternion &other) const {
                return ( fabs(getW() - other.getW()) < Quaternion::EPSILON ) &&
                       ( fabs(getX() - other.getX()) < Quaternion::EPSILON ) &&
                       ( fabs(getY() - other.getY()) < Quaternion::EPSILON ) &&
                       ( fabs(getZ() - other.getZ()) < Quaternion::EPSILON );
            }

            bool Quaternion::operator!=(const Quaternion &other) const {
                return !((*this) == other);
            }

            const string Quaternion::toString() const {
                stringstream s;
                s << "(" << m_w << "; " << m_x << "i; " << m_y << "j; " << m_z << "k)";
                return s.str();
            }

            ostream& Quaternion::operator<<(ostream &out) const {
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                stringstream rawData;
                rawData.precision(10);

                rawData << m_w << endl << m_x << endl << m_y << endl << m_z;

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                        rawData.str());

                return out;
            }

            istream& Quaternion::operator>>(istream &in) {
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                string data;

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                       data);

                stringstream rawData;
                rawData.precision(10);
                rawData.str(data);

                rawData >> m_w >> m_x >> m_y >> m_z;

                return in;
            }
        }
    }
} // hesperia::data::environment

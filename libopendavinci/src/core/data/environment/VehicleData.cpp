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

#include "core/data/environment/VehicleData.h"

namespace core {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace core::base;

            VehicleData::VehicleData() :
                SerializableData(),
                m_position(),
                m_heading(0),
                m_absTraveledPath(0),
                m_relTraveledPath(0),
                m_velocity(),
                m_speed(0),
                m_v_log(0),
                m_v_batt(0),
                m_temp(0) {}

            VehicleData::VehicleData(const VehicleData &obj) :
                SerializableData(obj),
                m_position(obj.m_position),
                m_heading(obj.m_heading),
                m_absTraveledPath(obj.m_absTraveledPath),
                m_relTraveledPath(obj.m_relTraveledPath),
                m_velocity(obj.m_velocity),
                m_speed(obj.m_speed),
                m_v_log(obj.m_v_log),
                m_v_batt(obj.m_v_batt),
                m_temp(obj.m_temp) {}

            VehicleData::~VehicleData() {}

            VehicleData& VehicleData::operator=(const VehicleData &obj) {
                m_position = obj.m_position;
                m_heading = obj.m_heading;
                m_absTraveledPath = obj.m_absTraveledPath;
                m_relTraveledPath = obj.m_relTraveledPath;
                m_velocity = obj.m_velocity;
                m_speed = obj.m_speed;
                m_v_log = obj.m_v_log;
                m_v_batt = obj.m_v_batt;
                m_temp = obj.m_temp;

                return (*this);
            }

            const Point3 VehicleData::getPosition() const {
                return m_position;
            }

            void VehicleData::setPosition(const Point3 &p) {
                m_position = p;
            }

            double VehicleData::getHeading() const {
                return m_heading;
            }

            void VehicleData::setHeading(const double &h) {
                m_heading = h;
            }

            double VehicleData::getAbsTraveledPath() const {
                return m_absTraveledPath;
            }

            void VehicleData::setAbsTraveledPath(const double &adp) {
                m_absTraveledPath = adp;
            }

            double VehicleData::getRelTraveledPath() const {
                return m_relTraveledPath;
            }

            void VehicleData::setRelTraveledPath(const double &rdp) {
                m_relTraveledPath = rdp;
            }

            const Point3 VehicleData::getVelocity() const {
                return m_velocity;
            }

            void VehicleData::setVelocity(const Point3 &velocity) {
                m_velocity = velocity;
            }

            double VehicleData::getSpeed() const {
                return m_speed;
            }

            void VehicleData::setSpeed(const double &speed) {
                m_speed = speed;
            }

            double VehicleData::getV_log() const {
                return m_v_log;
            }

            void VehicleData::setV_log(const double &v_log) {
                m_v_log = v_log;
            }

            double VehicleData::getV_batt() const {
                return m_v_batt;
            }

            void VehicleData::setV_batt(const double &v_batt) {
                m_v_batt = v_batt;
            }

            double VehicleData::getTemp() const {
                return m_temp;
            }

            void VehicleData::setTemp(const double &temp) {
                m_temp = temp;
            }

            const string VehicleData::toString() const {
                stringstream s;
                s << "Position:" << m_position.toString() << ", heading: " << m_heading << ", abs: " << m_absTraveledPath << ", rel: " << m_relTraveledPath << ", velocity: " << m_velocity.toString() << ", speed: " << m_speed << ", V_log: " << m_v_log << ", V_batt: " << m_v_batt << ", temp: " << m_temp;
                return s.str();
            }

            ostream& VehicleData::operator<<(ostream &out) const {
                // Serialize this class.
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('p', 'o', 's', 'i', 't', 'i', 'o', 'n') >::RESULT,
                        m_position);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('h', 'e', 'a', 'd', 'i', 'n', 'g') >::RESULT,
                        m_heading);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('a', 'd', 'p') >::RESULT,
                        m_absTraveledPath);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('r', 'd', 'p') >::RESULT,
                        m_relTraveledPath);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('v', 'e', 'l', 'o', 'c', 'i', 't', 'y') >::RESULT,
                        m_velocity);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 'p', 'e', 'e', 'd') >::RESULT,
                        m_speed);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('v', 'l', 'o', 'g') >::RESULT,
                        m_v_log);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('v', 'b', 'a', 't') >::RESULT,
                        m_v_batt);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'e', 'm', 'p') >::RESULT,
                        m_temp);

                return out;
            }

            istream& VehicleData::operator>>(istream &in) {
                // Deserialize this class.
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('p', 'o', 's', 'i', 't', 'i', 'o', 'n') >::RESULT,
                       m_position);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('h', 'e', 'a', 'd', 'i', 'n', 'g') >::RESULT,
                       m_heading);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('a', 'd', 'p') >::RESULT,
                       m_absTraveledPath);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('r', 'd', 'p') >::RESULT,
                       m_relTraveledPath);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('v', 'e', 'l', 'o', 'c', 'i', 't', 'y') >::RESULT,
                       m_velocity);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 'p', 'e', 'e', 'd') >::RESULT,
                       m_speed);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('v', 'l', 'o', 'g') >::RESULT,
                       m_v_log);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('v', 'b', 'a', 't') >::RESULT,
                       m_v_batt);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'e', 'm', 'p') >::RESULT,
                       m_temp);

                return in;
            }

        }
    }
} // core::data::environment

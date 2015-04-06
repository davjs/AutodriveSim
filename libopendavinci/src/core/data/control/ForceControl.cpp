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

#include <sstream>

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/data/control/ForceControl.h"

namespace core {
    namespace data {
        namespace control {

            using namespace std;

            using namespace core::base;

            ForceControl::ForceControl() :
                    SerializableData(),
                    m_accelerationForce(),
                    m_brakeForce(),
                    m_steeringForce(),
                    m_brakeLights(false),
                    m_flashingLightsLeft(false),
                    m_flashingLightsRight(false)
            {}

            ForceControl::ForceControl(const ForceControl &obj) :
                    SerializableData(obj),
                    m_accelerationForce(obj.getAccelerationForce()),
                    m_brakeForce(obj.getBrakeForce()),
                    m_steeringForce(obj.getSteeringForce()),
                    m_brakeLights(obj.getBrakeLights()),
                    m_flashingLightsLeft(obj.getLeftFlashingLights()),
                    m_flashingLightsRight(obj.getRightFlashingLights())
            {}

            ForceControl::~ForceControl() {}

            ForceControl& ForceControl::operator=(const ForceControl &obj) {
                setAccelerationForce(obj.getAccelerationForce());
                setBrakeForce(obj.getBrakeForce());
                setSteeringForce(obj.getSteeringForce());
                setBrakeLights(obj.getBrakeLights());
                setLeftFlashingLights(obj.getLeftFlashingLights());
                setRightFlashingLights(obj.getRightFlashingLights());

                return (*this);
            }

            double ForceControl::getAccelerationForce() const {
                return m_accelerationForce;
            }

            void ForceControl::setAccelerationForce(const double &f) {
                m_accelerationForce = f;
            }

            double ForceControl::getBrakeForce() const {
                return m_brakeForce;
            }

            void ForceControl::setBrakeForce(const double &f)  {
                m_brakeForce = f;
            }

            double ForceControl::getSteeringForce() const {
                return m_steeringForce;
            }

            void ForceControl::setSteeringForce(const double &f) {
                m_steeringForce = f;
            }

            bool ForceControl::getBrakeLights() const {
                return m_brakeLights;            
            } 

            void ForceControl::setBrakeLights(const bool &on) {
                m_brakeLights = on;
            }

            bool ForceControl::getLeftFlashingLights() const {
                return m_flashingLightsLeft;
            }

            void ForceControl::setLeftFlashingLights(const bool &on) {
                m_flashingLightsLeft = on;
            }

            bool ForceControl::getRightFlashingLights() const {
                return m_flashingLightsRight;
            }

            void ForceControl::setRightFlashingLights(const bool &on) {
                m_flashingLightsRight = on;
            }

            const string ForceControl::toString() const {
                stringstream sstr;
                sstr << "Acceleration force: " << getAccelerationForce() << ", Brake force: " << getBrakeForce() << ", Steering force: " << getSteeringForce() << ", brake lights: " << getBrakeLights() << ", flashingLightsLeft: " << getLeftFlashingLights() << ", flashingLightsRight: " << getRightFlashingLights();
                return sstr.str();
            }

            ostream& ForceControl::operator<<(ostream &out) const {
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('a', 'c', 'c', 'e', 'l') >::RESULT,
                        m_accelerationForce);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('b', 'r', 'a', 'k', 'e') >::RESULT,
                        m_brakeForce);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 't', 'e', 'e', 'r') >::RESULT,
                        m_steeringForce);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('b', 'r', 'l', 'i', 't') >::RESULT,
                        m_brakeLights);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('l', 'e', 'f', 't') >::RESULT,
                        m_flashingLightsLeft);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'i', 'g', 'h', 't') >::RESULT,
                        m_flashingLightsRight);

                return out;
            }

            istream& ForceControl::operator>>(istream &in) {
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('a', 'c', 'c', 'e', 'l') >::RESULT,
                       m_accelerationForce);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('b', 'r', 'a', 'k', 'e') >::RESULT,
                       m_brakeForce);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 't', 'e', 'e', 'r') >::RESULT,
                       m_steeringForce);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('b', 'r', 'l', 'i', 't') >::RESULT,
                        m_brakeLights);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('l', 'e', 'f', 't') >::RESULT,
                        m_flashingLightsLeft);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'i', 'g', 'h', 't') >::RESULT,
                        m_flashingLightsRight);

                return in;
            }

        }
    }
} // core::data::control

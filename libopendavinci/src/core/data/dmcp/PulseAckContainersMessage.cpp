/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#include "core/data/dmcp/PulseAckContainersMessage.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace core::base;
            using namespace core::data;

            PulseAckContainersMessage::PulseAckContainersMessage() :
                m_listOfContainers() {}

            PulseAckContainersMessage::PulseAckContainersMessage(const PulseAckContainersMessage &obj) :
                SerializableData(obj),
                m_listOfContainers(obj.m_listOfContainers) {}

            PulseAckContainersMessage& PulseAckContainersMessage::operator=(const PulseAckContainersMessage &obj) {
                m_listOfContainers = obj.m_listOfContainers;
                return *this;
            }

            PulseAckContainersMessage::~PulseAckContainersMessage() {}

            void PulseAckContainersMessage::addContainer(const Container &c) {
                m_listOfContainers.push_back(c);
            }

            void PulseAckContainersMessage::setListOfContainers(const vector<core::data::Container> &l) {
                m_listOfContainers.clear();
                m_listOfContainers = l;
            }

            vector<Container> PulseAckContainersMessage::getListOfContainers() const {
                return m_listOfContainers;
            }

            const string PulseAckContainersMessage::toString() const {
                return "PulseAckContainersMessage";
            }

            ostream& PulseAckContainersMessage::operator<<(ostream &out) const {
                SerializationFactory sf;
                Serializer &s = sf.getSerializer(out);

                const uint32_t numberOfContainersToBeTransferred = m_listOfContainers.size();
                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('n', 'u', 'm', 'c', 'o', 'n', 't') >::RESULT, numberOfContainersToBeTransferred);

                stringstream sstr;
                for (uint32_t i = 0; i < numberOfContainersToBeTransferred; i++) {
                    sstr << m_listOfContainers.at(i);
                }
                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('c', 'o', 'n', 't', 's') >::RESULT, sstr.str());

                return out;
            }

            istream& PulseAckContainersMessage::operator>>(istream &in) {
                SerializationFactory sf;
                Deserializer &d = sf.getDeserializer(in);

                uint32_t numberOfContainersToBeTransferred = 0;
                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('n', 'u', 'm', 'c', 'o', 'n', 't') >::RESULT, numberOfContainersToBeTransferred);

                if (numberOfContainersToBeTransferred > 0) {
                    string s;
                    d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('c', 'o', 'n', 't', 's') >::RESULT, s);

                    stringstream sstr(s);
                    for (uint32_t i = 0; i < numberOfContainersToBeTransferred; i++) {
                        Container c;
                        sstr >> c;
                        addContainer(c);
                    }
                }

                return in;
            }

        }
    }
}

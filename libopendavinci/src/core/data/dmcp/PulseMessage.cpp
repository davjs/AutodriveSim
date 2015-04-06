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

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "core/data/dmcp/PulseMessage.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace core::base;
            using namespace core::data;

            PulseMessage::PulseMessage() :
                m_realTimeFromSupercomponent(),
                m_nominalTimeSlice(0),
                m_cumulatedTimeSlice(0),
                m_listOfContainers() {}

            PulseMessage::PulseMessage(const core::data::TimeStamp &ts, const uint32_t &nominalTimeSlice, const uint32_t &cumulatedTimeSlice) :
                m_realTimeFromSupercomponent(ts),
                m_nominalTimeSlice(nominalTimeSlice),
                m_cumulatedTimeSlice(cumulatedTimeSlice),
                m_listOfContainers() {}

            PulseMessage::PulseMessage(const PulseMessage &obj) :
                SerializableData(obj),
                m_realTimeFromSupercomponent(obj.m_realTimeFromSupercomponent),
                m_nominalTimeSlice(obj.m_nominalTimeSlice),
                m_cumulatedTimeSlice(obj.m_cumulatedTimeSlice),
                m_listOfContainers(obj.m_listOfContainers) {}

            PulseMessage& PulseMessage::operator=(const PulseMessage &obj) {
                m_realTimeFromSupercomponent = obj.m_realTimeFromSupercomponent;
                m_nominalTimeSlice = obj.m_nominalTimeSlice;
                m_cumulatedTimeSlice = obj.m_cumulatedTimeSlice;
                m_listOfContainers = obj.m_listOfContainers;

                return *this;
            }

            PulseMessage::~PulseMessage() {}

            void PulseMessage::setNominalTimeSlice(const uint32_t &nts) {
                m_nominalTimeSlice = nts;
            }

            uint32_t PulseMessage::getNominalTimeSlice() const {
                return m_nominalTimeSlice;
            }

            void PulseMessage::setCumulatedTimeSlice(const uint32_t &cts) {
                m_cumulatedTimeSlice = cts;
            }

            uint32_t PulseMessage::getCumulatedTimeSlice() const {
                return m_cumulatedTimeSlice;
            }

            void PulseMessage::setRealTimeFromSupercomponent(const TimeStamp &ts) {
                m_realTimeFromSupercomponent = ts;
            }

            const TimeStamp PulseMessage::getRealtimeFromSupercomponent() const {
                return m_realTimeFromSupercomponent;
            }

            void PulseMessage::addContainer(const Container &c) {
                m_listOfContainers.push_back(c);
            }

            void PulseMessage::setListOfContainers(const vector<core::data::Container> &l) {
                m_listOfContainers.clear();
                m_listOfContainers = l;
            }

            vector<Container> PulseMessage::getListOfContainers() const {
                return m_listOfContainers;
            }

            const string PulseMessage::toString() const {
                stringstream sstr;
                sstr << "Real time from supercomponent: " << m_realTimeFromSupercomponent.toString() << ", " << "nominal time slice: " << m_nominalTimeSlice << ", " << "cumulated time slice: " << m_cumulatedTimeSlice;
                return sstr.str();
            }

            ostream& PulseMessage::operator<<(ostream &out) const {
                SerializationFactory sf;
                Serializer &s = sf.getSerializer(out);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 't', 's', 'c') >::RESULT, m_realTimeFromSupercomponent);
                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('n', 'o', 'm', 'i', 'n', 'a', 'l') >::RESULT, m_nominalTimeSlice);
                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('c', 'u', 'm', 'u', 'l', 'a', 't', 'd') >::RESULT, m_cumulatedTimeSlice);

                const uint32_t numberOfContainersToBeTransferred = m_listOfContainers.size();
                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('n', 'u', 'm', 'c', 'o', 'n', 't') >::RESULT, numberOfContainersToBeTransferred);

                stringstream sstr;
                for (uint32_t i = 0; i < numberOfContainersToBeTransferred; i++) {
                    sstr << m_listOfContainers.at(i);
                }
                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('c', 'o', 'n', 't', 's') >::RESULT, sstr.str());

                return out;
            }

            istream& PulseMessage::operator>>(istream &in) {
                SerializationFactory sf;
                Deserializer &d = sf.getDeserializer(in);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 't', 's', 'c') >::RESULT, m_realTimeFromSupercomponent);
                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('n', 'o', 'm', 'i', 'n', 'a', 'l') >::RESULT, m_nominalTimeSlice);
                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('c', 'u', 'm', 'u', 'l', 'a', 't', 'd') >::RESULT, m_cumulatedTimeSlice);

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

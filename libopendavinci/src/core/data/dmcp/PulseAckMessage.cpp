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

#include "core/data/dmcp/PulseAckMessage.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace core::base;
            using namespace core::data;

            PulseAckMessage::PulseAckMessage() {}

            PulseAckMessage::PulseAckMessage(const PulseAckMessage &obj) :
                SerializableData(obj) {}

            PulseAckMessage& PulseAckMessage::operator=(const PulseAckMessage &/*obj*/) {
                return *this;
            }

            PulseAckMessage::~PulseAckMessage() {}

            const string PulseAckMessage::toString() const {
                return "PulseAckMessage";
            }

            ostream& PulseAckMessage::operator<<(ostream &out) const {
//                SerializationFactory sf;
//                Serializer &s = sf.getSerializer(out);

//                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 't', 's', 'c') >::RESULT, m_realTimeFromSupercomponent);

                return out;
            }

            istream& PulseAckMessage::operator>>(istream &in) {
//                SerializationFactory sf;
//                Deserializer &d = sf.getDeserializer(in);

//                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 't', 's', 'c') >::RESULT, m_realTimeFromSupercomponent);

                return in;
            }

        }
    }
}

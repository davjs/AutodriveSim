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

#include "core/data/dmcp/DiscoverMessage.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace core::base;

            DiscoverMessage::DiscoverMessage() :
                m_type(UNDEFINED),
                m_serverInformation(),
                m_moduleName("")
            {}

            DiscoverMessage::DiscoverMessage(TYPE type, const string &name) :
                m_type(type),
                m_serverInformation(),
                m_moduleName(name)
            {}

            DiscoverMessage::DiscoverMessage(TYPE type, const core::dmcp::ServerInformation& serverInformation) :
                m_type(type),
                m_serverInformation(serverInformation),
                m_moduleName("")
            {}

            DiscoverMessage::~DiscoverMessage() {}

            ostream&  DiscoverMessage::operator<<(ostream &out) const {
                SerializationFactory sf;
                Serializer &s = sf.getSerializer(out);

                uint32_t type = m_type;
                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT, type);
                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('i', 'f', 'n', 'o') >::RESULT, m_serverInformation);
                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT, m_moduleName);

                return out;
            }

            istream& DiscoverMessage::operator>>(istream &in) {
                SerializationFactory sf;
                Deserializer &d = sf.getDeserializer(in);

                uint32_t type = 0;
                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT, type);
                m_type = static_cast<DiscoverMessage::TYPE>(type);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('i', 'f', 'n', 'o') >::RESULT, m_serverInformation);
                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT, m_moduleName);

                return in;
            }

            const string DiscoverMessage::getModuleName() const {
                return m_moduleName;
            }

            const string DiscoverMessage::toString() const {
                switch (m_type) {
                case UNDEFINED:
                    return "DiscoverMessage::UNDEFINED";
                case DISCOVER:
                    return "DiscoverMessage::DISCOVER";
                case RESPONSE:
                    return "DiscoverMessage::RESPONSE";
                }
                return "";
            }

            DiscoverMessage::TYPE DiscoverMessage::getType() const {
                return m_type;
            }

            const core::dmcp::ServerInformation DiscoverMessage::getServerInformation() const
            {
                return m_serverInformation;
            }
        }
    }
}

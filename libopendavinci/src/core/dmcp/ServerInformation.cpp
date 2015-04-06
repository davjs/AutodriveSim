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

#include "core/dmcp/ServerInformation.h"

#include <sstream>
#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/Serializer.h"
#include "core/base/SerializationFactory.h"

namespace core {
    namespace dmcp {
        using namespace core::base;

        ServerInformation::ServerInformation() :
            m_serverIP(""),
            m_serverPort(0),
            m_managedLevel(ServerInformation::ML_NONE)
        {}

        ServerInformation::ServerInformation(const ServerInformation &obj) :
            Serializable(obj),
            m_serverIP(obj.m_serverIP),
            m_serverPort(obj.m_serverPort),
            m_managedLevel(obj.m_managedLevel)
        {}

        ServerInformation& ServerInformation::operator=(const ServerInformation &obj) {
            m_serverIP = obj.m_serverIP;
            m_serverPort = obj.m_serverPort;
            m_managedLevel = obj.m_managedLevel;

            return *this;
        }

        ServerInformation::ServerInformation(const string& ip, const uint32_t& port, const MANAGED_LEVEL &managedLevel):
            m_serverIP(ip),
            m_serverPort(port),
            m_managedLevel(managedLevel)
        {}

        ServerInformation::~ServerInformation()
        {}

        const string ServerInformation::getIP() const
        {
            return m_serverIP;
        }

        uint32_t ServerInformation::getPort() const
        {
            return m_serverPort;
        }

        ServerInformation::MANAGED_LEVEL ServerInformation::getManagedLevel() const {
            return m_managedLevel;
        }

        ostream& ServerInformation::operator<<(ostream &out) const
        {
            SerializationFactory sf;
            Serializer &s = sf.getSerializer(out);

            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'p') >::RESULT, m_serverIP);
            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('p', 'o', 'r', 't') >::RESULT, m_serverPort);
            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', 'a', 'n', 'l', 'e', 'v') >::RESULT, (uint32_t)m_managedLevel);

            return out;
        }

        istream& ServerInformation::operator>>(istream &in)
        {
            SerializationFactory sf;
            Deserializer &d = sf.getDeserializer(in);

            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'p') >::RESULT, m_serverIP);
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('p', 'o', 'r', 't') >::RESULT, m_serverPort);

            uint32_t v = 0;
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', 'a', 'n', 'l', 'e', 'v') >::RESULT, v);
            m_managedLevel = static_cast<ServerInformation::MANAGED_LEVEL>(v);

            return in;
        }

        const string ServerInformation::toString() const
        {
            stringstream ss;
            ss << "IP: " << m_serverIP << ", Port: " << m_serverPort << ", managedLevel: " << m_managedLevel;
            return ss.str();
        }

        bool ServerInformation::operator==(const ServerInformation& other) const {
            return (m_serverIP ==other.m_serverIP ) && (m_serverPort==other.m_serverPort) && (m_managedLevel == other.m_managedLevel);
        }
    }
}




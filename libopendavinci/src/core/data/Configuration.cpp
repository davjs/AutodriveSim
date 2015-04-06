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
#include "core/data/Configuration.h"

namespace core {
    namespace data {

        using namespace std;
        using namespace core::base;

        Configuration::Configuration() : m_keyValueConfiguration() {}

        Configuration::Configuration(const KeyValueConfiguration &keyValueConfiguration) :
                m_keyValueConfiguration(keyValueConfiguration) {}

        Configuration::Configuration(const Configuration &obj) :
                SerializableData(),
                m_keyValueConfiguration(obj.m_keyValueConfiguration) {}

        Configuration::~Configuration() {}

        Configuration& Configuration::operator=(const Configuration &obj) {
            m_keyValueConfiguration = obj.m_keyValueConfiguration;
            return (*this);
        }

        const KeyValueConfiguration Configuration::getKeyValueConfiguration() const {
            return m_keyValueConfiguration;
        }

        const string Configuration::toString() const {
            stringstream s;
            s << m_keyValueConfiguration;
            return s.str();
        }

        ostream& Configuration::operator<<(ostream &out) const {
            SerializationFactory sf;

            Serializer &s = sf.getSerializer(out);

            const string configuration = toString();
            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('c', 'o', 'n', 'f', 'i', 'g') >::RESULT,
                    configuration);

            return out;
        }

        istream& Configuration::operator>>(istream &in) {
            SerializationFactory sf;

            Deserializer &d = sf.getDeserializer(in);

            string configuration;
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('c', 'o', 'n', 'f', 'i', 'g') >::RESULT,
                   configuration);

            stringstream stringstreamConfiguration(configuration);
            stringstreamConfiguration >> m_keyValueConfiguration;

            return in;
        }

    }
} // core::data

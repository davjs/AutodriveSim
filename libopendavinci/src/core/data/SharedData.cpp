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
#include "core/data/SharedData.h"

namespace core {
    namespace data {

        using namespace std;
        using namespace base;

        SharedData::SharedData() : m_name(), m_size(0) {}

        SharedData::SharedData(const SharedData &obj) :
                SerializableData(),
                m_name(obj.m_name),
                m_size(obj.m_size) {}

        SharedData::SharedData(const string &name, const uint32_t &size) :
                SerializableData(),
                m_name(name),
                m_size(size) {}

        SharedData::~SharedData() {}

        SharedData& SharedData::operator=(const SharedData &obj) {
            m_name = obj.m_name;
            m_size = obj.m_size;

            return (*this);
        }

        const string SharedData::getName() const {
            return m_name;
        }

        void SharedData::setName(const string &name) {
            m_name = name;
        }

        uint32_t SharedData::getSize() const {
            return m_size;
        }

        void SharedData::setSize(const uint32_t &s) {
            m_size = s;
        }

        const string SharedData::toString() const {
            stringstream s;
            s << m_name << " " << m_size;
            return s.str();
        }

        ostream& SharedData::operator<<(ostream &out) const {
            SerializationFactory sf;

            Serializer &s = sf.getSerializer(out);

            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                    m_name);

            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('l', 'e', 'n', 'g', 't', 'h') >::RESULT,
                    m_size);

            return out;
        }

        istream& SharedData::operator>>(istream &in) {
            SerializationFactory sf;

            Deserializer &d = sf.getDeserializer(in);

            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                   m_name);

            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('l', 'e', 'n', 'g', 't', 'h') >::RESULT,
                   m_size);

            return in;
        }

    }
} // core::data

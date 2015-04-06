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

#include "tools/MemorySegment.h"

namespace tools {

    using namespace core;
    using namespace core::base;
    using namespace core::data;

    MemorySegment::MemorySegment() :
        SerializableData(),
        m_header(),
        m_size(0),
        m_consumedSize(0),
        m_id(0)
    {}

    MemorySegment::MemorySegment(const MemorySegment &obj) : 
        SerializableData(obj),
        m_header(obj.m_header),
        m_size(obj.m_size),
        m_consumedSize(obj.m_consumedSize),
        m_id(obj.m_id)
    {}

    MemorySegment& MemorySegment::operator=(const MemorySegment &obj) {
        m_header = obj.m_header;
        m_size = obj.m_size;
        m_consumedSize = obj.m_consumedSize;
        m_id = obj.m_id;

        return *this;
    }

    ostream& MemorySegment::operator<<(ostream &out) const {
        // Serialize this class.
        SerializationFactory sf;

        Serializer &s = sf.getSerializer(out);

        s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('h', 'e', 'a', 'd', 'e', 'r') >::RESULT,
                m_header);

        s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('s', 'i', 'z', 'e') >::RESULT,
                m_size);

        s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('c', 'o', 'n', 's', 'i', 'z', 'e') >::RESULT,
                m_consumedSize);

        s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                m_id);

        return out;
    }

    istream& MemorySegment::operator>>(istream &in) {
        // Deserialize this class.
        SerializationFactory sf;

        Deserializer &d = sf.getDeserializer(in);

        d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('h', 'e', 'a', 'd', 'e', 'r') >::RESULT,
               m_header);

        d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('s', 'i', 'z', 'e') >::RESULT,
               m_size);

        d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('c', 'o', 'n', 's', 'i', 'z', 'e') >::RESULT,
               m_consumedSize);

        d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
               m_id);

        return in;
    }

    const string MemorySegment::toString() const {
        return "";
    }

} // tools


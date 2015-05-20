/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "Example3Data.h"

namespace examples {

	using namespace std;
	using namespace core::base;

	Example3Data::Example3Data() : m_numericalValue(0),
								   m_stringValue("") {}

	Example3Data::Example3Data(const Example3Data &obj) :
			SerializableData(),
			m_numericalValue(obj.m_numericalValue),
			m_stringValue(obj.m_stringValue) {}

	Example3Data::~Example3Data() {}

	Example3Data& Example3Data::operator=(const Example3Data &obj) {
		m_numericalValue = obj.m_numericalValue;
		m_stringValue = obj.m_stringValue;

		return (*this);
	}

	uint32_t Example3Data::getNumericalValue() const {
		return m_numericalValue;
	}

	void Example3Data::setNumericalValue(const uint32_t &nv) {
		m_numericalValue = nv;
	}

	const string Example3Data::getStringValue() const {
		return m_stringValue;
	}

	void Example3Data::setStringValue(const string &sv) {
		m_stringValue = sv;
	}

	const string Example3Data::toString() const {
		stringstream s;
		s << m_numericalValue;
		s << " ";
		s << m_stringValue;
		return s.str();
	}

	ostream& Example3Data::operator<<(ostream &out) const {
		SerializationFactory sf;

		Serializer &s = sf.getSerializer(out);

		s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('n', 'u', 'm') >::RESULT,
				m_numericalValue);

		s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('s', 't', 'r') >::RESULT,
				m_stringValue);

		return out;
	}

	istream& Example3Data::operator>>(istream &in) {
		SerializationFactory sf;

		Deserializer &d = sf.getDeserializer(in);

		d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('n', 'u', 'm') >::RESULT,
			   m_numericalValue);

		d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('s', 't', 'r') >::RESULT,
			   m_stringValue);

		return in;
	}


} // examples

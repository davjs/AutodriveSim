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
#include "core/data/RuntimeStatistic.h"

namespace core {
    namespace data {

        using namespace std;
        using namespace base;

        RuntimeStatistic::RuntimeStatistic() :
                m_sliceConsumption(0) {}

        RuntimeStatistic::RuntimeStatistic(const RuntimeStatistic &obj) :
                SerializableData(),
                m_sliceConsumption(obj.getSliceConsumption()) {}

        RuntimeStatistic::~RuntimeStatistic() {}

        RuntimeStatistic& RuntimeStatistic::operator=(const RuntimeStatistic &obj) {
            setSliceConsumption(obj.getSliceConsumption());
            return (*this);
        }

        float RuntimeStatistic::getSliceConsumption() const {
            return m_sliceConsumption;
        }

        void RuntimeStatistic::setSliceConsumption(const float &sc) {
            m_sliceConsumption = sc;
        }

        const string RuntimeStatistic::toString() const {
            stringstream s;
            s << getSliceConsumption() << "%";
            return s.str();
        }

        ostream& RuntimeStatistic::operator<<(ostream &out) const {
            SerializationFactory sf;

            Serializer &s = sf.getSerializer(out);

            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('s', 'c') >::RESULT,
                    getSliceConsumption());

            return out;
        }

        istream& RuntimeStatistic::operator>>(istream &in) {
            SerializationFactory sf;

            Deserializer &d = sf.getDeserializer(in);

            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('s', 'c') >::RESULT,
                   m_sliceConsumption);

            return in;
        }

    }
} // core::data

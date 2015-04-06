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

#include "core/data/dmcp/ModuleStatistics.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace std;
            using namespace core::base;
            using namespace core::data;

            ModuleStatistics::ModuleStatistics() :
                SerializableData(),
                m_moduleStatistics() {}

            ModuleStatistics::ModuleStatistics(const ModuleStatistics &obj) :
		SerializableData(),
                m_moduleStatistics(obj.getRuntimeStatistic()) {}

            ModuleStatistics::~ModuleStatistics() {}

            ModuleStatistics& ModuleStatistics::operator=(const ModuleStatistics &obj) {
                m_moduleStatistics = obj.getRuntimeStatistic();

                return (*this);
            }

            map<ModuleDescriptor, core::data::RuntimeStatistic, ModuleDescriptorComparator> ModuleStatistics::getRuntimeStatistic() const {
                return m_moduleStatistics;
            }

            void ModuleStatistics::setRuntimeStatistic(const ModuleDescriptor &md, const core::data::RuntimeStatistic &rts) {
                m_moduleStatistics[md] = rts;
            }

            const string ModuleStatistics::toString() const {
                stringstream sstr;
                sstr << m_moduleStatistics.size() << " statistical data.";
                return sstr.str();
            }

            ostream& ModuleStatistics::operator<<(ostream &out) const {
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                map<ModuleDescriptor, core::data::RuntimeStatistic, ModuleDescriptorComparator> data = getRuntimeStatistic();
                const uint32_t size = data.size();

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('s', 'i', 'z', 'e') >::RESULT,
                        size);

                stringstream dataStream;
                map<ModuleDescriptor, core::data::RuntimeStatistic, ModuleDescriptorComparator>::iterator it = data.begin();
                while (it != data.end()) {
                    dataStream << it->first << it->second;
                    it++;
                }

                if (size > 0) {
                    s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                            dataStream.str());
                }

                return out;
            }

            istream& ModuleStatistics::operator>>(istream &in) {
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                uint32_t size = 0;

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('s', 'i', 'z', 'e') >::RESULT,
                       size);

                if (size > 0) {
                    string dataStr;

                    d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                           dataStr);

                    stringstream data(dataStr);
                    for (uint32_t i = 0; i < size; i++) {
                        ModuleDescriptor md;
                        RuntimeStatistic rts;

                        data >> md >> rts;

                        setRuntimeStatistic(md, rts);
                    }
                }

                return in;
            }

        }
    }
} // core::data::dmcp

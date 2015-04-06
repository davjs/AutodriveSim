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

#ifndef OPENDAVINCI_DATA_DMCP_MODULESTATISTICS_H_
#define OPENDAVINCI_DATA_DMCP_MODULESTATISTICS_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/SerializableData.h"
#include "core/data/RuntimeStatistic.h"
#include "core/data/dmcp/ModuleDescriptorComparator.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace std;

            class OPENDAVINCI_API ModuleStatistics : public core::data::SerializableData {
                public:
                    ModuleStatistics();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ModuleStatistics(const ModuleStatistics &obj);

                    virtual ~ModuleStatistics();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ModuleStatistics& operator=(const ModuleStatistics &obj);

                    /**
                     * This method returns module statistics.
                     *
                     * @return Module statistics.
                     */
                    map<ModuleDescriptor, core::data::RuntimeStatistic, ModuleDescriptorComparator> getRuntimeStatistic() const;

                    /**
                     * This method sets a module's statistic.
                     *
                     * @param md ModuleDescriptor.
                     * @param rts RuntimeStatistic.
                     */
                    void setRuntimeStatistic(const ModuleDescriptor &md, const core::data::RuntimeStatistic &rts);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    map<ModuleDescriptor, core::data::RuntimeStatistic, ModuleDescriptorComparator> m_moduleStatistics;
            };
        }
    }
} // core::data::dmcp

#endif /*OPENDAVINCI_DATA_DMCP_MODULESTATISTICS_H_*/

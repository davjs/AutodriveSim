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

#ifndef OPENDAVINCI_DATA_DMCP_MODULEDESCRIPTORCOMPARATOR_H_
#define OPENDAVINCI_DATA_DMCP_MODULEDESCRIPTORCOMPARATOR_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/dmcp/ModuleDescriptor.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace std;

            /**
             * This class compares ModuleDescriptors for sorting.
             */
            class OPENDAVINCI_API ModuleDescriptorComparator {
                public:
                    ModuleDescriptorComparator();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ModuleDescriptorComparator(const ModuleDescriptorComparator &/*obj*/) {};

                    virtual ~ModuleDescriptorComparator();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ModuleDescriptorComparator& operator=(const ModuleDescriptorComparator &/*obj*/) {
                        return (*this);
                    };

                    /**
                     * This method returns s1 < s2.
                     *
                     * @return s1 < s2.
                     */
                    bool operator()(const ModuleDescriptor &m1, const ModuleDescriptor &m2) const;
            };

        }
    }
} // core::data::dmcp

#endif /*OPENDAVINCI_DATA_DMCP_MODULEDESCRIPTORCOMPARATOR_H_*/

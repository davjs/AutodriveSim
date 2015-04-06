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

#include "core/data/dmcp/ModuleDescriptorComparator.h"

namespace core {
    namespace data {
        namespace dmcp {

            ModuleDescriptorComparator::ModuleDescriptorComparator() {}

            ModuleDescriptorComparator::~ModuleDescriptorComparator() {}

            bool ModuleDescriptorComparator::operator()(const ModuleDescriptor &m1, const ModuleDescriptor &m2) const {
                return m1.toString().compare(m2.toString()) < 0;
            }

        }
    }
} // core::data::dmcp

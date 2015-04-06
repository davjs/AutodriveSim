/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#ifndef OPENDAVINCI_TOOLS_MEMORYSEGMENT_H_
#define OPENDAVINCI_TOOLS_MEMORYSEGMENT_H_

#include "core/data/Container.h"

namespace tools {

    using namespace std;

    class MemorySegment : public core::data::SerializableData {
        public:
            core::data::Container m_header;
            uint32_t m_size;
            uint32_t m_consumedSize;
            uint32_t m_id;

        public:
            /**
             * Constructor.
             */
            MemorySegment();

            MemorySegment(const MemorySegment &/*obj*/);

            MemorySegment& operator=(const MemorySegment &/*obj*/);

            virtual const string toString() const;

            virtual ostream& operator<<(ostream &out) const;
            virtual istream& operator>>(istream &in);
    };

} // tools

#endif /*OPENDAVINCI_TOOLS_MEMORYSEGMENT_H_*/

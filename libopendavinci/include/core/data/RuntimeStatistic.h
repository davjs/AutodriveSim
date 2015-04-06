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

#ifndef OPENDAVINCI_CORE_DATA_RUNTIMESTATISTIC_H_
#define OPENDAVINCI_CORE_DATA_RUNTIMESTATISTIC_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/SerializableData.h"

namespace core {
    namespace data {

        using namespace std;

        /**
         * This class can be used for gathering information about runtime.
         */
        class OPENDAVINCI_API RuntimeStatistic : public SerializableData {
            public:
                RuntimeStatistic();

                virtual ~RuntimeStatistic();

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                RuntimeStatistic(const RuntimeStatistic &obj);

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                RuntimeStatistic& operator=(const RuntimeStatistic &obj);

                /**
                 * This method returns the slice consumption in per cent.
                 *
                 * @return Slice consumption.
                 */
                float getSliceConsumption() const;

                /**
                 * This method sets the slice consumption.
                 *
                 * @param sc Slice consumption.
                 */
                void setSliceConsumption(const float &sc);

                virtual ostream& operator<<(ostream &out) const;
                virtual istream& operator>>(istream &in);

                virtual const string toString() const;

            private:
                float m_sliceConsumption;
        };

    }
} // core::data

#endif /*OPENDAVINCI_CORE_DATA_RUNTIMESTATISTIC_H_*/

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

#ifndef OPENDAVINCI_CORE_DATA_CONSTANTS_H_
#define OPENDAVINCI_CORE_DATA_CONSTANTS_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

namespace core {
    namespace data {

        /**
         * This class summarizes all constants as defined in Constants.cpp.
         */
        class OPENDAVINCI_API Constants {
            public:
                static const double PI;
                static const double DEG2RAD;
                static const double RAD2DEG;
                static const double MS2KMH;
                static const double KMH2MS;
                static const double G;
        };

    }
} // core::data

#endif /*OPENDAVINCI_CORE_DATA_CONSTANTS_H_*/

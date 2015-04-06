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

#include "core/data/Constants.h"

namespace core {
    namespace data {

        const double Constants::PI = 3.141592654;
        const double Constants::DEG2RAD = (3.141592654 / 180.0);
        const double Constants::RAD2DEG = (1.0 / Constants::DEG2RAD);
        const double Constants::MS2KMH = 3.6;
        const double Constants::KMH2MS = (1.0 / Constants::MS2KMH);
        const double Constants::G = 9.81;

	}
} // core::data

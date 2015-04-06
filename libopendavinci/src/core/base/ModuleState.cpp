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

#include "core/base/ModuleState.h"

namespace core {
    namespace base {

        const std::string ModuleState::getAsString(const MODULE_STATE& ms) {
            std::string retVal;
            switch (ms) {
                case RUNNING:
                {
                    retVal = "RUNNING";
                    break;
                }
                case NOT_RUNNING:
                {
                    retVal = "NOT_RUNNING";
                    break;
                }
                case UNDEFINED_STATE:
                {
                    retVal = "UNDEFINED_STATE";
                    break;
                }
            }
            return retVal;
        }

        const std::string ModuleState::getAsString(const MODULE_EXITCODE& me) {
            std::string retVal;
            switch (me) {
                case OKAY:
                {
                    retVal = "OKAY";
                    break;
                }
                case EXCEPTION_CAUGHT:
                {
                    retVal = "EXCEPTION_CAUGHT";
                    break;
                }
                case SERIOUS_ERROR:
                {
                    retVal = "SERIOUS_ERROR";
                    break;
                }
                case CONNECTION_LOST:
                {
                    retVal = "CONNECTION_LOST";
                    break;
                }
                case UNDEFINED_EXITCODE:
                {
                    retVal = "UNDEFINED_EXITCODE";
                    break;
                }
                case NO_SUPERCOMPONENT:
                {
                    retVal = "NO_SUPERCOMPONENT";
                    break;
                }
            }
            return retVal;
        }
    }
} // core::base

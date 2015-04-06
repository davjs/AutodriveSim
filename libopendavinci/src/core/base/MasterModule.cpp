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

#include "core/base/MasterModule.h"

namespace core {
    namespace base {

        using namespace std;
        using namespace exceptions;

        MasterModule::MasterModule(const int32_t &argc, char **argv) throw (InvalidArgumentException) :
                AbstractCIDModule(argc, argv) {}

        MasterModule::~MasterModule() {}

        ModuleState::MODULE_EXITCODE MasterModule::runModule() {
            ModuleState::MODULE_EXITCODE retVal = ModuleState::OKAY;

            setModuleState(ModuleState::RUNNING);

            try {
                retVal = body();
            } catch (std::exception &e) {
                // Try to catch any exception derived from std::exception and print32_t out reason.
                clog << e.what() << endl;
                retVal = ModuleState::EXCEPTION_CAUGHT;
            } catch (...) {
                // Try to catch anything else print32_t generic error.
                clog << "Unknown exception caught in MasterModule::run()" << endl;
                retVal = ModuleState::SERIOUS_ERROR;
            }

            return retVal;
        }

    }
} // core::base

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

#ifndef OPENDAVINCI_CORE_BASE_ABSTRACTMODULE_H_
#define OPENDAVINCI_CORE_BASE_ABSTRACTMODULE_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/base/Breakpoint.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/base/ModuleState.h"
#include "core/base/Mutex.h"

namespace core {
    namespace base {

        using namespace std;

        /**
         * This class is the abstract base for every module. For concrete
         * classes, use either ClientModule or MasterModule. ClientModules
         * use DMCP client requests for getting configuration data. MasterModules
         * however must provide DMCP services.
         */
        class OPENDAVINCI_API AbstractModule {
            protected:
                /**
                 * Constructor for any module.
                 */
                AbstractModule();

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                AbstractModule(const AbstractModule&);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                AbstractModule& operator=(const AbstractModule&);

            public:
                virtual ~AbstractModule();

                /**
                 * This method sets the module MODULE_STATE.
                 *
                 * @param s MODULE_STATE of the module.
                 */
                void setModuleState(const ModuleState::MODULE_STATE &s);

                /**
                 * This method returns the module MODULE_STATE.
                 *
                 * @return Module MODULE_STATE.
                 */
                ModuleState::MODULE_STATE getModuleState();

                /**
                 * This method returns the list of created modules for
                 * this class. This method can be used to broadcast
                 * signals to all instances.
                 */
                static vector<AbstractModule*>& getListOfModules();

            protected:
                /**
                 * This method is called to enforce a specific frequency.
                 */
                virtual void wait();

                /**
                 * This method can be used indicate to subclasses that
                 * getModuleState() was called. This is used by
                 * InterruptibleModule with private inheritance to
                 * not permit overriding getModuleState() in subclasses
                 * from InterruptibleModule.
                 */
                virtual void calledGetModuleState();

            private:
                static vector<AbstractModule*> m_listOfModules;

                Mutex m_moduleStateMutex;
                ModuleState::MODULE_STATE m_moduleState;
        };

    }
} // core::base

#endif /*OPENDAVINCI_CORE_BASE_ABSTRACTMODULE_H_*/

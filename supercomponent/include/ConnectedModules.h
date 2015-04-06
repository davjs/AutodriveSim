/**
 * supercomponent - Configuration and monitoring component for
 *                  distributed software systems
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SUPERCOMPONENT_CONNECTEDMODULES_H_
#define SUPERCOMPONENT_CONNECTEDMODULES_H_

#include <vector>

#include "core/base/ModuleState.h"
#include "core/base/Mutex.h"
#include "core/data/Container.h"
#include "core/data/dmcp/PulseMessage.h"
#include "core/data/dmcp/ModuleDescriptor.h"
#include "core/data/dmcp/ModuleDescriptorComparator.h"

#include "ConnectedModule.h"

namespace supercomponent {

    using namespace std;

    class ConnectedModules {
        public:
            ConnectedModules();
            virtual ~ConnectedModules();

            void addModule(const core::data::dmcp::ModuleDescriptor& md, ConnectedModule* module);
            ConnectedModule* getModule(const core::data::dmcp::ModuleDescriptor& md);
            void removeModule(const core::data::dmcp::ModuleDescriptor& md);
            bool hasModule(const core::data::dmcp::ModuleDescriptor& md);

            /**
             * This method sends a pulse to all connected modules.
             *
             * @param pm Pulse to be sent.
             */
            void pulse(const core::data::dmcp::PulseMessage &pm);

            /**
             * This method sends a pulse to all connected modules but shifts
             * the alignment interval by shift microseconds for each connected
             * module.
             *
             * @param pm Pulse to be sent.
             * @shift Increment for each newly connected module.
             */
            void pulseShift(const core::data::dmcp::PulseMessage &pm, const uint32_t &shift);

            /**
             * This method sends a pulse to all connected modules and
             * requires an ACK confirmation sent from the respective,
             * dependent module that the PULSE has been processed.
             *
             * @param pm Pulse to be sent.
             * @param timeout Timeout in milliseconds to wait for an ACK from the dependent module.
             * @param yield Time to wait in microseconds before sending the pulse to the next module in the list.
             * @param modulesToIgnore Modules that are skipped when sending the pulse signal.
             */
            void pulse_ack(const core::data::dmcp::PulseMessage &pm, const uint32_t &timeout, const uint32_t &yield, const vector<string> &modulesToIgnore);

            /**
             * This method sends a pulse to all connected modules and
             * requires an ACK confirmation sent from the respective,
             * dependent module that the PULSE has been processed.
             *
             * @param pm Pulse to be sent.
             * @param timeout Timeout in milliseconds to wait for an ACK from the dependent module.
             * @param yield Time to wait in microseconds before sending the pulse to the next module in the list.
             * @param modulesToIgnore Modules that are skipped when sending the pulse signal.
             * @return Containers to be transferred to supercomponent.
             */
            vector<core::data::Container> pulse_ack_containers(const core::data::dmcp::PulseMessage &pm, const uint32_t &timeout, const uint32_t &yield, const vector<string> &modulesToIgnore);

            void deleteAllModules();

        protected:
            core::base::Mutex m_modulesMutex;
            map< core::data::dmcp::ModuleDescriptor,
                 ConnectedModule*,
                 core::data::dmcp::ModuleDescriptorComparator> m_modules;

        private:
            ConnectedModules(const ConnectedModule &);
            ConnectedModules& operator=(const ConnectedModule &);
    };
}

#endif /*SUPERCOMPONENT_CONNECTEDMODULES_H_*/

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

#ifndef SUPERCOMPONENT_CONNECTEDMODULE_H_
#define SUPERCOMPONENT_CONNECTEDMODULE_H_

#include "core/base/ModuleState.h"
#include "core/dmcp/connection/ModuleConnection.h"

namespace supercomponent {

    using namespace std;

    class ConnectedModule {
        public:
            ConnectedModule(core::dmcp::connection::ModuleConnection* connection,
                            const core::base::ModuleState::MODULE_STATE& moduleState );

            virtual ~ConnectedModule();

            core::dmcp::connection::ModuleConnection& getConnection();

            core::base::ModuleState::MODULE_STATE getState() const;
            void setState(const core::base::ModuleState::MODULE_STATE& state);

            void setExitCode();
            bool hasExitCode() const;

        protected:
            core::base::ModuleState::MODULE_STATE m_state;
            core::dmcp::connection::ModuleConnection* m_connection;
            bool m_hasExitCode;

        private:
            ConnectedModule(const ConnectedModule &);
            ConnectedModule& operator=(const ConnectedModule &);
    };
}

#endif /*SUPERCOMPONENT_CONNECTEDMODULE_H_*/

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

#ifndef OPENDAVINCI_DMCP_CONFIG_H_
#define OPENDAVINCI_DMCP_CONFIG_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

namespace core {
    namespace dmcp {
        using namespace std;

         static const string DMCPConfig_TEST_GROUP = "225.0.0.250";
         static const uint32_t DMCPConfig_TEST_SERVERPORT = 25000;
         static const uint32_t DMCPConfig_TEST_CLIENTPORT = 25100;

        enum DMCP {
            CONNECTIONSERVER_PORT_BASE = 19755, // This is the base TCP port for connections.
            BROADCAST_PORT_SERVER = 19750,
            BROADCAST_PORT_CLIENT = 19751,
            CONNECTION_TIMEOUT = 1000,
            CONNECTION_RETRIES = 5,
            CONFIGURATION_TIMEOUT = 1000,
            DISCOVER_TIMEOUT = 1000,
            CONTROL_PORT_BASE = 10000,
        };
    }
} // core::dmcp
#endif /*OPENDAVINCI_DMCP_CONFIG_H_*/

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

#ifndef OPENDAVINCI_DMCP_CONNECTION_CLIENT_H_
#define OPENDAVINCI_DMCP_CONNECTION_CLIENT_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/base/Condition.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/base/ModuleState.h"
#include "core/data/Container.h"
#include "core/data/RuntimeStatistic.h"

#include "core/io/Connection.h"
#include "core/io/ConnectionErrorListener.h"

#include "core/data/Configuration.h"
#include "core/data/dmcp/PulseMessage.h"
#include "core/data/dmcp/ModuleDescriptor.h"
#include "core/dmcp/Config.h"
#include "core/dmcp/ServerInformation.h"
#include "core/dmcp/SuperComponentStateListener.h"

namespace core {
    namespace dmcp {
        namespace connection {

            using namespace std;

            class OPENDAVINCI_API Client : protected core::io::ContainerListener,
                                        protected core::io::ConnectionErrorListener
            {

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    Client(const Client &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    Client& operator=(const Client &);

                public:

                    Client(const core::data::dmcp::ModuleDescriptor& moduleDescriptor,
                           const ServerInformation& serverInformation);

                    virtual ~Client();

                    void initialize();

                    void sendModuleExitCode(const core::base::ModuleState::MODULE_EXITCODE& me);
                    void sendModuleState(const core::base::ModuleState::MODULE_STATE& me);
                    void sendStatistics(const core::data::RuntimeStatistic& rs);

                    core::base::KeyValueConfiguration getConfiguration();

                    const core::data::dmcp::PulseMessage getPulseMessage();

                    /**
                     * This method sends the PulseAckMessage to supercomponent.
                     */
                    void sendPulseAck();

                    /**
                     * This method sends the PulseAckMessage to supercomponent
                     * including all containers to be sent from this component.
                     *
                     * @param listOfContainers List of containers to be sent.
                     */
                    void sendPulseAckContainers(const vector<core::data::Container> &listOfContainers);

                    void setSupercomponentStateListener(SupercomponentStateListener* listener);

                    bool isConnected();

                protected:
                    void sendConfigurationRequest();
                    virtual void nextContainer(core::data::Container &c);
                    virtual void handleConnectionError();

                    void handleConfiguration(core::data::Configuration& configuration);
                    void waitForConfiguration();
                    bool isConfigured();

                private:
                    core::data::dmcp::ModuleDescriptor m_moduleDescriptor;
                    ServerInformation m_serverInformation;

                    core::io::Connection m_connection;

                    core::base::Mutex m_configurationMutex;
                    core::base::KeyValueConfiguration m_configuration;

                    bool m_configured;
                    core::base::Mutex m_configuredMutex;
                    core::base::Condition m_configurationRequestCondition;

                    core::base::Mutex m_listenerMutex;
                    SupercomponentStateListener* m_listener;

                    core::base::Condition m_pulseCondition;
                    core::base::Mutex m_pulseMessageMutex;
                    core::data::dmcp::PulseMessage m_pulseMessage;
            };
        }
    }
} // core::dmcp

#endif /*OPENDAVINCI_DMCP_CONNECTION_CLIENT_H_*/

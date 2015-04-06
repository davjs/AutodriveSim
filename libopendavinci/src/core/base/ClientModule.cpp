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

#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/data/RuntimeStatistic.h"
#include "core/data/TimeStamp.h"
#include "core/exceptions/Exceptions.h"

#include "core/base/ClientModule.h"
#include "core/data/dmcp/ModuleDescriptor.h"

#include "core/dmcp/Config.h"
#include "core/dmcp/discoverer/Client.h"
#include "core/dmcp/connection/Client.h"

namespace core {
    namespace base {

        using namespace std;

        using namespace core;
        using namespace core::base;
        using namespace core::data;
        using namespace core::exceptions;

        using namespace core::dmcp;
        using namespace core::data::dmcp;

        ClientModule::ClientModule(const int32_t &argc, char **argv, const string &name) throw (InvalidArgumentException) :
                AbstractCIDModule(argc, argv),
                m_name(name),
                m_keyValueConfiguration(),
                m_serverInformation(),
                m_dmcpClient() {}

        ClientModule::~ClientModule() {}

        core::SharedPointer<core::dmcp::connection::Client>& ClientModule::getDMCPClient() {
            return m_dmcpClient;
        }

        const string ClientModule::getName() const {
            return m_name;
        }

        const KeyValueConfiguration ClientModule::getKeyValueConfiguration() const {
            return m_keyValueConfiguration;
        }

        const core::dmcp::ServerInformation ClientModule::getServerInformation() const {
            return m_serverInformation;
        }

        ModuleState::MODULE_EXITCODE ClientModule::runModule() {
            // Try to discover supercomponent.
            try {
                SharedPointer<discoverer::Client> discovererClient =
                    SharedPointer<discoverer::Client>(
                            new discoverer::Client(getMultiCastGroup(),
                                                   BROADCAST_PORT_SERVER,
                                                   BROADCAST_PORT_CLIENT,
                                                   getName()));

                bool supercomponentFound = false;
                uint32_t attempt  = 0;

                while ( !supercomponentFound && ( attempt < CONNECTION_RETRIES)) {
                	clog << "(ClientModule) discovering supercomponent..." << endl;
                	supercomponentFound = discovererClient->existsServer();
                	attempt++;
                }

                if ( !supercomponentFound ) {
                    clog << "(ClientModule) no supercomponent running for " << getMultiCastGroup() << endl;
                    return ModuleState::NO_SUPERCOMPONENT;
                }

                m_serverInformation = discovererClient->getServerInformation();
                clog << "(ClientModule) supercomponent found at " << m_serverInformation.toString() << endl;
            }
            catch (...) {
                clog << "(ClientModule) error while discovering supercomponent." << endl;
                return ModuleState::SERIOUS_ERROR;
            }

            clog << "(ClientModule) connecting to supercomponent..." << endl;
            string myVersion = "No version set.";
            ModuleDescriptor md(getName(), getIdentifier(), myVersion, getFrequency());

            try {
                // Try to get configuration from DMCP server.
                m_dmcpClient = SharedPointer<connection::Client>(
                        new connection::Client(md, m_serverInformation));
                m_dmcpClient->setSupercomponentStateListener(this);
                m_dmcpClient->initialize();

                // Get configuration from DMCP client.
                m_keyValueConfiguration = m_dmcpClient->getConfiguration();
            } catch (ConnectException& e) {
                clog << "(ClientModule) connecting to supercomponent failed: " << e.getMessage() << endl;
                return ModuleState::SERIOUS_ERROR;
            }

            clog << "(ClientModule) connecting to supercomponent...done - managed level: " << m_serverInformation.getManagedLevel() << endl;

            // Run user implementation from derived ConferenceClientModule.
            ModuleState::MODULE_EXITCODE retVal = runModuleImplementation();

            if (m_dmcpClient.isValid()) {
                m_dmcpClient->sendModuleExitCode(retVal);
            }

            return retVal;
        }

        void ClientModule::handleConnectionLost() {
            clog << "(ClientModule) connection to supercomponent lost. Shutting down" << endl;
            setModuleState(ModuleState::NOT_RUNNING);
        }
    }
} // core::base

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

#include <iostream>
#include <sstream>

#include "core/macros.h"
#include "core/base/Lock.h"
#include "core/io/ContainerConferenceFactory.h"
#include "core/dmcp/ServerInformation.h"
#include "context/base/SuperComponent.h"

namespace context {
    namespace base {

        using namespace std;
        using namespace core::base;
        using namespace core::io;
        using namespace core::dmcp;

        SuperComponent::SuperComponent(const string &multicastGroup, const uint32_t &CID, const KeyValueConfiguration &configuration) :
            m_configurationMutex(),
            m_configuration(configuration),
            m_discovererServer(NULL),
            m_connectionServer(NULL),
            m_conference(NULL) {
            // Run locally.
            ServerInformation serverInformation("127.0.0.1", CONNECTIONSERVER_PORT_BASE + CID);

            clog << "(context::base::SuperComponent) Server information: " << serverInformation.toString() << endl;
            clog << "(context::base::SuperComponent) Creating discoverer server..." << endl;
            vector<string> noModulesToIgnore;
            m_discovererServer = new discoverer::Server(serverInformation, multicastGroup, BROADCAST_PORT_SERVER, BROADCAST_PORT_CLIENT, noModulesToIgnore);
            m_discovererServer->startResponding();

            clog << "(context::base::SuperComponent) Creating connection server..." << endl;
            m_connectionServer = new connection::Server(serverInformation, *this);
            m_connectionServer->setConnectionHandler(this);

            clog << "(context::base::SuperComponent) Creating ContainerConference..." << endl;
            m_conference = ContainerConferenceFactory::getInstance().getContainerConference(multicastGroup);
        }

        SuperComponent::~SuperComponent() {
            OPENDAVINCI_CORE_DELETE_POINTER(m_discovererServer);
            OPENDAVINCI_CORE_DELETE_POINTER(m_connectionServer);
        }

        ContainerConference& SuperComponent::getContainerConference() {
            return *m_conference;
        }

        KeyValueConfiguration SuperComponent::getConfiguration(const core::data::dmcp::ModuleDescriptor& md) {
            Lock l(m_configurationMutex);

             if (md.getName() == "Monitor") {
                 return m_configuration;
             }

             // Determine subset of configuration for this client.
             KeyValueConfiguration globalConfiguration = m_configuration.getSubsetForSection("global.");

             stringstream module;
             module << md.getName() << ".";
             KeyValueConfiguration privateConfigurationBasedOnModuleName = m_configuration.getSubsetForSection(module.str());

             KeyValueConfiguration privateConfigurationBasedOnModuleIdentifier;
             if (md.getIdentifier() != "") {
                 stringstream moduleIdentifier;
                 moduleIdentifier << md.getName() << ":" << md.getIdentifier() << ".";
                 KeyValueConfiguration privateConfigurationBasedOnModuleIdentiferIncludingModuleIdentifier;
                 privateConfigurationBasedOnModuleIdentiferIncludingModuleIdentifier = m_configuration.getSubsetForSection(moduleIdentifier.str());

                 // Remove string ":" + md.getIdentifier().
                 const vector<string> keys = privateConfigurationBasedOnModuleIdentiferIncludingModuleIdentifier.getListOfKeys();
                 vector<string>::const_iterator it = keys.begin();
                 stringstream moduleIdentifierPart;
                 moduleIdentifierPart << ":" << md.getIdentifier() << ".";
                 stringstream sstrPrivateConfigurationWithoutModuleIdentifier;
                 while (it != keys.end()) {
                     string key = (*it++);

                     stringstream modifiedKey;
                     modifiedKey << key.substr(0, key.find(moduleIdentifierPart.str())) << "." << key.substr(key.find(moduleIdentifierPart.str()) + moduleIdentifierPart.str().length());

                     sstrPrivateConfigurationWithoutModuleIdentifier << modifiedKey.str() << "=" << privateConfigurationBasedOnModuleIdentiferIncludingModuleIdentifier.getValue<string>(key) << endl;
                 }
                 if (sstrPrivateConfigurationWithoutModuleIdentifier.str().length() > 0) {
                     sstrPrivateConfigurationWithoutModuleIdentifier >> privateConfigurationBasedOnModuleIdentifier;
                 }
             }

             // Prepare configuration.
             stringstream configurationForClient;
             configurationForClient << globalConfiguration << endl;
             configurationForClient << privateConfigurationBasedOnModuleName << endl;
             configurationForClient << privateConfigurationBasedOnModuleIdentifier << endl;

             KeyValueConfiguration clientKeyValueConfiguration;
             configurationForClient >> clientKeyValueConfiguration;

             // Set up configuration object.
             return clientKeyValueConfiguration;
        }

        KeyValueConfiguration SuperComponent::getGlobalConfiguration() const {
            return m_configuration;
        }

        void SuperComponent::onNewModule(core::dmcp::connection::ModuleConnection *mc) {
            if (mc != NULL) {
                clog << "(context::base::SuperComponent) Got new connection from " << mc->getModuleDescriptor().toString() << endl;
            }
        }

        void SuperComponent::handleChangeState(const core::data::dmcp::ModuleDescriptor& md, const ModuleState::MODULE_STATE &ms) {
            switch (ms) {
                case ModuleState::NOT_RUNNING:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to NOT_RUNNING." << endl;
                break;

                case ModuleState::RUNNING:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to RUNNING." << endl;
                break;

                case ModuleState::UNDEFINED_STATE:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to UNDEFINED_STATE." << endl;
                break;
            }
        }

        void SuperComponent::handleExitCode(const core::data::dmcp::ModuleDescriptor& md, const ModuleState::MODULE_EXITCODE &me) {
            switch (me) {
                case ModuleState::OKAY:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode OKAY." << endl;
                break;

                case ModuleState::EXCEPTION_CAUGHT:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode EXCEPTION_CAUGHT." << endl;
                break;

                case ModuleState::SERIOUS_ERROR:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode SERIOUS_ERROR." << endl;
                break;

                case ModuleState::CONNECTION_LOST:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode CONNECTION_LOST." << endl;
                break;

                case ModuleState::NO_SUPERCOMPONENT:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode NO_SUPERCOMPONENT." << endl;
                break;

                case ModuleState::UNDEFINED_EXITCODE:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode UNDEFINED_EXITCODE." << endl;
                break;
            }
        }

        void SuperComponent::handleRuntimeStatistics(const core::data::dmcp::ModuleDescriptor& md,  const core::data::RuntimeStatistic& rs) {
            clog << "(context::base::SuperComponent) Received RuntimeStatistics for " << md.toString() << ": " << rs.toString() << endl;
        }

        void SuperComponent::handleConnectionLost(const core::data::dmcp::ModuleDescriptor& md) {
            clog << "(context::base::SuperComponent) Lost connection to " << md.toString() << endl;
        }

        void SuperComponent::handleUnkownContainer(const core::data::dmcp::ModuleDescriptor& md, const core::data::Container& container) {
            clog << "(context::base::SuperComponent) Received unknown container " << container.toString() << "from " << md.toString() << endl;
        }

    }
} // context::base

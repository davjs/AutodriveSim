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

#include <cstdlib>

#include <algorithm>
#include <fstream>

#include "core/StringToolbox.h"
#include "core/base/CommandLineParser.h"
#include "core/base/Lock.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/io/ContainerConferenceFactory.h"

#include "core/data/TimeStamp.h"
#include "core/data/dmcp/PulseMessage.h"
#include "core/data/Configuration.h"
#include "core/dmcp/discoverer/Client.h"
#include "core/dmcp/ServerInformation.h"

#include "SuperComponent.h"
#include "ConnectedModule.h"

namespace supercomponent {

    using namespace core::base;
    using namespace core::data;
    using namespace core::exceptions;
    using namespace core::data::dmcp;
    using namespace core::dmcp;
    using namespace core::dmcp::connection;
    using namespace core::io;

    SuperComponent::SuperComponent(const int &argc, char **argv) :
        MasterModule(argc, argv),
        m_configuration(),
        m_configurationProvider(),
        m_discovererServer(),
        m_connectionServer(NULL),
        m_conference(NULL),
        m_modules(),
        m_shutdownModules(),
        m_moduleStatisticsMutex(),
        m_moduleStatistics(),
        m_managedLevel(core::dmcp::ServerInformation::ML_NONE),
        m_startOfCurrentCycle(),
        m_startOfLastCycle(),
        m_lastCycle(),
        m_lastWaitTime(0),
        m_shiftMicroseconds(0),
        m_timeoutACKMilliseconds(0),
        m_yieldMicroseconds(0),
        m_modulesToIgnore() {
        // Check for any running supercomponents.
        checkForSuperComponent();

        // We need to read the configuration file first as the command line parser queries some settings.
        cout << "(supercomponent) Parsing configuration file..." << endl;
        ifstream configStream("configuration", ios::in);
        if (configStream.good()) {
            configStream >> m_configuration;
        }
        else {
            OPENDAVINCI_CORE_THROW_EXCEPTION(ConfigurationFileNotFoundException, "Configuration stream invalid.");
        }

        // Parse command line arguments.
        parseAdditionalCommandLineParameters(argc, argv);

        const uint32_t SERVER_PORT = CONNECTIONSERVER_PORT_BASE + getCID();
        // Listen on all interfaces.
        ServerInformation serverInformation("0.0.0.0", SERVER_PORT, m_managedLevel);

        cout << "(supercomponent) Server information: " << serverInformation.toString() << endl;
        cout << "(supercomponent) Creating discoverer server..." << endl;
        m_discovererServer = new discoverer::Server(serverInformation,
													getMultiCastGroup(),
                                                    BROADCAST_PORT_SERVER,
                                                    BROADCAST_PORT_CLIENT,
                                                    m_modulesToIgnore);
        m_discovererServer->startResponding();

        cout << "(supercomponent) Creating connection server..." << endl;
        m_configurationProvider = GlobalConfigurationProvider(m_configuration);
        m_connectionServer = new connection::Server(serverInformation, m_configurationProvider);
        m_connectionServer->setConnectionHandler(this);

        m_conference = core::SharedPointer<ContainerConference>(ContainerConferenceFactory::getInstance().getContainerConference(getMultiCastGroup()));
        m_conference->setContainerListener(this);

        cout << "(supercomponent) Ready - managed level " << m_managedLevel << endl;
    }

    SuperComponent::~SuperComponent() {
    }

    const TimeStamp SuperComponent::getStartOfCurrentCycle() const {
        return m_startOfCurrentCycle;
    }

    const TimeStamp SuperComponent::getStartOfLastCycle() const {
        return m_startOfLastCycle;
    }

    void SuperComponent::parseAdditionalCommandLineParameters(const int &argc, char **argv) {
        CommandLineParser cmdParser;
        cmdParser.addCommandLineArgument("managed");

        cmdParser.parse(argc, argv);

        CommandLineArgument cmdArgumentMANAGED = cmdParser.getCommandLineArgument("managed");

        // Check the centrally maintained managed level.
        if (cmdArgumentMANAGED.isSet()) {
            string managedLevel = cmdArgumentMANAGED.getValue<string>();
            core::StringToolbox::trim(managedLevel);

            if (core::StringToolbox::equalsIgnoreCase(managedLevel, "none")) {
                m_managedLevel = core::dmcp::ServerInformation::ML_NONE;
            }
            if (core::StringToolbox::equalsIgnoreCase(managedLevel, "pulse")) {
                m_managedLevel = core::dmcp::ServerInformation::ML_PULSE;
            }
            if (core::StringToolbox::equalsIgnoreCase(managedLevel, "pulse_shift")) {
                m_managedLevel = core::dmcp::ServerInformation::ML_PULSE_SHIFT;

                m_shiftMicroseconds = 10 * 1000;
                try {
                    m_shiftMicroseconds = m_configuration.getValue<uint32_t>("supercomponent.pulseshift.shift");
                }
                catch(...) {
                    cerr << "(supercomponent) Value for 'supercomponent.pulseshift.shift' not found in configuration, using " << m_shiftMicroseconds << " as default." << endl;
                }
            }
            if (core::StringToolbox::equalsIgnoreCase(managedLevel, "pulse_time")) {
                m_managedLevel = core::dmcp::ServerInformation::ML_PULSE_TIME;
            }
            if (core::StringToolbox::equalsIgnoreCase(managedLevel, "pulse_time_ack") || core::StringToolbox::equalsIgnoreCase(managedLevel, "simulation") || core::StringToolbox::equalsIgnoreCase(managedLevel, "simulation_rt")) {
                if (core::StringToolbox::equalsIgnoreCase(managedLevel, "pulse_time_ack")) {
                    m_managedLevel = core::dmcp::ServerInformation::ML_PULSE_TIME_ACK;
                }
                if (core::StringToolbox::equalsIgnoreCase(managedLevel, "simulation")) {
                    m_managedLevel = core::dmcp::ServerInformation::ML_SIMULATION;
                }
                if (core::StringToolbox::equalsIgnoreCase(managedLevel, "simulation_rt")) {
                    m_managedLevel = core::dmcp::ServerInformation::ML_SIMULATION_RT;
                }

                m_timeoutACKMilliseconds = 1000;
                m_yieldMicroseconds = 5 * 1000;

                try {
                    m_timeoutACKMilliseconds = m_configuration.getValue<uint32_t>("supercomponent.pulsetimeack.timeout");
                }
                catch(...) {
                    cerr << "(supercomponent) Value for 'supercomponent.pulsetimeack.timeout' not found in configuration, using " << m_timeoutACKMilliseconds << " as default." << endl;
                }

                try {
                    m_yieldMicroseconds = m_configuration.getValue<uint32_t>("supercomponent.pulsetimeack.yield");
                }
                catch(...) {
                    cerr << "(supercomponent) Value for 'supercomponent.pulsetimeack.yield' not found in configuration, using " << m_yieldMicroseconds << " as default." << endl;
                }

                try {
                    string s = m_configuration.getValue<string>("supercomponent.pulsetimeack.exclude");
                    transform(s.begin(), s.end(), s.begin(), ::tolower);

                    m_modulesToIgnore = core::StringToolbox::split(s, ',');
                }
                catch(...) {
                    // If "supercomponent.pulsetimeack.exclude" is not specified, just ignore exception.
                }

            }
        }
    }

    void SuperComponent::checkForSuperComponent() {
        string noName = "";
        discoverer::Client discovererClient(getMultiCastGroup(),
                                            BROADCAST_PORT_SERVER,
                                            BROADCAST_PORT_CLIENT,
                                            noName);

         if ( discovererClient.existsServer() ) {
             cout << "(supercomponent) supercomponent already running for " << getMultiCastGroup() << endl;
             exit(-1);
         }
    }

    ModuleState::MODULE_EXITCODE SuperComponent::body() {
        uint32_t cumulatedTimeSlice = 0;
        const long ONE_SECOND_IN_MICROSECONDS = 1000 * 1000 * 1;

        vector<Container> containersToBeDistributedToModules;

        m_lastCycle = TimeStamp();
        while (getModuleState() == ModuleState::RUNNING) {
            TimeStamp current;
            m_startOfCurrentCycle = current;
            m_startOfLastCycle = m_lastCycle;

            {
                // Update statistics.
                Lock l(m_moduleStatisticsMutex);
                Container c(Container::MODULESTATISTICS, m_moduleStatistics);
                m_conference->send(c);
            }

            // Remove disconnected modules.
            m_shutdownModules.deleteAllModules();

            if (m_managedLevel == core::dmcp::ServerInformation::ML_NONE) {
                // Just sleep 2 seconds in the case of managed level == NONE.
                Thread::usleep(2 * ONE_SECOND_IN_MICROSECONDS);
            }
            else if ( (m_managedLevel == core::dmcp::ServerInformation::ML_PULSE) ||
                      (m_managedLevel == core::dmcp::ServerInformation::ML_PULSE_SHIFT) ||
                      (m_managedLevel == core::dmcp::ServerInformation::ML_PULSE_TIME) ||
                      (m_managedLevel == core::dmcp::ServerInformation::ML_PULSE_TIME_ACK) ||
                      (m_managedLevel == core::dmcp::ServerInformation::ML_SIMULATION) ||
                      (m_managedLevel == core::dmcp::ServerInformation::ML_SIMULATION_RT) ) {

                const float FREQ = getFrequency();
                const long TIME_CONSUMPTION_OF_CURRENT_SLICE = (current.toMicroseconds() - m_lastCycle.toMicroseconds()) - m_lastWaitTime;
                m_lastCycle = current;
                const long NOMINAL_DURATION_OF_ONE_SLICE = static_cast<long>((1.0f/FREQ) * ONE_SECOND_IN_MICROSECONDS);
                long WAITING_TIME_OF_CURRENT_SLICE = NOMINAL_DURATION_OF_ONE_SLICE - TIME_CONSUMPTION_OF_CURRENT_SLICE;

                if (isVerbose()) {
                    cerr << "(supercomponent) Waiting real slice: " << WAITING_TIME_OF_CURRENT_SLICE << ", nominal waiting slice: " << NOMINAL_DURATION_OF_ONE_SLICE << ", cumulated time slice: " << cumulatedTimeSlice << endl;
                }

                const TimeStamp supercomponent_now;
                PulseMessage pm(supercomponent_now, NOMINAL_DURATION_OF_ONE_SLICE, cumulatedTimeSlice);

                if (m_managedLevel == core::dmcp::ServerInformation::ML_PULSE) {
                    m_modules.pulse(pm);
                }
                else if (m_managedLevel == core::dmcp::ServerInformation::ML_PULSE_SHIFT) {
                    m_modules.pulseShift(pm, m_shiftMicroseconds);
                }
                else if (m_managedLevel == core::dmcp::ServerInformation::ML_PULSE_TIME) {
                    // Managed level ML_PULSE_TIME is handled by the dependent modules and thus, the regular pulse method can be called.
                    m_modules.pulse(pm);
                }
                else if (m_managedLevel == core::dmcp::ServerInformation::ML_PULSE_TIME_ACK) {
                    // Managed level ML_PULSE_TIME_ACK requires a confirmation from the dependent modules
                    // that the received PULSE has been processed.
                    //
                    // m_yieldMicroseconds specifies the amount of time that we are going to wait before
                    // we trigger the next module (send the pulse to it) to allow delivery of any packets
                    // on the OS level.
                    m_modules.pulse_ack(pm, m_timeoutACKMilliseconds, m_yieldMicroseconds, m_modulesToIgnore);
                }
                else if ( (m_managedLevel == core::dmcp::ServerInformation::ML_SIMULATION) || (m_managedLevel == core::dmcp::ServerInformation::ML_SIMULATION_RT) ) {
                    // Managed level ML_SIMULATION requires a confirmation from the dependent
                    // modules that the received PULSE has been processed and the connected modules need
                    // to return all Containers to be distributed to the connected modules in the next
                    // call cycle.
                    //
                    // m_yieldMicroseconds specifies the amount of time that we are going to wait before
                    // we trigger the next module (send the pulse to it) to allow delivery of any packets
                    // on the OS level.

                    // Set containers to be delivered to the connected modules.
                    pm.setListOfContainers(containersToBeDistributedToModules);

                    // Replicate containers to real UDP conference for modules that are excluded from the ML.
                    vector<Container>::iterator it = containersToBeDistributedToModules.begin();
                    while (it != containersToBeDistributedToModules.end()) {
                        m_conference->send(*it);
                        it++;
                        Thread::usleep(500);
                    }

                    // Clear containers from last cycle.
                    containersToBeDistributedToModules.clear();

                    // Save containers to be distributed in the next cycle.
                    containersToBeDistributedToModules = m_modules.pulse_ack_containers(pm, m_timeoutACKMilliseconds, m_yieldMicroseconds, m_modulesToIgnore);
                }

                // Increment the nomimal time slices.
                cumulatedTimeSlice = (cumulatedTimeSlice + NOMINAL_DURATION_OF_ONE_SLICE) % ONE_SECOND_IN_MICROSECONDS;

                // Ensure that we are not waiting in the case that we needed more than one second for this execution cycle.
                if (TIME_CONSUMPTION_OF_CURRENT_SLICE > ONE_SECOND_IN_MICROSECONDS) {
                    WAITING_TIME_OF_CURRENT_SLICE = 0;
                }
                m_lastWaitTime = WAITING_TIME_OF_CURRENT_SLICE;

                // Check if we really need to artificially consume this time slice in real time or if we can run as fast as possible.
                if (m_managedLevel == core::dmcp::ServerInformation::ML_SIMULATION) {
                    // We can run as fast as possible but we need to allow some scheduling for the connected modules.
                    Thread::usleep(1000);
                }
                else {
                    Thread::usleep(WAITING_TIME_OF_CURRENT_SLICE);
                }
            }
        }

        m_conference->setContainerListener(NULL);

        // Clean up connections.
        cout << "(supercomponent) Closing down... ";
        delete m_connectionServer;
        m_connectionServer = NULL;

        delete m_discovererServer;
        m_discovererServer = NULL;

        m_modules.deleteAllModules();

        cout << "done." << endl;

        return ModuleState::OKAY;
    }

    void SuperComponent::onNewModule(ModuleConnection* mc) {
        mc->waitForModuleDescription();
        cout << "(supercomponent) New connected module " << mc->getModuleDescriptor().toString() << endl;

        ConnectedModule* module = new ConnectedModule(mc, ModuleState::NOT_RUNNING);
        mc->setModuleStateListener(this);

        if (m_modules.hasModule(mc->getModuleDescriptor())) {
            cout << "(supercomponent) WARNING!!! MODULE " << mc->getModuleDescriptor().toString() << " AREADY CONNECTED: Consider using --id to differentiate modules!" << endl;
        }
        else {
            m_modules.addModule(mc->getModuleDescriptor(), module);
        }
    }

    void SuperComponent::handleChangeState(const ModuleDescriptor& md, const ModuleState::MODULE_STATE &ms) {
        cout << "(supercomponent) Module " << md.toString() << " changed state to " << ModuleState::getAsString(ms) << endl;
        if (m_modules.hasModule(md)) {
            m_modules.getModule(md)->setState(ms);
        }
    }

    void SuperComponent::handleExitCode(const ModuleDescriptor& md, const ModuleState::MODULE_EXITCODE &me) {
        cout << "(supercomponent) Module " << md.toString() << " shutdown with exitcode " << ModuleState::getAsString(me) << endl;

        if (m_modules.hasModule(md)) {
            ConnectedModule* module = m_modules.getModule(md);
            m_modules.removeModule(md);
            module->setExitCode();
            m_shutdownModules.addModule(md, module);
        }
    }

    void SuperComponent::handleRuntimeStatistics(const ModuleDescriptor& md, const RuntimeStatistic& rs) {
        Lock l(m_moduleStatisticsMutex);
        m_moduleStatistics.setRuntimeStatistic(md, rs);
    }

    void SuperComponent::handleConnectionLost(const ModuleDescriptor& md) {
        // This methods is called when a module terminates not properly.
        if (m_modules.hasModule(md)) {
            cout << "(supercomponent) Connection to module " << md.toString() << " lost" << endl;
            ConnectedModule* module = m_modules.getModule(md);
            m_modules.removeModule(md);
            m_shutdownModules.addModule(md, module);
        }
        else {
            if (m_shutdownModules.hasModule(md)) {
                if (!m_shutdownModules.getModule(md)->hasExitCode()) {
                    cout << "(supercomponent) Something went wrong...lost connection to module " << md.toString();
                    cout << ", module is in shutdownModule list but has not set an ExitCode." << endl;
                }
            }
        }
    }

    void SuperComponent::handleUnkownContainer(const ModuleDescriptor& md, const Container& container) {
        cout << "Received unknown container " << container.toString() << "from " << md.toString() << endl;
    }

    void SuperComponent::nextContainer(Container &/*container*/) {}
    
} // supercomponent

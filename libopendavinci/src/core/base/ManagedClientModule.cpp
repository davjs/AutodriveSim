/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#include "core/base/ManagedClientModule.h"

#include "context/base/RuntimeControl.h"

namespace core {
    namespace base {

        using namespace std;

        using namespace core;
        using namespace core::base;
        using namespace core::data;
        using namespace core::exceptions;

        ManagedClientModule::ManagedClientModule(const int32_t &argc, char **argv, const string &name) throw (InvalidArgumentException) :
            ClientModule(argc, argv, name),
            m_startOfCurrentCycle(),
            m_startOfLastCycle(),
            m_lastCycle(),
            m_lastWaitTime(0),
            m_cycleCounter(0),
            m_profilingFile(NULL),
            m_firstCallToBreakpoint_ManagedLevel_Pulse(true),
            m_time(),
            m_controlledTimeFactory(NULL),
            m_pulseMessage(),
            m_localContainerConference(),
            m_hasExternalContainerConference(false),
            m_containerConference(NULL) {}

        ManagedClientModule::~ManagedClientModule() {
            if (m_profilingFile != NULL) {
                m_profilingFile->flush();
                m_profilingFile->close();
            }

            if (m_hasExternalContainerConference) {
                OPENDAVINCI_CORE_DELETE_POINTER(m_containerConference);
                m_hasExternalContainerConference = false;
            }

            OPENDAVINCI_CORE_DELETE_POINTER(m_profilingFile);
        }

        void ManagedClientModule::DMCPconnectionLost() {}

        void ManagedClientModule::setContainerConference(core::io::ContainerConference *c) {
            if (m_hasExternalContainerConference) {
                OPENDAVINCI_CORE_DELETE_POINTER(m_containerConference);
                m_hasExternalContainerConference = false;
            }

            if (c != NULL) {
                m_containerConference = c;
                m_hasExternalContainerConference = true;
            }
        }

        core::io::ContainerConference* ManagedClientModule::getContainerConference() {
            return m_containerConference;
        }

        const TimeStamp ManagedClientModule::getStartOfCurrentCycle() const {
            return m_startOfCurrentCycle;
        }

        const TimeStamp ManagedClientModule::getStartOfLastCycle() const {
            return m_startOfLastCycle;
        }

        void ManagedClientModule::wait() {
            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_NONE) {
                wait_ManagedLevel_None();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE) {
                wait_ManagedLevel_Pulse();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE_SHIFT) {
                wait_ManagedLevel_Pulse_Shift();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE_TIME) {
                wait_ManagedLevel_Pulse_Time();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE_TIME_ACK) {
                wait_ManagedLevel_Pulse_Time_Ack();
            }

            if ( (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_SIMULATION) || (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_SIMULATION_RT) ) {
                wait_ManagedLevel_Pulse_Time_Ack_Containers();
            }
        }

        ModuleState::MODULE_EXITCODE ManagedClientModule::runModuleImplementation() {
            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_NONE) {
                return runModuleImplementation_ManagedLevel_None();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE) {
                return runModuleImplementation_ManagedLevel_Pulse();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE_SHIFT) {
                return runModuleImplementation_ManagedLevel_Pulse_Shift();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE_TIME) {
                return runModuleImplementation_ManagedLevel_Pulse_Time();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE_TIME_ACK) {
                return runModuleImplementation_ManagedLevel_Pulse_Time_Ack();
            }

            if ( (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_SIMULATION) || (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_SIMULATION_RT) ) {
                return runModuleImplementation_ManagedLevel_Pulse_Time_Ack_Containers();
            }

            return ModuleState::OKAY;
        }

        void ManagedClientModule::reached() {
            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE) {
                reached_ManagedLevel_Pulse();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE_SHIFT) {
                reached_ManagedLevel_Pulse_Shift();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE_TIME) {
                reached_ManagedLevel_Pulse_Time();
            }

            if (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_PULSE_TIME_ACK) {
                reached_ManagedLevel_Pulse_Time_Ack();
            }

            if ( (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_SIMULATION) || (getServerInformation().getManagedLevel() == core::dmcp::ServerInformation::ML_SIMULATION_RT) ) {
                reached_ManagedLevel_Pulse_Time_Ack_Containers();
            }
        }

        void ManagedClientModule::logProfilingData(const TimeStamp &current, const TimeStamp &lastCycle, const float &freq, const long &lastWaitTime, const long &timeConsumptionCurrent, const long &nominalDuration, const long &waitingTimeCurrent, const int32_t &cycleCounter) {
            if (m_profilingFile == NULL) {
                stringstream sstr;
                sstr << getName() << "_" << TimeStamp().getYYYYMMDD_HHMMSS() << ".profiling.csv";
                m_profilingFile = new ofstream();
                m_profilingFile->open(sstr.str().c_str(), ios::out | ios::app);

                (*m_profilingFile) <<
                    "timestamp_current_cycle" << ";" <<
                    "timestamp_last_cycle" << ";" <<
                    "freq" << ";" <<
                    "last_wait_time" << ";" <<
                    "time_consumption_current" << ";" <<
                    "nominal_duration" << ";" <<
                    "waiting_time_current" << ";" <<
                    "percentage_load_current_slice" << ";" <<
                    "percentage_waiting_current_slice" << ";" <<
                    "cycle_counter" << endl;
            }

            if (m_profilingFile != NULL) {
                (*m_profilingFile) <<
                    current.toMicroseconds() << ";" <<
                    lastCycle.toMicroseconds() << ";" <<
                    freq << ";" <<
                    lastWaitTime << ";" <<
                    timeConsumptionCurrent << ";" <<
                    nominalDuration << ";" <<
                    waitingTimeCurrent << ";" <<
                    (100.0-(waitingTimeCurrent*100.0/((float)nominalDuration))) << ";" <<
                    (waitingTimeCurrent*100.0/((float)nominalDuration)) << ";" <<
                    cycleCounter << endl;
                m_profilingFile->flush();
            }
        }

        ///////////////////////////////////////////////////////////////////////
        // Implementation for managed level none.
        ///////////////////////////////////////////////////////////////////////

        core::base::ModuleState::MODULE_EXITCODE ManagedClientModule::runModuleImplementation_ManagedLevel_None() {
            ModuleState::MODULE_EXITCODE retVal = ModuleState::OKAY;

            try {
                // Setup the module itself.
                setUp();

                setModuleState(ModuleState::RUNNING);
                if (getDMCPClient().isValid()) {
                    getDMCPClient()->sendModuleState(ModuleState::RUNNING);
                }

                // Execute the module's body.
                retVal = body();

                setModuleState(ModuleState::NOT_RUNNING);
                if (getDMCPClient().isValid()) {
                    getDMCPClient()->sendModuleState(ModuleState::NOT_RUNNING);
                }

                // Clean up.
                tearDown();
            } catch (std::exception &e) {
                // Try to catch any exception derived from std::exception and print32_t out reason.
                clog << e.what() << endl;
                retVal = ModuleState::EXCEPTION_CAUGHT;
            } catch (std::string &str) {
                clog << "string exception caught in ClientModule::run()" << endl;
                clog << str << endl;
                retVal = ModuleState::SERIOUS_ERROR;
            } catch (...) {
                // Try to catch anything else print32_t generic error.
                clog << "Unknown exception caught in ClientModule::run()" << endl;
                retVal = ModuleState::SERIOUS_ERROR;
            }

            return retVal;
        }

        uint32_t ManagedClientModule::getWaitingTimeAndUpdateRuntimeStatistics() {
            // Update liveliness.
            m_cycleCounter++;

            // Get "now".
            TimeStamp current;
            m_startOfCurrentCycle = current;
            m_startOfLastCycle = m_lastCycle;

            const float FREQ = getFrequency();
            const long TIME_CONSUMPTION_OF_CURRENT_SLICE = (current.toMicroseconds() - m_lastCycle.toMicroseconds()) - m_lastWaitTime;

            const long ONE_SECOND_IN_MICROSECONDS = 1000 * 1000 * 1;
            const long NOMINAL_DURATION_OF_ONE_SLICE = static_cast<long>((1.0f/FREQ) * ONE_SECOND_IN_MICROSECONDS);
            const long WAITING_TIME_OF_CURRENT_SLICE = NOMINAL_DURATION_OF_ONE_SLICE - TIME_CONSUMPTION_OF_CURRENT_SLICE;

            // Inform supercomponent about statistical runtime data.
            bool sendStatistics = false;
            if (FREQ < 1) {
                sendStatistics = true;

                // Avoid overflows.
                m_cycleCounter = (m_cycleCounter % 1000);
            }
            else {
				const int32_t CYCLES_PER_SECOND = static_cast<int32_t>(fabs(floor(FREQ + 0.5)));
                if ( (m_cycleCounter % CYCLES_PER_SECOND) == 0 ) {
                    sendStatistics = true;
                    m_cycleCounter = 0;
                }
            }

            // Send RuntimeStatistic to supercomponent.
            if (sendStatistics && getDMCPClient().isValid()) {
                RuntimeStatistic rts;
                rts.setSliceConsumption((float)TIME_CONSUMPTION_OF_CURRENT_SLICE/(float)NOMINAL_DURATION_OF_ONE_SLICE);
                getDMCPClient()->sendStatistics(rts);
            }

            // Check whether we need to save profiling data.
            if (isProfiling()) {
                logProfilingData(current, m_lastCycle, FREQ, m_lastWaitTime, TIME_CONSUMPTION_OF_CURRENT_SLICE, NOMINAL_DURATION_OF_ONE_SLICE, WAITING_TIME_OF_CURRENT_SLICE, m_cycleCounter);
            }

            // Store "now" to m_lastCycle for usage in next cycle.
            m_lastCycle = current;

            // Save the time to be waited.
            if (WAITING_TIME_OF_CURRENT_SLICE > 0) {
                m_lastWaitTime = WAITING_TIME_OF_CURRENT_SLICE;
            }
            else {
                m_lastWaitTime = 0;
            }

            return WAITING_TIME_OF_CURRENT_SLICE;
        }

        void ManagedClientModule::wait_ManagedLevel_None() {
            const long WAITING_TIME_OF_CURRENT_SLICE = getWaitingTimeAndUpdateRuntimeStatistics();

            // Enforce waiting to consume the rest of the time slice but ensure that there is no overflow.
            const long ONE_SECOND_IN_MICROSECONDS = 1000 * 1000 * 1;
            if ( (WAITING_TIME_OF_CURRENT_SLICE > 0) && (WAITING_TIME_OF_CURRENT_SLICE < ONE_SECOND_IN_MICROSECONDS) ) {
                Thread::usleep(WAITING_TIME_OF_CURRENT_SLICE);
            }

            if (isVerbose()) {
                clog << "Starting next cycle at " << TimeStamp().toString() << endl;
            }
        }

        ///////////////////////////////////////////////////////////////////////
        // Implementation for managed level pulse.
        ///////////////////////////////////////////////////////////////////////

        void ManagedClientModule::reached_ManagedLevel_Pulse() {
            if (m_firstCallToBreakpoint_ManagedLevel_Pulse) {
                // Align the further execution of a module's body until this realtime clock matches with supercomponent's realtime clock for the required waiting slice.
                setBreakpoint(NULL);
                m_firstCallToBreakpoint_ManagedLevel_Pulse = false;

                // Align the component ten times.
                uint32_t aligner = 10;
                while (aligner-- > 0) {
                    const core::data::dmcp::PulseMessage pm = getDMCPClient()->getPulseMessage();

                    const long ONE_SECOND_IN_MICROSECONDS = 1000 * 1000 * 1;
                    const long ADJUSTMENT_TIME_TO_VIRTUAL_ONE_SECOND = (ONE_SECOND_IN_MICROSECONDS - pm.getCumulatedTimeSlice());

                    const TimeStamp module_now;
                    const long ADJUSTMENT_TIME_TO_ALIGN_REALTIME = (module_now.toMicroseconds() - pm.getRealtimeFromSupercomponent().toMicroseconds());

                    const long ADJUSTMENT_TIME = ADJUSTMENT_TIME_TO_VIRTUAL_ONE_SECOND - ADJUSTMENT_TIME_TO_ALIGN_REALTIME;

                    if (ADJUSTMENT_TIME > 0) {
                        Thread::usleep(ADJUSTMENT_TIME);

                        clog << "(ManagedClientModule) Adjust execution to next timeslice that is aligned with supercomponent: " << ADJUSTMENT_TIME << " microseconds." << endl;
                    }
                }
            }
        }

        core::base::ModuleState::MODULE_EXITCODE ManagedClientModule::runModuleImplementation_ManagedLevel_Pulse() {
            // For the very first call to getModuleState(), delay the sliced execution to the next timeslice.
            m_firstCallToBreakpoint_ManagedLevel_Pulse = true;
            setBreakpoint(this);            

            ModuleState::MODULE_EXITCODE retVal = ModuleState::OKAY;

            try {
                // Setup the module itself.
                setUp();

                setModuleState(ModuleState::RUNNING);
                if (getDMCPClient().isValid()) {
                    getDMCPClient()->sendModuleState(ModuleState::RUNNING);
                }

                // Execute the module's body.
                retVal = body();

                setModuleState(ModuleState::NOT_RUNNING);
                if (getDMCPClient().isValid()) {
                    getDMCPClient()->sendModuleState(ModuleState::NOT_RUNNING);
                }

                // Clean up.
                tearDown();
            } catch (std::exception &e) {
                // Try to catch any exception derived from std::exception and print32_t out reason.
                clog << e.what() << endl;
                retVal = ModuleState::EXCEPTION_CAUGHT;
            } catch (std::string &str) {
                clog << "string exception caught in ClientModule::run()" << endl;
                clog << str << endl;
                retVal = ModuleState::SERIOUS_ERROR;
            } catch (...) {
                // Try to catch anything else print32_t generic error.
                clog << "Unknown exception caught in ClientModule::run()" << endl;
                retVal = ModuleState::SERIOUS_ERROR;
            }

            return retVal;
        }

        void ManagedClientModule::wait_ManagedLevel_Pulse() {
            // No specific implementation for waiting in mode managed_level == pulse.
            wait_ManagedLevel_None();
        }

        ///////////////////////////////////////////////////////////////////////
        // Implementation for managed level pulse shift.
        ///////////////////////////////////////////////////////////////////////

        void ManagedClientModule::reached_ManagedLevel_Pulse_Shift() {
            // No specific implementation for waiting in mode managed_level == pulse_shift.
            reached_ManagedLevel_Pulse();
        }

        core::base::ModuleState::MODULE_EXITCODE ManagedClientModule::runModuleImplementation_ManagedLevel_Pulse_Shift() {
            // No specific implementation for waiting in mode managed_level == pulse_shift 
            return runModuleImplementation_ManagedLevel_Pulse();
        }

        void ManagedClientModule::wait_ManagedLevel_Pulse_Shift() {
            // No specific implementation for waiting in mode managed_level == pulse_shift.
            wait_ManagedLevel_None();
        }

        ///////////////////////////////////////////////////////////////////////
        // Implementation for managed level pulse time (i.e. the execution of
        // this module is suspended unless we receive the next pulse.
        ///////////////////////////////////////////////////////////////////////

        void ManagedClientModule::reached_ManagedLevel_Pulse_Time() {
            // Get next PulseMessage. This call blocks until the next PulseMessage has been received.
            m_pulseMessage = getDMCPClient()->getPulseMessage();

            // Check whether our clock was already initialized (i.e. getSeconds() > 0).
            if (m_time.now().getSeconds() < 1) {
                // Set seconds of our virtual clock to the clock from supercomponents.
                m_time = context::base::Clock(m_pulseMessage.getRealtimeFromSupercomponent().getSeconds(), 0);
            }

            // Increment the virtual time by the nominal value of the time slice
            // provided by from supercomponent. As PulseMessage provides this
            // value in microseconds, we need to convert to milliseconds.
            const uint32_t INCREMENT_IN_MS = m_pulseMessage.getNominalTimeSlice()/1000.0;
            m_time.increment(INCREMENT_IN_MS);

            // Set the new system time in the TimeFactory.
            m_controlledTimeFactory->setTime(m_time.now());

            // Update the RuntimeStatistics which will be done by the following method.
            getWaitingTimeAndUpdateRuntimeStatistics();

            if (isVerbose()) {
                clog << "Starting next cycle at " << TimeStamp().toString() << endl;
            }
        }

        core::base::ModuleState::MODULE_EXITCODE ManagedClientModule::runModuleImplementation_ManagedLevel_Pulse_Time() {
            // In the controlled pulse_time mode, the time pulses are provided
            // centrally from supercomponent and each component is incrementing
            // the local time based on these pulses.
            //
            // Therefore, the local TimeFactory that wraps the local system
            // time needs to be disabled and exchanged by a controllable one.

            // 1) Disable the existing TimeFactory.
            context::base::RuntimeControl::DisableTimeFactory dtf;
            dtf.disable();

            // 2) Create a controllable TimeFactory.
            m_controlledTimeFactory = new context::base::ControlledTimeFactory();

            // 3) Initialize the new TimeFactory with the new actual time.
            m_controlledTimeFactory->setTime(m_time.now());

            // 4) Run the module implementation as usual.
            core::base::ModuleState::MODULE_EXITCODE moduleExitCode = runModuleImplementation_ManagedLevel_Pulse();

            // 5) Disable the TimeFactory to restore previous behavior.
            dtf.disable();

            // 6) Return the module's exit code.
            return moduleExitCode;
        }

        void ManagedClientModule::wait_ManagedLevel_Pulse_Time() {
            // As the managed level ML_PULSE_TIME uses a breakpoint, the wait() method
            // will not be called at all. Thus, all profiling information needs to be
            // handled in reached_ManagedLevel_Pulse_Time().
        }

        ///////////////////////////////////////////////////////////////////////
        // Implementation for managed level pulse time ack (i.e. the execution of
        // this module is suspended unless we receive the next pulse AND we need
        // to confirm the processing of the currently received pulse.
        ///////////////////////////////////////////////////////////////////////

        void ManagedClientModule::reached_ManagedLevel_Pulse_Time_Ack() {
            // For a further explanation, please see runModuleImplementation_ManagedLevel_Pulse_Time_Ack().
            //
            // Here, we simply confirm that we have received AND processed
            // our recently received pulse message.
            if (getDMCPClient().isValid()) {
                getDMCPClient()->sendPulseAck();
            }

            // Call reached_ManagedLevel_Pulse_Time() that will wait for the
            // next pulse message.
            reached_ManagedLevel_Pulse_Time();
        }

        core::base::ModuleState::MODULE_EXITCODE ManagedClientModule::runModuleImplementation_ManagedLevel_Pulse_Time_Ack() {
            // In managed level ML_PULSE_TIME_ACK, supercomponent is continuously
            // sending pulses but is awaiting for an acknowledgment for every
            // successfully received pulse.
            //
            // We will send the acknowledgment for every pulse just before we are
            // going to wait for the new one. Thus, we confirm the reception of
            // a pulse AND confirm that we have done our algorithmic processing.
            //
            // Thereby, we can enforce a centralized deterministic scheduling by
            // supercomponent that we only send the pulse to the next module when
            // the previous module has be called and processed completely in its
            // assigned time slice.
            //
            // The ACK message will be sent in reached_ManagedLevel_Pulse_Time_Ack().
            //
            // Thus, we simply call the overwritten implementation from
            // runModuleImplementation_ManagedLevel_Pulse_Time() here that
            // will replace the real time with a virtual time.

            return runModuleImplementation_ManagedLevel_Pulse_Time();
        }

        void ManagedClientModule::wait_ManagedLevel_Pulse_Time_Ack() {
            // As the managed level ML_PULSE_TIME_ACK uses a breakpoint, the wait() method
            // will not be called at all. Thus, all profiling information needs to be
            // handled in reached_ManagedLevel_Pulse_Time_Ack().
        }


        ///////////////////////////////////////////////////////////////////////
        // Implementation for ML_SIMULATION and ML_SIMULATION_RT (i.e. the
        // execution of this module is suspended unless we receive the next pulse
        // AND we need to deliver all containers to ourselves before we start the
        // next iterator of the loop's body
        // AND we need to confirm the processing of the currently received pulse
        // AND we need to return all containers that we want to deliver to other
        // modules in the NEXT cycle.
        ///////////////////////////////////////////////////////////////////////

        void ManagedClientModule::reached_ManagedLevel_Pulse_Time_Ack_Containers() {
            // For a further explanation, please see runModuleImplementation_ManagedLevel_Pulse_Time_Ack_Containers().
            //
            // Here, we simply confirm that we have received AND processed
            // our recently received pulse message.

            // Confirm the successful processing of the received pulse and
            // deliver all containers from this module to supercomponent.
            if (getDMCPClient().isValid()) {
                getDMCPClient()->sendPulseAckContainers(m_localContainerConference.getListOfContainers());

                // After all containers have been delivered to supercomponent,
                // reset the list of containers from the last iteration in our own
                // ContainerConference before we initiate the next cycle.
                m_localContainerConference.clearListOfContainers();
            }

            // Call reached_ManagedLevel_Pulse_Time() that will wait for the
            // next pulse message.
            reached_ManagedLevel_Pulse_Time();

            // Deliver containers from last cycle before starting current cycle.
            vector<Container> listOfContainersToBeDistributed = m_pulseMessage.getListOfContainers();
            vector<Container>::iterator it = listOfContainersToBeDistributed.begin();
            while (it != listOfContainersToBeDistributed.end()) {
                Container c = *it;
                c.setReceivedTimeStamp(TimeStamp());
                m_localContainerConference.receiveFromLocal(c);
                it++;
            }

            // When the program flow leaves this method, the next iteration
            // in a program's while loop will start.
        }

        core::base::ModuleState::MODULE_EXITCODE ManagedClientModule::runModuleImplementation_ManagedLevel_Pulse_Time_Ack_Containers() {
            // In managed level ML_SIMULATION and ML_SIMULATION_RT, supercomponent is
            // continuously sending pulses but is awaiting for an acknowledgment
            // for every successfully received pulse.
            //
            // We will send the acknowledgment for every pulse just before we are
            // going to wait for the new one. Thus, we confirm the reception of
            // a pulse AND confirm that we have done our algorithmic processing.
            //
            // Thereby, we can enforce a centralized deterministic scheduling by
            // supercomponent that we only send the pulse to the next module when
            // the previous module has be called and processed completely in its
            // assigned time slice.
            //
            // The ACK message will be sent in reached_ManagedLevel_Pulse_Time_Ack_Containers().
            //
            // Futhermore, we will distribute any containers from the previous execution
            // cycle to our nextContainer-listeners AND we will collect all
            // containers to be distributed in return to supercomponent for
            // distribution to all connected modules. Therefore, we need to disable
            // any existing ContainerConference.

            if (m_hasExternalContainerConference) {
                if (m_containerConference != NULL) {
                    m_localContainerConference.setContainerListener(m_containerConference->getContainerListener());
                }

                OPENDAVINCI_CORE_DELETE_POINTER(m_containerConference);
                m_hasExternalContainerConference = false;

                m_containerConference = &m_localContainerConference;

                clog << "Existing ContainerConference disabled and ContainerListener redirected to localContainerConference." << endl;
            }

            // Now, we simply call the overwritten implementation from
            // runModuleImplementation_ManagedLevel_Pulse_Time() here that
            // will replace the real time with a virtual time.

            return runModuleImplementation_ManagedLevel_Pulse_Time();
        }

        void ManagedClientModule::wait_ManagedLevel_Pulse_Time_Ack_Containers() {
            // As the managed level ML_SIMULATION uses a breakpoint, the
            // wait() method will not be called at all. Thus, all profiling information
            // needs to be handled in reached_ManagedLevel_Pulse_Time_Ack().
        }

    }
} // core::base

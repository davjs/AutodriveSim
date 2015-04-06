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

#include <cerrno>
#include <iostream>
#include <sstream>

#include "core/base/Lock.h"
#include "core/base/ModuleState.h"
#include "core/base/Thread.h"
#include "core/exceptions/Exceptions.h"
#include "context/base/ConferenceClientModuleRunner.h"
#include "context/base/ControlledContainerConferenceForSystemUnderTest.h"
#include "context/base/TimeConstants.h"

namespace context {
    namespace base {

        using namespace std;
        using namespace core::base;
        using namespace core::exceptions;
        using namespace core::base;

        // If the dynamic cast fails, the user did not call RuntimeControl::setup(RuntimeControl::TAKE_CONTROL).
        ConferenceClientModuleRunner::ConferenceClientModuleRunner(ConferenceClientModule &ccm) :
            m_conferenceClientModuleStarted(false),
            m_conferenceClientModuleFinishedMutex(),
            m_conferenceClientModuleFinished(false),
            m_conferenceClientModule(ccm),
            m_blockableContainerListener(dynamic_cast<ControlledContainerConferenceForSystemUnderTest&>(ccm.getConference()).getBlockableContainerReceiver()),
            m_runModuleBreakpoint(dynamic_cast<ControlledContainerConferenceForSystemUnderTest&>(ccm.getConference()).getBlockableContainerReceiver()) {
            ccm.setBreakpoint(&m_runModuleBreakpoint);
        }

        ConferenceClientModuleRunner::~ConferenceClientModuleRunner() {
            // Unlock the app's sending.
            m_blockableContainerListener.setNextContainerAllowed(true);
        }

        float ConferenceClientModuleRunner::getFrequency() const {
            return m_conferenceClientModule.getFrequency();
        }

        void ConferenceClientModuleRunner::step(const core::wrapper::Time &t) {
            if (needsExecution(t)) {
                clog << "[APP] at " << t.getSeconds() << "." << t.getPartialMicroseconds() << endl;

                // Start application as independent thread at first call.
                if (!m_conferenceClientModuleStarted) {
                    start();
                    m_conferenceClientModuleStarted = true;
                }
                else {
                    // OTHERWISE!!!! continue held execution.
                    m_runModuleBreakpoint.continueExecution();
                }

                // Waiting for breakpoint.
                uint32_t waitingForReachingBreakpoint = 0;
                while (!m_runModuleBreakpoint.hasReached()) {
                    Thread::usleep(TimeConstants::ONE_MILLISECOND_IN_MICROSECONDS);
                    waitingForReachingBreakpoint += TimeConstants::ONE_MILLISECOND_IN_MICROSECONDS;

                    if (waitingForReachingBreakpoint > TimeConstants::MAX_WAIT_FOR_REACHING_BREAKPOINT_PER_CYCLE) {
                        stringstream reason;
                        reason << m_conferenceClientModule.getName() << " is not responding after " << (TimeConstants::MAX_WAIT_FOR_REACHING_BREAKPOINT_PER_CYCLE / TimeConstants::ONE_SECOND_IN_MICROSECONDS) << "s." << endl;

                        // Throw exception to kill ourselves.
                        errno = 0;
                        OPENDAVINCI_CORE_THROW_EXCEPTION(ModulesNotRespondingException, reason.str());
                    }
                }
            }
        }

        void ConferenceClientModuleRunner::beforeStop() {
            // Stop module.
            m_conferenceClientModule.setModuleState(ModuleState::NOT_RUNNING);

            // Remove breakpoint.
            m_conferenceClientModule.setBreakpoint(NULL);

            // Unlock the app's sending since we're leaving.
            m_blockableContainerListener.setNextContainerAllowed(true);

            // Release interrupted application for last time.
            m_runModuleBreakpoint.continueExecution();
        }

        bool ConferenceClientModuleRunner::hasFinished() const {
            // This method returns true until runModule returned.
            bool retVal = true;
            {
                Lock l(m_conferenceClientModuleFinishedMutex);
                retVal = m_conferenceClientModuleFinished;
            }
            return retVal;
        }

        void ConferenceClientModuleRunner::run() {
            // Allow sending containers for applications which already send containers BEFORE they call getModuleState() for the first time.
            m_blockableContainerListener.setNextContainerAllowed(true);

            serviceReady();

            if (m_conferenceClientModule.runModule() == ModuleState::OKAY) {
                // After finishing the application, report that no more execution is necessary.
                Lock l(m_conferenceClientModuleFinishedMutex);
                m_conferenceClientModuleFinished = true;

                // Finally reaching breakpoint (since RuntimeControl is waiting for unlocking its waiting).
                m_runModuleBreakpoint.setFinallyReaching();
            }
            else {
                // Otherwise let RuntimeControl kill us.
            }
        }

    }
} // context::base

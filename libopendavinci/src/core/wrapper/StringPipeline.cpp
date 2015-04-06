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

#include "core/wrapper/ConcurrencyFactory.h"
#include "core/wrapper/ConditionFactory.h"
#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/StringPipeline.h"

namespace core {
    namespace wrapper {

        using namespace std;

        StringPipeline::StringPipeline() :
                m_queueCondition(NULL),
                m_queueMutex(NULL),
                m_queue(),
                m_stringListenerMutex(NULL),
                m_stringListener(NULL),
                m_thread(NULL),
                m_threadStateMutex(NULL),
                m_threadState(true) {
            m_queueCondition = ConditionFactory::createCondition();
            if (m_queueCondition == NULL) {
                stringstream s;
                s << "Error while creating condition at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }

            m_queueMutex = MutexFactory::createMutex();
            if (m_queueMutex == NULL) {
                stringstream s;
                s << "Error while creating mutex at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }

            m_stringListenerMutex = MutexFactory::createMutex();
            if (m_stringListenerMutex == NULL) {
                stringstream s;
                s << "Error while creating mutex at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }

            m_threadStateMutex = MutexFactory::createMutex();
            if (m_threadStateMutex == NULL) {
                stringstream s;
                s << "Error while creating mutex at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }
        }

        StringPipeline::~StringPipeline() {
            // Stop the queue.
            stop();

            // Stop thread.
            if (m_thread  != NULL) {
                m_thread->stop();
            }

            // Destroy mutex.
            if (m_queueMutex != NULL) {
                delete m_queueMutex;
            }
            m_queueMutex = NULL;

            // Destroy condition.
            if (m_queueCondition != NULL) {
                delete m_queueCondition;
            }
            m_queueCondition = NULL;

            // Destroy thread.
            if (m_thread != NULL) {
                delete m_thread;
            }
            m_thread = NULL;

            if (m_stringListenerMutex != NULL) {
                delete m_stringListenerMutex;
            }
            m_stringListenerMutex = NULL;

            if (m_threadStateMutex != NULL) {
                delete m_threadStateMutex;
            }
            m_threadStateMutex = NULL;
        }

        void StringPipeline::start() {
            setRunning(true);

            // Create thread for encapsulating string distribution.
            m_thread = ConcurrencyFactory::createThread(*this);
            if (m_thread == NULL) {
                stringstream s;
                s << "Error while creating thread at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }

            // Start thread.
            m_thread->start();
        }

        void StringPipeline::stop() {
            if (isRunning()) {
                // Stop runnable.
                setRunning(false);
            }
            // Wake awaiting threads.
            m_queueCondition->wakeAll();
        }

        void StringPipeline::setStringListener(StringListener *sl) {
            m_stringListenerMutex->lock();
            {
                // Prevent listening by ourselves!
                if (sl != this) {
                    m_stringListener = sl;
                }
            }
            m_stringListenerMutex->unlock();
        }

        void StringPipeline::nextString(const string &s) {
            m_queueCondition->lock();
            {
                // Enter new data.
                m_queueMutex->lock();
                m_queue.push(s);
                m_queueMutex->unlock();

                // Wake awaiting threads.
                m_queueCondition->wakeAll();
            }
            m_queueCondition->unlock();
        }

        void StringPipeline::run() {
            while (isRunning()) {
                m_queueCondition->lock();
                m_queueCondition->waitOnSignal();
                m_queueCondition->unlock();

                if (isRunning()) {
                    uint32_t numberOfEntries = 0;

                    // Determine the amount of current entries.
                    m_queueMutex->lock();
                    {
                        numberOfEntries = static_cast<uint32_t>(m_queue.size());
                    }
                    m_queueMutex->unlock();

                    // Read all entries and distribute using the stringListener.
                    m_stringListenerMutex->lock();
                    {
                        if (m_stringListener != NULL) {
                            // At this position, the number of entries contains at least numberOfEntries elements.
                            string entry;
                            for (uint32_t i = 0; i < numberOfEntries; i++) {
                                // Acquire next entry.
                                m_queueMutex->lock();
                                {
                                    entry = m_queue.front();
                                }
                                m_queueMutex->unlock();

                                // Distribute entry to connected listeners while NOT locking the queue.
                                m_stringListener->nextString(entry);

                                // Remove processed entry.
                                m_queueMutex->lock();
                                {
                                    m_queue.pop();
                                }
                                m_queueMutex->unlock();
                            }
                        }
                    }
                    m_stringListenerMutex->unlock();
                }
            }
        }

        void StringPipeline::setRunning(const bool &b) {
            m_threadStateMutex->lock();
            {
                m_threadState = b;
            }
            m_threadStateMutex->unlock();
        }

        bool StringPipeline::isRunning() {
            bool retVal = false;
            m_threadStateMutex->lock();
            {
                retVal = m_threadState;
            }
            m_threadStateMutex->unlock();

            return retVal;
        }

    }
} // core::wrapper

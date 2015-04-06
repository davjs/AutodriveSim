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

#ifndef OPENDAVINCI_CORE_WRAPPER_STRINGPIPELINE_H_
#define OPENDAVINCI_CORE_WRAPPER_STRINGPIPELINE_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/wrapper/Condition.h"
#include "core/wrapper/Mutex.h"
#include "core/wrapper/Runnable.h"
#include "core/wrapper/StringObserver.h"
#include "core/wrapper/StringListener.h"
#include "core/wrapper/Thread.h"

namespace core {
    namespace wrapper {

        using namespace std;

        /**
         * This class distributes strings using an asynchronous pipeline.
         */
        class StringPipeline : public Runnable, public StringObserver, public StringListener {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                StringPipeline(const StringPipeline &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                StringPipeline& operator=(const StringPipeline &);

            public:
                StringPipeline();

                virtual ~StringPipeline();

                virtual void setStringListener(StringListener *sl);

                virtual void nextString(const string &s);

                /**
                 * This method starts the string pipeline.
                 */
                void start();

                /**
                 * This method stops the string pipeline.
                 */
                void stop();

            private:
                Condition *m_queueCondition;
                Mutex *m_queueMutex;
                queue<string> m_queue;

                Mutex *m_stringListenerMutex;
                StringListener *m_stringListener;

                Thread *m_thread;

                Mutex *m_threadStateMutex;
                bool m_threadState;

                /**
                 * This method changes the thread's state.
                 *
                 * @param state True iff the StringPipeline's thread is running.
                 */
                void setRunning(const bool &state);

                virtual void run();

                virtual bool isRunning();
        };

    }
} // core::wrapper

#endif /*OPENDAVINCI_CORE_WRAPPER_STRINGPIPELINE_H_*/

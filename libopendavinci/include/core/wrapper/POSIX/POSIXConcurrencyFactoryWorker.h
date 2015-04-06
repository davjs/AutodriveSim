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

#ifndef OPENDAVINCI_CORE_WRAPPER_POSIX_POSIXCONCURRENCYFACTORYWORKER_H_
#define OPENDAVINCI_CORE_WRAPPER_POSIX_POSIXCONCURRENCYFACTORYWORKER_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/wrapper/SystemLibraryProducts.h"
#include "core/wrapper/ConcurrencyFactoryWorker.h"

#include "core/wrapper/POSIX/POSIXThread.h"

namespace core {
    namespace wrapper {

        template <> class OPENDAVINCI_API ConcurrencyFactoryWorker<SystemLibraryPosix>
        {
            public:
                static Thread* createThread(Runnable &runnable)
                {
                    return new core::wrapper::POSIX::POSIXThread(runnable);
                };

                static void usleep(const long &microseconds)
                {
                    struct timespec delay;

                    delay.tv_sec = 0;
                    delay.tv_nsec = 0;

                    const long NANOSECONDS_PER_SECOND = 1000 * 1000 * 1000;
                    long nanoseconds = microseconds * 1000;
                    while (nanoseconds >= NANOSECONDS_PER_SECOND) {
                        nanoseconds -= NANOSECONDS_PER_SECOND;
                        delay.tv_sec++;
                    }
                    // Add remaining nanoseconds.
                    delay.tv_nsec += nanoseconds;

                    nanosleep(&delay, NULL);
                };
        };
    }
} // core::wrapper::POSIX

#endif /*OPENDAVINCI_CORE_WRAPPER_POSIX_POSIXCONCURRENCYFACTORY_H_*/

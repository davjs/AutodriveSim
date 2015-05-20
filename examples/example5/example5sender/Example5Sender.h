/**
 * OpenDaVINCI - Portable middleware for distributed components.
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

#ifndef EXAMPLE5SENDER_H_
#define EXAMPLE5SENDER_H_

#include "core/base/ConferenceClientModule.h"
#include "core/base/FIFOQueue.h"

namespace examples {

    using namespace std;

    /**
     * This class demonstrates how to send data as a Container.
     */
    class Example5Sender : public core::base::ConferenceClientModule, public core::wrapper::StringListener, public core::wrapper::ConnectionListener {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Example5Sender(const Example5Sender &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Example5Sender& operator=(const Example5Sender &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            Example5Sender(const int32_t &argc, char **argv);

            virtual ~Example5Sender();

            core::base::ModuleState::MODULE_EXITCODE body();

            virtual void handleConnectionError();

            virtual void nextString(const string &s);

        private:
            virtual void setUp();

            virtual void tearDown();
    };

} // examples

#endif /*EXAMPLE5SENDER_H_*/

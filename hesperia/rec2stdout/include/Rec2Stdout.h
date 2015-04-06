/**
 * rec2stdout - Dump the content of a .rec file to console (part of simulation environment)
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

#ifndef REC2STDOUT_H_
#define REC2STDOUT_H_

#include "core/base/ConferenceClientModule.h"

namespace rec2stdout {

    using namespace std;

    /**
     * This class converts a given previously recorded data file
     * to a video.
     */
    class Rec2Stdout : public core::base::ConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Rec2Stdout(const Rec2Stdout &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Rec2Stdout& operator=(const Rec2Stdout &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            Rec2Stdout(const int32_t &argc, char **argv);

            virtual ~Rec2Stdout();

            virtual void setUp();

            virtual void tearDown();

            core::base::ModuleState::MODULE_EXITCODE body();
    };

} // rec2stdout

#endif /*REC2STDOUT_H_*/

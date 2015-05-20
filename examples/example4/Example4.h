/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifndef EXAMPLE4_H_
#define EXAMPLE4_H_

#include <opencv/highgui.h>

#include "core/base/ConferenceClientModule.h"

namespace linearkalmanfilter {

    using namespace std;

    class LinearKalmanFilter : public core::base::ConferenceClientModule {
        private:
            enum {
                HEIGHT = 500,
                WIDTH = 500
            };

        public:
            LinearKalmanFilter(const int32_t &argc, char **argv);

            core::base::ModuleState::MODULE_EXITCODE body();

        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            LinearKalmanFilter(const LinearKalmanFilter &/*obj*/) :
                    core::base::ConferenceClientModule(0, NULL, "LinearKalmanFilter") {};

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            LinearKalmanFilter& operator=(const LinearKalmanFilter &/*obj*/) {
                return (*this);
            };

            void setUp();
            void tearDown();

            /**
             * This method draws a cross around the given point.
             *
             * @param img Image on which the cross has to be drawn.
             * @param point Point to be drawn.
             * @param d Distance from the center of the cross to the corner.
             * @param r R part of the color.
             * @param g G part of the color.
             * @param b B part of the color.
             */
            void drawCross(IplImage *img, const CvPoint &point, const double d, const uint32_t r, const uint32_t g, const uint32_t b);
    };
}

#endif /*EXAMPLE4_H_*/

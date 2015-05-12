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

#ifndef PARKING_H_
#define PARKING_H_

#include "core/base/ConferenceClientModule.h"
#include "core/data/environment/VehicleData.h"
#include "core/data/control/VehicleControl.h"
#include "GeneratedHeaders_Data.h"


namespace msv {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
   	using namespace core::data::control;
   	using namespace core::data::environment;

    class Parking : public core::base::ConferenceClientModule {
        private:

            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Parking(const Parking &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Parking& operator=(const Parking &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            Parking(const int32_t &argc, char **argv);

            virtual ~Parking();

            core::base::ModuleState::MODULE_EXITCODE body();

        private:
            virtual void setUp();

            virtual void tearDown();

            /* --------------------------- Aurélien ------------------------------ */

            VehicleControl vc;

            // sensor values
            float irFrontRight;
            float irRear;
            float irRearRight;
            float usFront;
            float usFrontRight;
            float usRearRight;

            // car values
            float traveledPath;
            float heading;

            // measuring the parking spot
            float gapStart;
            float gapLength;

            // the state of the car
			enum State {DETECT_GAP, PARKING, DONE};
			State currentState;

			// the different parking procedures
			enum Procedure {NO_PROCEDURE, PARALLEL_STANDARD, PARALLEL_WIDE, PERPENDICULAR_STANDARD};
            Procedure parkingProcedure;
            
			// maneuvers
            enum Maneuver { NO_MANEUVER, FORWARDS, BACKWARDS, FORWARD_RIGHT, BACKWARDS_RIGHT, FORWARD_LEFT, BACKWARDS_LEFT };
            Maneuver currentManeuver;
            float drivingSpeed;
            float turningSpeed;
            float headingStart; // the direction of the car at the start of the turn
            bool turning;
            bool emergencyStop;
            
            void SetSpeed(float speed);

            bool TryStop();
            bool TryMove(float distance);
            bool TryTurn(float desiredAngle);
            bool EmergencyStop(bool back);
        
            float GetGapLength();
            
			Procedure GetParkingProcedure(float gapLength);
            
			State ParallelStandard();
			State ParallelWide();
			State PerpendicularStandard();

			/* --------------------------------------------------------------------- */
    };

} // msv
#endif /*PARKING_H_*/

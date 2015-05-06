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

 /* Aurélien Hontabat -- parking funcionality */

#include <stdio.h>
#include <math.h>

#include "core/io/ContainerConference.h"
#include "core/data/Container.h"
#include "core/data/Constants.h"
#include "core/data/control/VehicleControl.h"
#include "core/data/environment/VehicleData.h"

#include "GeneratedHeaders_Data.h"

#include "Parking.h"

namespace msv {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
   	using namespace core::data::control;
   	using namespace core::data::environment;

    Parking::Parking(const int32_t &argc, char **argv) :
    ConferenceClientModule(argc, argv, "Parking")
    {}

    Parking::~Parking() {}
    
    /* --------------------------- Aurélien ------------------------------ */

    void Parking::setUp() {
        
        // state at launch
        currentState = DETECT_GAP;
        
        // current parking procedure
        parkingProcedure = NO_PROCEDURE;
        
        // current parking maneuver
        currentManeuver = NO_MANEUVER;

		// speeds and angles
		drivingSpeed = 2;
		turningSpeed = 0.8;
        
        // TODO: combine with the edge following
        vc.setSpeed(drivingSpeed);
        vc.setSteeringWheelAngle(0);
    }

    void Parking::tearDown() {}
    
    /* -------------------------- helper functions ----------------------- */
    
    // measure the length of a gap
    // TODO: make it work no matter if it starts next to an obstacle or not
    float Parking::GetGapLength(){
        if(irFrontRight < 0){
			gapLength = traveledPath - gapStart;
		}else{
			gapStart = traveledPath;
		}
        return gapLength;
    }

    // defines the procedure to engage depending on the size of a  gap
	Parking::Procedure Parking::GetParkingProcedure(float length) {

        // return the appropriate parking procedure
		if (usFrontRight < 0) {		
			return PARALLEL_WIDE;
		} else {
			if (length > 6 && irRearRight > 0) {		
				return PARALLEL_STANDARD;
			} else if (length > 3 && length < 6 && irRearRight > 0) {
				return PERPENDICULAR_STANDARD;
			} else {
				return NO_PROCEDURE;
			}
		}
	}
	
	/* -------------------------- maneuvers ----------------------- */

	// stops the car - returns true if the car stoped
	bool Parking::TryStop(){
		vc.setSpeed(0);
		vc.setSteeringWheelAngle(0);
		if(vc.getSpeed() < 0.1){
			return true;
		}else{
			return false;		
		}
	}

	// moves the car a specified distance
	bool Parking::TryMove(float distance){

		vc.setSteeringWheelAngle(0);

		if(!turning){								// TODO: rename variables!!
			gapStart = traveledPath;
			turning = true;
		}
		if((traveledPath - gapStart) > distance){
			turning = false;
			return true;
		}else{
			return false;
		}
	}
	
	void Parking::SetSpeed(float speed){
		vc.setSpeed(speed);
	}

	// turns the car X° in a specified direction - returns true if the car is done turning
	bool Parking::TryTurn(float desiredAngle){
            
        float currentAngle = 0;
   
        // initialize starting point
        if(!turning){
            headingStart = heading;
            turning = true;
        }
        
        // get the current angle from where the car was, to where it is now
        currentAngle = fmod((headingStart - heading),360);
        if(currentAngle > 180) currentAngle = 360 - currentAngle;
        
        cerr << "angle: " << currentAngle << endl;
        
        // set the steering wheel angle to the direction we want to turn
		if(desiredAngle > 0){
			vc.setSteeringWheelAngle(30 * Constants::DEG2RAD);
		}else{
			vc.setSteeringWheelAngle(-30 * Constants::DEG2RAD);
		}

        if(fabs(currentAngle) > fabs(desiredAngle)) {
            turning = false;
	        return true;
        }else{
            return false;
        }
	}

	// stops the car if it gets too close to something 
	bool Parking::EmergencyStop(bool back){
		if(irRear > -1 && irRear < 2.5 && back){
            emergencyStop = true;
			return TryStop();
		}else if(((usFront > -1 && usFront < 2) || (usFrontRight > -1 && usFrontRight <2)) && !back){
            return TryStop();
        }else{
			return false;
		}	
	}
    
    // the parallel parking maneuver
	Parking::State Parking::ParallelStandard(){

		switch(currentManeuver){
			case NO_MANEUVER:
				cout << "parallel standard" << endl;
                if(TryStop()){
                    currentManeuver = BACKWARDS_RIGHT;
                }
				return PARKING;

			case BACKWARDS_RIGHT:
				cout << "turn right" << endl;
				SetSpeed(turningSpeed * -1);
                
                if(EmergencyStop(1)){ // obstacle in the back
                    currentManeuver = FORWARD_RIGHT;
                }
                
                if(TryTurn(60)){
                    currentManeuver = BACKWARDS_LEFT;
                }
		        return PARKING;

			case BACKWARDS_LEFT:
				cout << "turn left" << endl;
				SetSpeed(turningSpeed * -1);
                
                if(EmergencyStop(1)){ // obstacle in the back
                    currentManeuver = FORWARD_RIGHT;
                }
                
				if(TryTurn(-60)){
					TryStop();
                    return DONE;
                }else{
                    return PARKING;
                }
                
            case FORWARD_RIGHT:
                cout << "forward right" << endl;
                SetSpeed(turningSpeed);
                
                if(EmergencyStop(0)){
                    currentManeuver = BACKWARDS_LEFT;
                }
                
                if(TryTurn(60)){
                	TryStop();
                    return DONE;
                }else{
                    return PARKING;
                }
                
			default:
				return PARKING;
		}
	}

	// the parallel parking maneuver on wide spot
	Parking::State Parking::ParallelWide(){

		switch(currentManeuver){
			case NO_MANEUVER:
				cout << "parallel wide" << endl;
                if(TryStop()){
                    currentManeuver = FORWARD_RIGHT;
                }
				return PARKING;

            case FORWARD_RIGHT:
                cout << "forward right" << endl;
                SetSpeed(turningSpeed);

                if(TryTurn(60)){
                	currentManeuver = FORWARD_LEFT;
                }
                return PARKING;

            case FORWARD_LEFT:
                 cout << "forward left" << endl;
                 SetSpeed(turningSpeed);

                 if(TryTurn(-60)){
                	 if(TryStop()){
                		 return DONE;
                	 }else{
                		 return PARKING;
                	 }
                 }else{
                	 return PARKING;
                 }

			default:
				return PARKING;
		}
	}

	// perpendicular parking maneuver
	Parking::State Parking::PerpendicularStandard(){
		switch(currentManeuver){
			case NO_MANEUVER:
				cout << "perpendicular standard" << endl;
                if(TryStop()){
                    currentManeuver = BACKWARDS_RIGHT;
                }
				return PARKING;

			case BACKWARDS_RIGHT:
				cout << "backwards right" << endl;
				SetSpeed(turningSpeed * -1);

				if (TryTurn(90)) {
					if(TryStop()){
						return DONE;
					} else {
						return PARKING;
					}
				}
				return PARKING;

            case BACKWARDS:
                cout << "backwards" << endl;

                if(TryMove(1)){

                }
                return PARKING;

			default:
				return PARKING;
		}
	}

	// ----------------------------------------

    ModuleState::MODULE_EXITCODE Parking::body() {

        while(getModuleState() == ModuleState::RUNNING){

        	/* ----------------------------------- Data ---------------------------- */

            // Vehicle data
            Container containerVehicleData = getKeyValueDataStore().get(Container::VEHICLEDATA);
            VehicleData vd = containerVehicleData.getData<VehicleData> ();

            // Sensor board data
            Container containerSensorBoardData = getKeyValueDataStore().get(Container::USER_DATA_0);
            SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();

            // Assigning the values of the sensors
            irFrontRight = sbd.getMapOfDistances()[0];
            irRear = sbd.getMapOfDistances()[1];
            irRearRight = sbd.getMapOfDistances()[2];
            usFront = sbd.getMapOfDistances()[3];
            usFrontRight = sbd.getMapOfDistances()[4];
            usRearRight = sbd.getMapOfDistances()[5];

            // Assigning the values of the vehicle
            traveledPath = vd.getAbsTraveledPath();
            heading = vd.getHeading() * Constants::RAD2DEG;

            /* ---------------------------------------------------------------------- */
            
            /* -------------------------- state switch ------------------------------ */
            
            switch(currentState){
                
                case DETECT_GAP:                                                // if the car is supposed to park
                    cout << "MOVE_FORWARD" << endl;
                    parkingProcedure = GetParkingProcedure(GetGapLength());     // save a procedure depending on the size of a gap
                    
                    // exit state
                    if(parkingProcedure != NO_PROCEDURE){                        // if we found a suitable parking spot
                        currentState = PARKING;   
                    }
                    break;
                    
                case PARKING:
                    cout << "PARKING" << endl;
                    
                    switch (parkingProcedure) {			                        // switch to the appropriate parking procedure
			            
                        case PARALLEL_STANDARD:
                        	currentState = DETECT_GAP;							// toggle comment to test this parking procedure
            				// currentState = ParallelStandard();
            				break;
                            
            			case PARALLEL_WIDE:
            				currentState = DETECT_GAP;
            				//currentState = ParallelWide();
            				cout << "parallel wide" << endl;
            				break;
                            
            			case PERPENDICULAR_STANDARD:
            				currentState = PerpendicularStandard();
            				cout << "perpendicular" << endl;
            				break;
                            
            			default:
            				break;
		            }
                    break;
                    
                case DONE:
                    cout << "DONE" << endl;
                    break;
            }

            /* ---------------------------------------------------------------------- */

            /* ----------------------------------- Debug ---------------------------- */
            // sensor data
            cerr << "Distance front right infrared '" << irFrontRight << "'" << endl;
            cerr << "Distance rear infrared '" << irRear << "'" << endl;
            cerr << "Distance front ultrasonic '" << usFront << "'" << endl;
            cerr << "Distance front right ultrasonic '" << usFrontRight << "'" << endl;
            cerr << "Gap length '" << gapLength << "'" << endl;
            
            // vehicle data
            cerr << "Heading '" << heading << "'" << endl;
            cerr << "Heading Start '" << headingStart << "'" << endl;
            /* ---------------------------------------------------------------------- */

            // Create container for finally sending the data
            Container c(Container::VEHICLECONTROL, vc);

            // Send container
            getConference().send(c);

        }
        return ModuleState::OKAY;
    }
} //msv

/**
 * driver - Sample application for calculating steering and acceleration commands.
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

#include <stdio.h>
#include <math.h>

#include "core/io/ContainerConference.h"
#include "core/data/Container.h"
#include "core/data/Constants.h"
#include "core/data/control/VehicleControl.h"
#include "core/data/environment/VehicleData.h"

#include "GeneratedHeaders_Data.h"

#include "Driver.h"

namespace msv {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace core::data::control;
    using namespace core::data::environment;

    Driver::Driver(const int32_t &argc, char **argv) :
            ConferenceClientModule(argc, argv, "Driver") {
    }

    Driver::~Driver() {}

    void Driver::setUp() {

        // This method will be call automatically _before_ running body().
    }void Driver::tearDown() {

        // This method will be call automatically _after_ return from body().
    }

    // This method will do the main data processing job.
    ModuleState::MODULE_EXITCODE Driver::body() {
        bool lane_Detection_Mode = true;
        bool obstacle_Detection_Mode = false;
        bool overtaking_Mode = false;
        bool left_Lane = false;
        bool right_Lane = false;
        int angle;
        double steerAngle = 0;
        double frontCenter;
        double infrared_Rear;
        double infrared_front;
        double front_Right_Sonic;

        while (getModuleState() == ModuleState::RUNNING) {
            // In the following, you find example for the various data sources that are available:

            // 1. Get most recent vehicle data:
            Container containerVehicleData = getKeyValueDataStore().get(Container::VEHICLEDATA);
            VehicleData vd = containerVehicleData.getData<VehicleData> ();
            cerr << "Most recent vehicle data: '" << vd.toString() << "'" << endl;

            // 2. Get most recent sensor board data:
            Container containerSensorBoardData = getKeyValueDataStore().get(Container::USER_DATA_0);
            SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();
            cerr << "Most recent sensor board data: '" << sbd.toString() << "'" << endl;

            // 3. Get most recent user button data:
            Container containerUserButtonData = getKeyValueDataStore().get(Container::USER_BUTTON);
            UserButtonData ubd = containerUserButtonData.getData<UserButtonData> ();
            cerr << "Most recent user button data: '" << ubd.toString() << "'" << endl;

            // 4. Get most recent steering data as fill from lanedetector for example:
            Container containerSteeringData = getKeyValueDataStore().get(Container::USER_DATA_1);
            SteeringData sd = containerSteeringData.getData<SteeringData> ();
            cerr << "Most recent steering data: '" << sd.toString() << "'" << endl;

            // Design your control algorithm here depending on the input data from above.


            // Create vehicle control data.
            VehicleControl vc;

            // With setSpeed you can set a desired speed for the vehicle in the range of -2.0 (backwards) .. 0 (stop) .. +2.0 (forwards)
            vc.setSpeed(0.8);
            angle = sd.getExampleData();
            front_Right_Sonic = sbd.getValueForKey_MapOfDistances(4);
            infrared_front = sbd.getValueForKey_MapOfDistances(0);
            infrared_Rear = sbd.getValueForKey_MapOfDistances(2);
            frontCenter = sbd.getValueForKey_MapOfDistances(3);
            /*Overtaking in right MOde) */
            if(lane_Detection_Mode){
                if(angle <100){
                    steerAngle = angle;
                }
                if(angle >=102){
                    vc.setSpeed(0.5);
                }
            }
            if(!left_Lane  && !lane_Detection_Mode && !right_Lane && !obstacle_Detection_Mode && !right_Lane){
                vc.setSpeed(-1.0);
                vc.setAcceleration(0.0);
                lane_Detection_Mode = false;
                overtaking_Mode = false;
            }
            if(!obstacle_Detection_Mode && (frontCenter > 0.0 && frontCenter <7.2))  {
                FILE* pFile2 = std::fopen("log1.txt", "a");
                vc.setSpeed(0.5);
                steerAngle = -25;
                obstacle_Detection_Mode = true;
                overtaking_Mode = true;
                lane_Detection_Mode = false;
                cout << "O V E R T A K I N G    S T A R T S..."  <<endl;
                fprintf(pFile2, "frontCenter: %f\n", frontCenter);
                fprintf(pFile2, "steerAngle: %f\n", steerAngle);
                fflush(pFile2);
                fclose(pFile2);
            }

            if(overtaking_Mode && (infrared_front >= 0.0 && infrared_front < 2.9)){
                FILE* pFile3 = std::fopen("log2.txt", "a");
                vc.setSpeed(0.5);
                steerAngle = 23;
                left_Lane = true;
                overtaking_Mode = false;
                cout << "T U R N    R I G H T...L E A V E   O V E R T A K I N G"  <<endl;
                fprintf(pFile3, "infrared_front: %f\n", infrared_front);
                fprintf(pFile3, "steerAngle: %f\n", steerAngle);
                fflush(pFile3);
                fclose(pFile3);
            }

            if(left_Lane && (infrared_Rear > 0.0 && infrared_Rear < 2.9)){
                FILE* pFile4 = std::fopen("log3.txt", "a");
                steerAngle = 0;
                right_Lane = true;
                left_Lane = false;
                fprintf(pFile4, "infrared_Rear: %f\n", infrared_Rear);
                fflush(pFile4);
                fclose(pFile4);
            }

            if(right_Lane && infrared_front < 0.0 && infrared_Rear >=0.0){
                FILE* pFile5 = std::fopen("log4.txt", "a");
                steerAngle = 23;
                fprintf(pFile5, "infrared_front: %f\n", infrared_front);
                fprintf(pFile5, "steerAngle: %f\n", steerAngle);
                fprintf(pFile5, "infrared_Rear: %f\n", infrared_Rear);
                fflush(pFile5);
                fclose(pFile5);
            }

            if(right_Lane && infrared_front < 0.0 && infrared_Rear <= 0.0){
                FILE* pFile6 = std::fopen("log5.txt", "a");
                steerAngle = 25;
                lane_Detection_Mode = true;
                right_Lane = false;
                obstacle_Detection_Mode = false;
                fprintf(pFile6, "infrared_Rear: %f\n", infrared_Rear);
                fprintf(pFile6, "steerAngle: %f\n", steerAngle);
                fprintf(pFile6, "infrared_front: %f\n", infrared_front);
                fflush(pFile6);
                fclose(pFile6);
            }

            //car on, car does whatever it is supposed to.
            // You can also turn on or off various lights:
            vc.setBrakeLights(false);
            vc.setLeftFlashingLights(false);
            vc.setRightFlashingLights(false);
            vc.setSteeringWheelAngle(steerAngle* Constants::DEG2RAD);
            // Create container for finally sending the data.
            Container c(Container::VEHICLECONTROL, vc);
            // Send container.
            getConference().send(c);
        }

        return ModuleState::OKAY;
    }
} // msv
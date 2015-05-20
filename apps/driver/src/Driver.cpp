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
#include "core/data/control/LaneConfig.h"

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

    Driver::~Driver() { }

    void Driver::setUp() {
        // This method will be call automatically _before_ running body().
    }

    void Driver::tearDown() {
        // This method will be call automatically _after_ return from body().
    }

    // This method will do the main data processing job.
    ModuleState::MODULE_EXITCODE Driver::body() {


        int angle; // in degrees
//        double front_Right_Sonic;
//        double front_Center_Sonic;
        double infraRightRear;
        double infraRightFront;
//        double infra_Rear;
        bool right_clear = false;
        bool overtake = false;
        double steerAngle = 0;
        bool is_Right_Lane = true;
        const int min_Distance = 10;
//        const int max_Right_Angle = 25;
        const int max_Left_Angle = -25;
        const int min_RightSpace = 10;
        int distance_To_Obstacle = 0;
        string mode = " ";
        LaneConfig lc;
        lc.setCmd(is_Right_Lane);


        while (getModuleState() == ModuleState::RUNNING) {
            // In the following, you find example for the various data sources that are available:
            // 1. Get most recent vehicle data:
            Container containerVehicleData = getKeyValueDataStore().get(Container::VEHICLEDATA);
            VehicleData vd = containerVehicleData.getData<VehicleData>();
            cerr << "Most recent vehicle data: '" << vd.toString() << "'" << endl;
            // 2. Get most recent sensor board data:
            Container containerSensorBoardData = getKeyValueDataStore().get(Container::USER_DATA_0);
            SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData>();
            cerr << "Most recent sensor board data: '" << sbd.toString() << "'" << endl;
            // 3. Get most recent user button data:
            Container containerUserButtonData = getKeyValueDataStore().get(Container::USER_BUTTON);
            UserButtonData ubd = containerUserButtonData.getData<UserButtonData>();
            cerr << "Most recent user button data: '" << ubd.toString() << "'" << endl;
            // 4. Get most recent steering data as fill from lanedetector for example:
            Container containerSteeringData = getKeyValueDataStore().get(Container::USER_DATA_1);
            SteeringData sd = containerSteeringData.getData<SteeringData>();
            cerr << "Most recent steering data: '" << sd.toString() << "'" << endl;

            cerr << "Current state '" << mode << "'" << endl;
            // Design your control algorithm here depending on the input data from above.
            // Create vehicle control data.
            VehicleControl vc;
            TimeStamp ts;

            // With setSpeed you can set a desired speed for the vehicle in the range of -2.0 (backwards) .. 0 (stop) .. +2.0 (forwards)
            vc.setSpeed(2);

            //update data
            angle = sd.getExampleData(); // in degrees
//            front_Right_Sonic = sbd.getValueForKey_MapOfDistances(4);
//            infra_Rear = sbd.getValueForKey_MapOfDistances(1);
//            front_Center_Sonic = sbd.getValueForKey_MapOfDistances(3);
            infraRightRear = sbd.getValueForKey_MapOfDistances(2);
            infraRightFront = sbd.getValueForKey_MapOfDistances(0);
            if (infraRightRear > min_RightSpace && infraRightFront > min_RightSpace) {
                right_clear = true;
            }


            // state machine
            if (is_Right_Lane) {

                if (distance_To_Obstacle > min_Distance) { // normal mode
                    cerr << " L A N E  F O L L O W I N G" << endl;
                    steerAngle = angle;
                }

                else {  // overtake
                    //vc.setSpeed(1);
                    steerAngle = max_Left_Angle;
                    lc.setCmd(false);
                    overtake = true;
                    right_clear = false;
                    is_Right_Lane = false;

                }
            }
            else {   // during overtaking
                if (right_clear && overtake) {//turn back
                    steerAngle = max_Left_Angle;
                    lc.setCmd(true);
                    overtake = true;
                }


            }

            // You can also turn on or off various lights:
            vc.setBrakeLights(false);
            vc.setLeftFlashingLights(false);
            vc.setRightFlashingLights(false);


            vc.setSteeringWheelAngle(steerAngle * Constants::DEG2RAD);
            // Create container for finally sending the data.
            Container c(Container::VEHICLECONTROL, vc);
            // Send container.
            getConference().send(c);

            LaneConfig lc;
            //lc.toString();
            // LaneConfig lc;
            lc.setCmd(false);
//            // Create container for finally sending the data.
            Container cmd(Container::USER_DATA_9, lc);
//            // Send container.
            getConference().send(cmd);


        }
        return
        ModuleState::OKAY;
    }
} // msv

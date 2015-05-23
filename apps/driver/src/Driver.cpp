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
#include <unistd.h>
#include <cmath>

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
        double steerAngle = 0;

        double overtaking = -1;
        int obstacleMet = 0;
        double finaliseOvertaking = -1;
        double calibrateToLane = -1;

        int objectDistance = 10;
        double laneSwitchingOffset = 6;
        int optimisedAngle = 22;
        
        while (getModuleState() == ModuleState::RUNNING) {
            Container containerVehicleData = getKeyValueDataStore().get(Container::VEHICLEDATA);
            VehicleData vd = containerVehicleData.getData<VehicleData>();

            Container containerSensorBoardData = getKeyValueDataStore().get(Container::USER_DATA_0);
            SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData>();

            Container containerSteeringData = getKeyValueDataStore().get(Container::USER_DATA_1);
            SteeringData sd = containerSteeringData.getData<SteeringData>();

            VehicleControl vc;
            LaneConfig lc;

            double irFrontRight = sbd.getValueForKey_MapOfDistances(0);
            double irRearRight = sbd.getValueForKey_MapOfDistances(2);
            double usFrontCenter = sbd.getValueForKey_MapOfDistances(3);
            double usFrontRight = sbd.getValueForKey_MapOfDistances(4);


            steerAngle = sd.getExampleData();

            vc.setSpeed(2);

            if (usFrontCenter > 0 && usFrontCenter < objectDistance && calibrateToLane <= 0) {
                if (overtaking < 0) overtaking = vd.getAbsTraveledPath();
            }

            if (overtaking > 0) {
                if ((vd.getAbsTraveledPath() - overtaking) < laneSwitchingOffset) {
                    steerAngle = optimisedAngle * -1;
                } else {
                    lc.setCmd(false);
                }

                if (irRearRight > 0 && ! obstacleMet) obstacleMet = 1;

                if (obstacleMet) {
                    if (irFrontRight < 0 && ! (usFrontRight > 0 && usFrontRight < objectDistance)) {
                        overtaking = -1;
                        obstacleMet = 0;

                        if (finaliseOvertaking < 0) finaliseOvertaking = vd.getAbsTraveledPath();
                    }
                }
            }

            if (finaliseOvertaking > 0) {
                if ((vd.getAbsTraveledPath() - finaliseOvertaking) < laneSwitchingOffset) {
                    steerAngle = optimisedAngle;
                } else {
                    if (calibrateToLane <= 0) calibrateToLane =  vd.getAbsTraveledPath();

                    if ((vd.getAbsTraveledPath() - calibrateToLane) < laneSwitchingOffset) {
                        steerAngle = optimisedAngle * -1;
                    } else {
                        lc.setCmd(true);
                        finaliseOvertaking = -1;
                        calibrateToLane = -1;
                    }
                }
            }

            cout << "overtaking: " << overtaking << endl;
            cout << "obstacleMet: " << obstacleMet << endl;
            cout << "finaliseOvertaking: " << finaliseOvertaking << endl;
            cout << "calibrateToLane: " << calibrateToLane << endl;

            vc.setSteeringWheelAngle(steerAngle * Constants::DEG2RAD);
            // Create container for finally sending the data.
            Container c(Container::VEHICLECONTROL, vc);
            // Send container.
            getConference().send(c);

            Container cmd(Container::USER_DATA_9, lc);
            getConference().send(cmd);
        }

        return
        ModuleState::OKAY;
    }
} // msv

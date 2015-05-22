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
	int overtaking = 0;
	int obstacleMet = 0;
	int finaliseOvertaking = 0;
	int calibrateToLane = 0;
	//int straightLineThreshold = 50;
	//int straightLineProgress = 0;
	//int isStraightLine = 0;
	//int lastAngle = 0;
	int laneSwitchingOffset = 5;

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
	//double irRightRear = sbd.getValueForKey_MapOfDistances(1);
	double irRearRight = sbd.getValueForKey_MapOfDistances(2);
	double usFrontCenter = sbd.getValueForKey_MapOfDistances(3);
	//double usFrontRight = sbd.getValueForKey_MapOfDistances(4);
	//double usRearRight = sbd.getValueForKey_MapOfDistances(5);

    //update data
    steerAngle = sd.getExampleData(); // in degrees

	// curve detection
        /*
	if (lastAngle <= steerAngle + 1 && lastAngle >= steerAngle - 1) {
		if (straightLineProgress <= straightLineThreshold) straightLineProgress++;
	} else {
		straightLineProgress = 0;
	}

	if (straightLineProgress >= straightLineThreshold) isStraightLine = 1; else isStraightLine = 0;

	cout << ((isStraightLine) ? "straight line" : "curve line") << endl;
	*/
	vc.setSpeed(2);

	if (usFrontCenter > 0 && usFrontCenter < 7) {
		if (! overtaking) overtaking = vd.getAbsTraveledPath();
	}

	if (overtaking) {
	 	if ((vd.getAbsTraveledPath() - overtaking) <= laneSwitchingOffset) {
			steerAngle = -25;
		} else {
			lc.setCmd(false);
		}

		if (irRearRight > 0 && ! obstacleMet) obstacleMet = 1;
		
		if (obstacleMet) {
			if (irFrontRight < 0) {
				overtaking = 0;
				obstacleMet = 0;
			
				if (! finaliseOvertaking) finaliseOvertaking = vd.getAbsTraveledPath();
			}
		}
	}

	if (finaliseOvertaking) {
		if ((vd.getAbsTraveledPath() - finaliseOvertaking) < laneSwitchingOffset) {
			steerAngle = 25;
		} else {
			if (! calibrateToLane) calibrateToLane = vd.getAbsTraveledPath();

			if ((vd.getAbsTraveledPath() - calibrateToLane) < laneSwitchingOffset) {
				steerAngle = -25;
			} else {
				lc.setCmd(true);
				finaliseOvertaking = 0;
				calibrateToLane = 0;
			}
		}
	}

	cout << "overtaking: " << overtaking << endl;
	cout << "obstacleMet: " << obstacleMet << endl;
	cout << "finaliseOvertaking: " << finaliseOvertaking << endl;
	cout << "calibrateToLane: " << calibrateToLane << endl;

//    	lastAngle = steerAngle;


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

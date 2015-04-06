/**
 * vehicle - Vehicle dynamics (part of simulation environment)
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

#include <iostream>

#include "core/macros.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"

#include "hesperia/data/environment/EgoState.h"
#include "core/data/environment/VehicleData.h"
#include "core/data/environment/Point3.h"
#include "core/data/control/ForceControl.h"
#include "core/data/control/VehicleControl.h"

#include "Vehicle.h"
#include "LinearBicycleModel.h"
#include "LinearBicycleModelNew.h"

namespace vehicle {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace core::data::control;
    using namespace hesperia::data::environment;
    using namespace core::data::environment;

    Vehicle::Vehicle(const int32_t &argc, char **argv) :
        ConferenceClientModule(argc, argv, "Vehicle") {}

    Vehicle::~Vehicle() {}

    void Vehicle::setUp() {}

    void Vehicle::tearDown() {}

    ModuleState::MODULE_EXITCODE Vehicle::body() {
        string model = getKeyValueConfiguration().getValue<string>("Vehicle.model");

        if (model == "LinearBicycleModelNew") {
            cerr << "Using LinearBicycleModelNew" << endl;

            bool withSpeedController = (getKeyValueConfiguration().getValue<int32_t>("Vehicle.LinearBicycleModelNew.withSpeedController") == 1);

            return runLinearBicycleModelNew(withSpeedController);
        }

        cerr << "Using LinearBicycleModel" << endl;
        return runLinearBicycleModel();
    }

    ModuleState::MODULE_EXITCODE Vehicle::runLinearBicycleModelNew(const bool &withSpeedController) {
        LinearBicycleModelNew lbmn(getKeyValueConfiguration(), withSpeedController);

        KeyValueDataStore &kvs = getKeyValueDataStore();

        while (getModuleState() == ModuleState::RUNNING) {
            // Get current ForceControl.
            Container c = kvs.get(Container::VEHICLECONTROL);
            VehicleControl vc = c.getData<VehicleControl>();
            cerr << "VehicleControl: '" << vc.toString() << "'" << endl;

            if (withSpeedController) {
            	lbmn.speed(vc.getSpeed());
            }
            else {
            	lbmn.accelerate(vc.getAcceleration());
            }
        	lbmn.steer(vc.getSteeringWheelAngle());

            if (vc.getBrakeLights()) {
                cout << "Turn ON brake lights." << endl;
            }

            if (vc.getLeftFlashingLights()) {
                cout << "Turn ON left flashing lights." << endl;
            }

            if (vc.getRightFlashingLights()) {
                cout << "Turn ON right flashing lights." << endl;
            }
           
            EgoState es = lbmn.computeEgoState();
            
            // Get vehicle data.
            VehicleData vd = lbmn.getVehicleData();
            cerr << "VehicleData: '" << vd.toString() << "'" << endl;

            Container container(Container::EGOSTATE, es);
            getConference().send(container);

            // Send vehicledata.
            Container c2(Container::VEHICLEDATA, vd);
            getConference().send(c2);
        }
        return ModuleState::OKAY;
    }

    ModuleState::MODULE_EXITCODE Vehicle::runLinearBicycleModel() {
        LinearBicycleModel lbm(getKeyValueConfiguration());

        KeyValueDataStore &kvs = getKeyValueDataStore();

        while (getModuleState() == ModuleState::RUNNING) {
            // Get current ForceControl.
            Container c = kvs.get(Container::FORCECONTROL);
            ForceControl fc = c.getData<ForceControl>();
            cerr << "ForceControl: '" << fc.toString() << "'" << endl;

        	lbm.accelerate(fc.getAccelerationForce());
        	lbm.brake(fc.getBrakeForce());
        	lbm.steer(fc.getSteeringForce());

            if (fc.getBrakeLights()) {
                cout << "Turn ON brake lights." << endl;
            }
            else {
            }

            if (fc.getLeftFlashingLights()) {
                cout << "Turn ON left flashing lights." << endl;
            }
            else {
            }

            if (fc.getRightFlashingLights()) {
                cout << "Turn ON right flashing lights." << endl;
            }
            else {
            }
           
            EgoState es = lbm.computeEgoState();
            
            // Get vehicle data.
            VehicleData vd = lbm.getVehicleData();
            cerr << "VehicleData: '" << vd.toString() << "'" << endl;

            Container container(Container::EGOSTATE, es);
            getConference().send(container);

            // Send vehicledata.
            Container c2(Container::VEHICLEDATA, vd);
            getConference().send(c2);
        }
        return ModuleState::OKAY;
    }

} // vehicle

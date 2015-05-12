/**
 * overtaking
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
    }

    void Driver::tearDown() {
            // This method will be call automatically _after_ return from body().
    }

    ModuleState::MODULE_EXITCODE Driver::body() {
            while (getModuleState() == ModuleState::RUNNING) {
                    VehicleControl vc;
                    Container containerSensorBoardData = getKeyValueDataStore().get(Container::USER_DATA_0);
                    SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();
                    double ultraSonicFrontCenter = sbd.getValueForKey_MapOfDistances(3);
                    double ultraSonicFrontRight = sbd.getValueForKey_MapOfDistances(4);
                    double ultraSonicRearRight = sbd.getValueForKey_MapOfDistances(5);
                    double desiredSteeringWheelAngle = 0;

                    if (ultraSonicFrontCenter > 0 && ultraSonicFrontCenter < 14) {
                            desiredSteeringWheelAngle = -26;
                    } else if (ultraSonicFrontCenter < 0) {
                            if (ultraSonicFrontRight > 2 && ultraSonicFrontRight < 3) {
                                    desiredSteeringWheelAngle = 26;
                            } else if (ultraSonicRearRight > 2 && ultraSonicRearRight < 3) {
                                    desiredSteeringWheelAngle = 26;
                            }
                    }

                    vc.setSpeed(2);
                    vc.setSteeringWheelAngle(desiredSteeringWheelAngle * Constants::DEG2RAD);
                    Container c(Container::VEHICLECONTROL, vc);
                    getConference().send(c);
            }

            return ModuleState::OKAY;
    }
} // msv
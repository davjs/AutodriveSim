/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_DATA_ENVIRONMENT_VEHICLEDATA_H_
#define OPENDAVINCI_DATA_ENVIRONMENT_VEHICLEDATA_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/SerializableData.h"

#include "core/data/environment/Point3.h"

namespace core {
    namespace data {
        namespace environment {

            using namespace std;

            /**
             * This class contains all relevant data for the own car.
             */
            class OPENDAVINCI_API VehicleData : public core::data::SerializableData {
                public:
                    VehicleData();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    VehicleData(const VehicleData &obj);

                    virtual ~VehicleData();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    VehicleData& operator=(const VehicleData &obj);

                    /**
                     * This method returns the current position (2D, estimated!).
                     *
                     * @return position.
                     */
                    const Point3 getPosition() const;

                    /**
                     * This method sets a position.
                     *
                     * @param p New position.
                     */
                    void setPosition(const Point3 &position);

                    /**
                     * This method returns the heading.
                     *
                     * @return Heading.
                     */
                    double getHeading() const;

                    /**
                     * This method sets the heading.
                     *
                     * @param h Heading.
                     */
                    void setHeading(const double &h);

                    /**
                     * This method returns the traveled path (absolute).
                     *
                     * @return Absolutely driven path.
                     */
                    double getAbsTraveledPath() const;

                    /**
                     * This method sets the traveled path (absolute).
                     *
                     * @param adp Absolutely driven path.
                     */
                    void setAbsTraveledPath(const double &adp);

                    /**
                     * This method returns the traveled path (relative).
                     *
                     * @return Relatively driven path.
                     */
                    double getRelTraveledPath() const;

                    /**
                     * This method sets the traveled path (relative).
                     *
                     * @param rdp Relatively driven path.
                     */
                    void setRelTraveledPath(const double &rdp);

                    /**
                     * This method returns the current velocity.
                     *
                     * @return velocity.
                     */
                    const Point3 getVelocity() const;

                    /**
                     * This method sets a velocity.
                     *
                     * @param velocity New velocity.
                     */
                    void setVelocity(const Point3 &velocity);

                    /**
                     * This method returns the current speed.
                     *
                     * @return speed.
                     */
                    double getSpeed() const;

                    /**
                     * This method sets a speed.
                     *
                     * @param speed New speed.
                     */
                    void setSpeed(const double &speed);
                    /**
                     * This method returns v_log.
                     *
                     * @return v_log.
                     */
                    double getV_log() const;

                    /**
                     * This method sets a v_log.
                     *
                     * @param speed New v_log.
                     */
                    void setV_log(const double &v_log);

                    /**
                     * This method returns v_batt.
                     *
                     * @return v_batt.
                     */
                    double getV_batt() const;

                    /**
                     * This method sets a v_batt.
                     *
                     * @param speed New v_batt.
                     */
                    void setV_batt(const double &v_batt);

                    /**
                     * This method returns the current temp.
                     *
                     * @return temp.
                     */
                    double getTemp() const;

                    /**
                     * This method sets a temp.
                     *
                     * @param temp New temp.
                     */
                    void setTemp(const double &temp);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    Point3 m_position;
                    double m_heading;
                    double m_absTraveledPath;
                    double m_relTraveledPath;
                    Point3 m_velocity;
                    double m_speed;
                    double m_v_log;
                    double m_v_batt;
                    double m_temp;
            };

        }
    }
} // core::data::environment

#endif /*OPENDAVINCI_DATA_ENVIRONMENT_VEHICLEDATA_H_*/

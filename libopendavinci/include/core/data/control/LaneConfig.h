//
// Created by msv on 2015-05-19.
//

#ifndef OPENDAVINCI_LANECONFIG_H
#define OPENDAVINCI_LANECONFIG_H
#include "core/native.h"


#include "core/data/SerializableData.h"

namespace core {
    namespace data {
        namespace control {

            /**
             * This class represents commands to control the car.
             */
            class OPENDAVINCI_API LaneConfig : public core::data::SerializableData {
                public:
                LaneConfig();

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                LaneConfig(const LaneConfig &obj);

                virtual ~LaneConfig();

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                LaneConfig& operator=(const LaneConfig &obj);

                /**
                 * This method returns the speed.
                 *
                 * @return Speed.
                 */
                bool getCmd() const;

                /**
                 * This method sets the speed.
                 *
                 * @param s Speed.
                 */
                void setCmd( bool s);

                /**
                 * This method returns the acceleration.
                 *
                 * @return Acceleration.
                 */


                virtual std::ostream& operator<<(std::ostream &out) const;
                virtual std::istream& operator>>(std::istream &in);

                virtual const std::string toString() const;

                private:
                bool cmd;


            };
        }
    }
} // core::data::control

#endif //OPENDAVINCI_LANECONFIG_H

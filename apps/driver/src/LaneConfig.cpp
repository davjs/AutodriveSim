//
// Created by msv on 2015-05-19.
//
#include <sstream>

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "LaneConfig.h"

namespace core {
    namespace data {
        namespace control {

            using namespace std;

            using namespace core::base;

            LaneConfig::LaneConfig() :
                    SerializableData(),

                    cmd(true)
            {}

            LaneConfig::LaneConfig(const LaneConfig &obj) :
                    SerializableData(obj),

                    cmd(obj.getCmd())
            {}

            LaneConfig::~LaneConfig() {}

            LaneConfig& LaneConfig::operator=(const LaneConfig &obj) {

                setCmd(obj.getCmd());

                return (*this);
            }



            bool LaneConfig::getCmd() const {
                return cmd;
            }

            void LaneConfig::setCmd(const bool &on) {
                cmd = on;
            }

            const string LaneConfig::toString() const {
                stringstream sstr;
                sstr <<  "cmd: " << getCmd();
                return sstr.str();
            }

            ostream& LaneConfig::operator<<(ostream &out) const {
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);



                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'i', 'g', 'h', 't') >::RESULT,
                        cmd);

                return out;
            }

            istream& LaneConfig::operator>>(istream &in) {
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);



                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'i', 'g', 'h', 't') >::RESULT,
                       cmd);

                return in;
            }

        }
    }
} // core::data::control

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

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/data/recorder/RecorderCommand.h"

namespace core {
    namespace data {
        namespace recorder {

            using namespace core::base;

            RecorderCommand::RecorderCommand() :
                    m_command(STOP) {}

            RecorderCommand::RecorderCommand(const RecorderCommand &obj) :
		SerializableData(),
                m_command(obj.getCommand()) {}

            RecorderCommand::~RecorderCommand() {}

            RecorderCommand& RecorderCommand::operator=(const RecorderCommand &obj) {
                setCommand(obj.getCommand());

                return (*this);
            }

            RecorderCommand::COMMAND RecorderCommand::getCommand() const {
                return m_command;
            }

            void RecorderCommand::setCommand(const RecorderCommand::COMMAND &c) {
                m_command = c;
            }

            const string RecorderCommand::toString() const {
                stringstream sstr;
                sstr  << ((m_command == STOP) ? "Not r" : "R") << "ecording.";
                return sstr.str();
            }

            ostream& RecorderCommand::operator<<(ostream &out) const {
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('c', 'o', 'm', 'm', 'a', 'n', 'd') >::RESULT,
                        static_cast<uint32_t>(m_command));

                return out;
            }

            istream& RecorderCommand::operator>>(istream &in) {
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                uint32_t command = 0;
                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('c', 'o', 'm', 'm', 'a', 'n', 'd') >::RESULT,
                       command);
                m_command = static_cast<COMMAND>(command);

                return in;
            }

        }
    }
} // core::data::recorder

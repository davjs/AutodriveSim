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

#ifndef OPENDAVINCI_DMCP_SERVERINFORMATION_H_
#define OPENDAVINCI_DMCP_SERVERINFORMATION_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/base/Serializable.h"

namespace core {
    namespace dmcp {

        using namespace std;

        class OPENDAVINCI_API ServerInformation : public core::base::Serializable {
            public:
                    enum MANAGED_LEVEL {
                        ML_NONE = 0,
                        ML_PULSE,
                        ML_PULSE_SHIFT,
                        ML_PULSE_TIME,
                        ML_PULSE_TIME_ACK,
                        ML_SIMULATION_RT,
                        ML_SIMULATION,
                    };

            public:
                ServerInformation();

                ServerInformation(const string& ip, const uint32_t& port, const MANAGED_LEVEL &managedLevel = ML_NONE);

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                ServerInformation(const ServerInformation &obj);

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                ServerInformation& operator=(const ServerInformation &obj);

                virtual ~ServerInformation();

                const string getIP() const;
                uint32_t getPort() const;
                MANAGED_LEVEL getManagedLevel() const;

                virtual ostream& operator<<(ostream &out) const;
                virtual istream& operator>>(istream &in);
                virtual const string toString() const;

                bool operator==(const ServerInformation& other) const;
            protected:
                string m_serverIP;
                uint32_t m_serverPort;
                MANAGED_LEVEL m_managedLevel;
        };
    }
} // core::dmcp

#endif /*OPENDAVINCI_DMCP_SERVERINFORMATION_H_*/

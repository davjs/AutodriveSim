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

#ifndef OPENDAVINCI_DATA_DMCP_DISCOVERMESSAGE_H_
#define OPENDAVINCI_DATA_DMCP_DISCOVERMESSAGE_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/SerializableData.h"
#include "core/dmcp/ServerInformation.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace std;

            class OPENDAVINCI_API DiscoverMessage : public core::data::SerializableData {
                public:
                    enum TYPE {
                        UNDEFINED,
                        DISCOVER,
                        RESPONSE
                    };

                    DiscoverMessage();
                    DiscoverMessage(TYPE type, const string &name);
                    DiscoverMessage(TYPE type, const core::dmcp::ServerInformation& serverInformation);

                    virtual ~DiscoverMessage();

                    TYPE getType() const;
                    const core::dmcp::ServerInformation getServerInformation() const;
                    const string getModuleName() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    TYPE m_type;
                    core::dmcp::ServerInformation m_serverInformation;
                    string m_moduleName;
            };
        }
    }
} // core::data::dmcp

#endif /*OPENDAVINCI_DATA_DMCP_DISCOVERMESSAGE_H_*/

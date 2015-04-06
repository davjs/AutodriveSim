/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#ifndef OPENDAVINCI_DATA_DMCP_PULSEMESSAGE_H_
#define OPENDAVINCI_DATA_DMCP_PULSEMESSAGE_H_

#include <vector>

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/Container.h"
#include "core/data/SerializableData.h"
#include "core/data/TimeStamp.h"
#include "core/base/ModuleState.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace std;

            class OPENDAVINCI_API PulseMessage : public core::data::SerializableData {
                public:
                    PulseMessage();
                    PulseMessage(const core::data::TimeStamp &ts, const uint32_t &nominalTimeSlice, const uint32_t &cumulatedTimeSlice);
                    PulseMessage(const PulseMessage &obj);
                    PulseMessage& operator=(const PulseMessage &obj);

                    virtual ~PulseMessage();

                    void setNominalTimeSlice(const uint32_t &nts);
                    uint32_t getNominalTimeSlice() const;

                    void setCumulatedTimeSlice(const uint32_t &cts);
                    uint32_t getCumulatedTimeSlice() const;

                    void setRealTimeFromSupercomponent(const core::data::TimeStamp &ts);
                    const core::data::TimeStamp getRealtimeFromSupercomponent() const;

                    /**
                     * This message adds a container to be transferred to a connected
                     * module from supercomponent.
                     *
                     * @param c Container to be added for transfer to supercomponent.
                     */
                    void addContainer(const core::data::Container &c);

                    /**
                     * This message sets the list of containers to be transferred to a connected
                     * module from supercomponent.
                     *
                     * @param l List of containers to be transferred to supercomponent.
                     */
                    void setListOfContainers(const vector<core::data::Container> &l);

                    /**
                     * This message returns the list of containers to be transferred to a connected
                     * module from supercomponent.
                     *
                     * @return List of containers to be transferred to supercomponent.
                     */
                    vector<core::data::Container> getListOfContainers() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    core::data::TimeStamp m_realTimeFromSupercomponent;
                    uint32_t m_nominalTimeSlice;
                    uint32_t m_cumulatedTimeSlice;
                    vector<core::data::Container> m_listOfContainers;
            };
        }
    }
} // core::data::dmcp

#endif /*OPENDAVINCI_DATA_DMCP_PULSEMESSAGE_H_*/

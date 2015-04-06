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
#ifndef OPENDAVINCI_DATA_DMCP_MODULEDESCRIPTOR_H_
#define OPENDAVINCI_DATA_DMCP_MODULEDESCRIPTOR_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/SerializableData.h"

namespace core {
    namespace data{
        namespace dmcp {

            using namespace std;

            class OPENDAVINCI_API ModuleDescriptor : public core::data::SerializableData {
                public:
                    ModuleDescriptor();

                    ModuleDescriptor(const string& name,
                                     const string& identifier,
                                     const string& version,
                                     const float &frequency);
                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ModuleDescriptor(const ModuleDescriptor &obj);

                    virtual ~ModuleDescriptor();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ModuleDescriptor& operator=(const ModuleDescriptor &obj);

                    const string getName() const;
                    const string getIdentifier() const;
                    const string getVersion() const;
                    float getFrequency() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                protected:
                    string m_name;
                    string m_identifier;
                    string m_version;
                    float m_frequency;
            };
        }
    }
} // core::data::dmcp

#endif /* OPENDAVINCI_DATA_DMCP_MODULEDESCRIPTOR_H_ */

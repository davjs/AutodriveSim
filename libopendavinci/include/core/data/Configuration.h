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

#ifndef OPENDAVINCI_CORE_DATA_CONFIGURATION_H_
#define OPENDAVINCI_CORE_DATA_CONFIGURATION_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/base/KeyValueConfiguration.h"
#include "core/data/SerializableData.h"

namespace core {
    namespace data {

        using namespace std;

        /**
         * This class contains a specific configuration.
         */
        class OPENDAVINCI_API Configuration : public core::data::SerializableData {
            public:
                Configuration();

                /**
                 * Constructor.
                 *
                 * @param keyValueConfiguration Key/value-configuration for constructing this configuration object.
                 */
                Configuration(const core::base::KeyValueConfiguration &keyValueConfiguration);

                virtual ~Configuration();

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                Configuration(const Configuration &obj);

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                Configuration& operator=(const Configuration &obj);

                /**
                 * This method returns the key/value-configuration.
                 *
                 * @return Key/value-configuration.
                 */
                const core::base::KeyValueConfiguration getKeyValueConfiguration() const;

                virtual ostream& operator<<(ostream &out) const;
                virtual istream& operator>>(istream &in);

                virtual const string toString() const;

            private:
                core::base::KeyValueConfiguration m_keyValueConfiguration;
        };

    }
} // core::data

#endif /*OPENDAVINCI_CORE_DATA_CONFIGURATION_H_*/

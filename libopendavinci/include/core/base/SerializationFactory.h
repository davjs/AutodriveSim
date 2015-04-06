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

#ifndef OPENDAVINCI_CORE_BASE_SERIALIZATIONFACTORY_H_
#define OPENDAVINCI_CORE_BASE_SERIALIZATIONFACTORY_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/SharedPointer.h"
#include "core/base/Serializer.h"
#include "core/base/Deserializer.h"
#include "core/exceptions/Exceptions.h"

namespace core {
    namespace base {

        using namespace std;

        /**
         * This class is the factory for providing serializers and
         * deserializers.
         *
         * @See Serializable
         */
        class OPENDAVINCI_API SerializationFactory {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                SerializationFactory(const SerializationFactory &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                SerializationFactory& operator=(const SerializationFactory &);

            public:
                SerializationFactory();

                virtual ~SerializationFactory();

                /**
                 * This method returns a serializer.
                 *
                 * @param out Output stream for serialization.
                 * @return Serializer.
                 */
                Serializer& getSerializer(ostream &out) const;

                /**
                 * This method returns a deserializer.
                 *
                 * @param in Input stream for deserialization.
                 * @return Deserializer.
                 */
                Deserializer& getDeserializer(istream &in) const;

            private:
                mutable vector<SharedPointer<Serializer> > m_listOfSerializers;
                mutable vector<SharedPointer<Deserializer> > m_listOfDeserializers;
        };

    }
} // core::base

#endif /*OPENDAVINCI_CORE_BASE_SERIALIZATIONFACTORY_H_*/

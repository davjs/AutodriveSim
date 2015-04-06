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

#include "core/base/QueryableNetstringsSerializer.h"
#include "core/base/QueryableNetstringsDeserializer.h"
#include "core/base/SerializationFactory.h"

namespace core {
    namespace base {

        using namespace std;

        SerializationFactory::SerializationFactory() :
                m_listOfSerializers(),
                m_listOfDeserializers() {}

        SerializationFactory::~SerializationFactory() {
            m_listOfSerializers.clear();
            m_listOfDeserializers.clear();
        }

        Serializer& SerializationFactory::getSerializer(ostream &out) const {
            Serializer *s = NULL;
            if (m_listOfSerializers.empty()) {
                s = new QueryableNetstringsSerializer(out);
                m_listOfSerializers.push_back(SharedPointer<Serializer>(s));
            }
            else {
                s = &(*(*(m_listOfSerializers.begin()))); // The innermost * dereferences the iterator to SharedPointer<Serializer>, the second * returns the Serializer from within the SharedPointer, and the & turns it into a regular pointer.
            }
            return *s;
        }

        Deserializer& SerializationFactory::getDeserializer(istream &in) const {
            Deserializer *d = NULL;
            if (m_listOfDeserializers.empty()) {
                d = new QueryableNetstringsDeserializer(in);
                m_listOfDeserializers.push_back(SharedPointer<Deserializer>(d)); // The innermost * dereferences the iterator to SharedPointer<Deserializer>, the second * returns the Deserializer from within the SharedPointer, and the & turns it into a regular pointer.
            }
            else {
                d = &(*(*(m_listOfDeserializers.begin())));
            }
            return *d;
        }

    }
} // core::base

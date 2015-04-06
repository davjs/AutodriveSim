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

#ifndef OPENDAVINCI_CORE_DATA_SHAREDDATA_H_
#define OPENDAVINCI_CORE_DATA_SHAREDDATA_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/SerializableData.h"

namespace core {
    namespace data {

        using namespace std;

        /**
         * This class provides information about shared data using shared memory
         * segments. This class can be used to exchange information about
         * accessing this data. It can be used as follows:
         *
         * @code
         * // Server:
         * SharedPointer<wrapper::SharedMemory> memory = wrapper::SharedMemoryFactory::getInstance().createSharedMemory("NameOfSharedMemory", 1024);
         * if (memory->isValid()) {
         *     SharedData sd(memory->getName(), memory->getSize());
         *
         *     Container c(Container::SHARED_DATA, sd);
         *     getConference().send(c);
         *
         *     // Write something to shared memory.
         *     memory->lock();
         *     memset(memory->getAddress(), 1, 1024);
         *     memory->unlock();
         *     ...
         * }
         *
         *
         * // Client:
         * Container c = myFifo.leave();
         * if (c.getDataType() == Container::SHARED_DATA) {
         *     SharedData sd = c.getData<SharedData>();
         *     SharedPointer<wrapper::SharedMemory> memory = wrapper::SharedMemoryFactory::getInstance().attachToSharedMemory(sd.getName());
         *     if (memory->isValid()) {
         *         memory->lock();
         *         char *p = static_cast<char*>(memory->getAddress());
         *         string s(p, memory->getSize());
         *         ...
         *         memory->unlock();
         *     }
         * }
         * @endcode
         */
        class OPENDAVINCI_API SharedData : public SerializableData {
            public:
                SharedData();

                /**
                 * Constructor.
                 *
                 * @param name Name of the shared memory segment.
                 * @param size Size of the shared memory segment.
                 */
                SharedData(const string &name, const uint32_t &size);

                virtual ~SharedData();

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                SharedData(const SharedData &obj);

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                SharedData& operator=(const SharedData &obj);

                /**
                 * This method returns the name of the shared data.
                 *
                 * @return Name for the shared data.
                 */
                const string getName() const;

                /**
                 * This method sets the name of the shared data.
                 *
                 * @param name Name for the shared data.
                 */
                void setName(const string &name);

                /**
                 * This method returns the size of the shared data.
                 *
                 * @return Size for the shared data.
                 */
                virtual uint32_t getSize() const;

                /**
                 * This method sets the size of the shared data.
                 *
                 * @param s Size for the shared data.
                 */
                void setSize(const uint32_t &s);

                virtual ostream& operator<<(ostream &out) const;
                virtual istream& operator>>(istream &in);

                virtual const string toString() const;

            private:
                string m_name;
                uint32_t m_size;
        };

    }
} // core::data

#endif /*OPENDAVINCI_CORE_DATA_SHAREDDATA_H_*/

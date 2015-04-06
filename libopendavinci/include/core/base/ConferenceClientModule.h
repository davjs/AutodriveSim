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

#ifndef OPENDAVINCI_BASE_CONFERENCECLIENTMODULE_H_
#define OPENDAVINCI_BASE_CONFERENCECLIENTMODULE_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/SharedPointer.h"
#include "core/base/Mutex.h"
#include "core/data/Container.h"
#include "core/exceptions/Exceptions.h"
#include "core/io/ContainerConference.h"
#include "core/io/ContainerListener.h"

#include "core/base/ManagedClientModule.h"
#include "core/base/DataStoreManager.h"

namespace core {
    namespace base {

        using namespace std;

        /**
         * This class is the base for every client module. It participates
         * automatically in a UDP multicast container conference. All
         * received data is written into a key/value-map using
         * Container::DATATYPE as key. Thus, it is possible to get the
         * newest data using the map.
         * Furthermore, it is possible to request a thread-safe FIFO-
         * or LIFO-style queue for a specific Container::DATATYPE.
         * It can be used as follows:
         *
         * @code
         * class MyModule: public ConferenceClientModule
         * {
         *     public:
         *         MyModule(const int32_t argc, char **argv) :
         *           ConferenceClientModule(argc, argv, "MyName")
         *         {}
         *
         *        virtual void setUp()
         *        {}
         *
         *        virtual void tearDown()
         *        {}
         *
         *        virtual ModuleState::MODULE_EXITCODE body() {
         *            FIFOQueue fifo;
         *            addDataStoreFor(Container::TIMESTAMP, fifo);
         *
         *            while (getModuleState() == ModuleState::RUNNING) {
         *                Container c = fifo.leave();
         *                TimeStamp ts = c.getData<TimeStamp>();
         *
         *                // Do something...
         *
         *                Container c2(Container::TIMESTAMP, TimeStamp());
         *                getConference().send(c2);
         *            }
         *
         *            return ModuleState::OKAY;
         *         }
         * };
         *
         * // Regular main method.
         * int32_t main(int32_t argc, char **argv) {
         *     MyModule myModule(argc, argv);
         *
         *     return myModule.runModule();
         * }
         * @endcode
         */
        class OPENDAVINCI_API ConferenceClientModule : public ManagedClientModule, public core::io::ContainerListener, public DataStoreManager {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ConferenceClientModule(const ConferenceClientModule& );

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ConferenceClientModule& operator=(const ConferenceClientModule&);

            public:
                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 * @param name Name of this module. This parameter is necessary for identifying the corresponding parts in the configuration.
                 * @throw InvalidArgumentException if the signal handler could not be registered.
                 * @throw NoDatabaseAvailableException if the database could not be created.
                 */
                ConferenceClientModule(const int32_t &argc, char **argv, const string &name) throw (core::exceptions::InvalidArgumentException,
                        core::exceptions::NoDatabaseAvailableException);

                virtual ~ConferenceClientModule();

                /**
                 * This method returns the conference.
                 *
                 * @return Conference.
                 */
                core::io::ContainerConference& getConference();

            protected:
                virtual void setUp() = 0;

                virtual void tearDown() = 0;

                virtual core::base::ModuleState::MODULE_EXITCODE body() = 0;

                virtual void nextContainer(core::data::Container &c);

                virtual void addDataStoreFor(core::base::AbstractDataStore &dataStore);

                virtual void addDataStoreFor(const core::data::Container::DATATYPE &datatype, core::base::AbstractDataStore &dataStore);

                virtual core::base::KeyValueDataStore& getKeyValueDataStore();

            private:
                void setupContainerConference();

                // Distribute input data using thread-safe data stores.
                core::base::Mutex m_dataStoresMutex;
                vector<core::base::AbstractDataStore*> m_listOfDataStores;
                map<core::data::Container::DATATYPE, vector<core::base::AbstractDataStore*> > m_mapOfListOfDataStores;

                // Store all received data using Container::DATATYPE as key.
                core::SharedPointer<core::base::KeyValueDataStore> m_keyValueDataStore;
        };

    }
} // core::base

#endif /*OPENDAVINCI_BASE_CONFERENCECLIENTMODULE_H_*/

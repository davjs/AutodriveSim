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

#ifndef OPENDAVINCI_CORE_WRAPPER_KEYVALUEDATABASEFACTORYWORKER
#define OPENDAVINCI_CORE_WRAPPER_KEYVALUEDATABASEFACTORYWORKER

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/SharedPointer.h"
#include "core/wrapper/KeyValueDatabase.h"
#include "core/wrapper/KeyValueDatabaseLibraryProducts.h"

namespace core {
    namespace wrapper {

        /**
         * This template class provides factory methods to the
         * KeyValueDatabaseFactory. The factory methods' implementations
         * for different products have to be defined in specializations
         * of the KeyValueDatabaseFactoryWorker template class.
         *
         * @See KeyValueDatabaseFactory, KeyValueDatabaseFactoryWorker,
         *      KeyValueDatabaseFactoryLibraryProducts,
         *      BerkeleyDBKeyValueDatabaseFactory, SimpleDBKeyValueDatabaseFactory
         */

        template <KeyValueDatabaseLibraryProducts product>
        class OPENDAVINCI_API KeyValueDatabaseFactoryWorker
        {
            public:
                /**
                 * This method returns a wrapped key/value database.
                 *
                 * @param fileName Name of the underlying file for the database.
                 *                 If left blank (i.e. ""), this method tries to
                 *                 create either an in-memory-only database or
                 *                 uses a default file.
                 * @return  key/value database based on the type of instance this factory is.
                 */
                static SharedPointer<KeyValueDatabase> createKeyValueDatabase(const string &fileName);
        };

    }
} // core::wrapper

#endif /*OPENDAVINCI_CORE_WRAPPER_KEYVALUEDATABASEFACTORYWORKER*/

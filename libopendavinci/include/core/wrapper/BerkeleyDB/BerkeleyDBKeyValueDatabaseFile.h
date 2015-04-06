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

#ifndef OPENDAVINCI_CORE_WRAPPER_BERKELEYDB_BERKELEYDBKEYVALUEDATABASEFILE_H_
#define OPENDAVINCI_CORE_WRAPPER_BERKELEYDB_BERKELEYDBKEYVALUEDATABASEFILE_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include <db.h>

#include "core/wrapper/BerkeleyDB/BerkeleyDBKeyValueDatabase.h"
#include "core/wrapper/KeyValueDatabaseFactoryWorker.h"
#include "core/wrapper/KeyValueDatabaseLibraryProducts.h"

namespace core {
    namespace wrapper {
        namespace BerkeleyDB {

            /**
             * This class implements a key/value database using the BerkeleyDB
             * with a file backend.
             *
             * @See KeyValueDatabaseFactory
             */
            class BerkeleyDBKeyValueDatabaseFile : public BerkeleyDBKeyValueDatabase {
                private:
                    friend class KeyValueDatabaseFactoryWorker<KeyValueDatabaseBerkeleyDB>;

                    BerkeleyDBKeyValueDatabaseFile(const string &databaseFile);

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    BerkeleyDBKeyValueDatabaseFile(const BerkeleyDBKeyValueDatabaseFile &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    BerkeleyDBKeyValueDatabaseFile& operator=(const BerkeleyDBKeyValueDatabaseFile &);

                public:
                    virtual ~BerkeleyDBKeyValueDatabaseFile();

                private:
                    string m_databaseFile;
                    DB_ENV *m_databaseEnvironment;
                    DB *m_database;

                    virtual DB* getDatabase() const;

                    /**
                     * This method sets up the database environment.
                     */
                    void setupEnvironment();

                    /**
                     * This method sets up the database using the previously
                     * set up environment.
                     */
                    void setupDatabase();
            };

        }
    }
} // core::wrapper::BerkeleyDB

#endif /*OPENDAVINCI_CORE_WRAPPER_BERKELEYDB_BERKELEYDBKEYVALUEDATABASEFILE_H_*/

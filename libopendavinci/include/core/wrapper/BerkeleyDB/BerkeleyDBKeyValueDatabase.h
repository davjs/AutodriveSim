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

#ifndef OPENDAVINCI_CORE_WRAPPER_BERKELEYDB_BERKELEYDBKEYVALUEDATABASE_H_
#define OPENDAVINCI_CORE_WRAPPER_BERKELEYDB_BERKELEYDBKEYVALUEDATABASE_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include <db.h>

#include "core/wrapper/Mutex.h"
#include "core/wrapper/KeyValueDatabase.h"

namespace core {
    namespace wrapper {
        namespace BerkeleyDB {

            /**
             * This class is the super class for either the in-memory only
             * database or the file based database using the BerkeleyDB.
             * This class implements generically the storing- and retrieving-methods
             * for both types.
             *
             * @See KeyValueDatabaseFactory
             */
            class BerkeleyDBKeyValueDatabase : public KeyValueDatabase {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    BerkeleyDBKeyValueDatabase(const BerkeleyDBKeyValueDatabase &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    BerkeleyDBKeyValueDatabase& operator=(const BerkeleyDBKeyValueDatabase &);

                protected:
                    BerkeleyDBKeyValueDatabase();

                public:
                    virtual ~BerkeleyDBKeyValueDatabase();

                    virtual void put(const int32_t &key, const string &value);

                    virtual const string get(const int32_t &key) const;

                private:
                    Mutex* m_mutex;

                protected:
                    /**
                     * This method returns the database handle. This method
                     * is implemented in subclasses return either file-based
                     * or in-memory-only databases. This method is used in
                     * put(...) and get(...) methods.
                     *
                     * @return Handle to the actual database.
                     */
                    virtual DB* getDatabase() const = 0;
            };

        }
    }
} // core::wrapper::BerkeleyDB

#endif /*OPENDAVINCI_CORE_WRAPPER_BERKELEYDB_BERKELEYDBKEYVALUEDATABASEFILE_H_*/

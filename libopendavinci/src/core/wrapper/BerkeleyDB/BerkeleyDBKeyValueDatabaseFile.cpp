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

#include "core/wrapper/BerkeleyDB/BerkeleyDBKeyValueDatabaseFile.h"

namespace core {
    namespace wrapper {
        namespace BerkeleyDB {

            using namespace std;

            BerkeleyDBKeyValueDatabaseFile::BerkeleyDBKeyValueDatabaseFile(const string &databaseFile) :
                    m_databaseFile(databaseFile),
                    m_databaseEnvironment(NULL),
                    m_database(NULL) {
                setupEnvironment();
                if (m_databaseEnvironment == NULL) {
                    stringstream s;
                    s << "Error while creating database environment at " << __FILE__ << ": " << __LINE__;
                    throw s.str();
                }

                setupDatabase();
                if (m_databaseEnvironment == NULL) {
                    stringstream s;
                    s << "Error while creating database at " << __FILE__ << ": " << __LINE__;
                    throw s.str();
                }
            }

            BerkeleyDBKeyValueDatabaseFile::~BerkeleyDBKeyValueDatabaseFile() {
                m_database->close(m_database, 0);
                m_databaseEnvironment->close(m_databaseEnvironment, 0);
            }

            void BerkeleyDBKeyValueDatabaseFile::setupEnvironment() {
                // Create database environment.
                int32_t retVal = ::db_env_create(&m_databaseEnvironment, 0);
                if (retVal != 0) {
                    clog << "Error creating database environment: " << ::db_strerror(retVal) << endl;
                    return;
                }

                uint32_t environmentFlags =
                    DB_CREATE     | /* Create the environment if it does not exist. */
                    /*DB_INIT_LOCK  |*/ /* Initialize the locking subsystem. */
                    /*DB_INIT_LOG   |*/ /* Initialize the logging subsystem. */
                    DB_INIT_MPOOL | /* Initialize the memory pool (in-memory cache) */
                    /*DB_INIT_TXN   |*/ /* Initialize transaction subsystem. */
                    /*DB_THREAD     |*/ /* Enable multithreading. */
                    DB_PRIVATE;     /* Region files are not backed by the filesystem. Instead, they are backed by heap memory. */

                // Specify the size of the in-memory cache.
                retVal = m_databaseEnvironment->set_cachesize(m_databaseEnvironment, 0, 10 * 1024 * 1024, 1);
                if (retVal != 0) {
                    clog << "Error increasing the cache size: " << ::db_strerror(retVal) << endl;
                    return;
                }

                // Open the configured environment.
                retVal = m_databaseEnvironment->open(m_databaseEnvironment, NULL /* Environment home MUST be null*/, environmentFlags, 0);
                if (retVal != 0) {
                    clog << "Error opening the environment: " << ::db_strerror(retVal) << endl;
                    return;
                }
            }

            void BerkeleyDBKeyValueDatabaseFile::setupDatabase() {
                // Create database.
                int32_t retVal = ::db_create(&m_database, m_databaseEnvironment, 0);
                if (retVal != 0) {
                    clog << "Error creating database: " << ::db_strerror(retVal) << endl;
                    return;
                }

                // Open in-memory-database.
                uint32_t databaseFlags = DB_CREATE/* | DB_AUTO_COMMIT*/; 

                retVal = m_database->open(m_database, NULL /*TXN pointer*/, m_databaseFile.c_str(), NULL /*Logical databasename*/, DB_BTREE, databaseFlags, 0 /*File mode*/);
                if (retVal != 0) {
                    clog << "Error opening database: " << ::db_strerror(retVal) << endl;
                    return;
                }
            }

            DB* BerkeleyDBKeyValueDatabaseFile::getDatabase() const {
                return m_database;
            }

        }
    }
} // core::wrapper::BerkeleyDB

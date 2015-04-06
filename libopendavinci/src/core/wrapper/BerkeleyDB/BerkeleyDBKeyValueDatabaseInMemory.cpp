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

#include "core/wrapper/BerkeleyDB/BerkeleyDBKeyValueDatabaseInMemory.h"

namespace core {
    namespace wrapper {
        namespace BerkeleyDB {

            using namespace std;

            BerkeleyDBKeyValueDatabaseInMemory::BerkeleyDBKeyValueDatabaseInMemory() :
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
                    s << "Error while creating database in memory at " << __FILE__ << ": " << __LINE__;
                    throw s.str();
                }
            }

            BerkeleyDBKeyValueDatabaseInMemory::~BerkeleyDBKeyValueDatabaseInMemory() {
                m_database->close(m_database, 0);
                m_databaseEnvironment->close(m_databaseEnvironment, 0);
            }

            void BerkeleyDBKeyValueDatabaseInMemory::setupEnvironment() {
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

                // Specify in-memory logging.
                retVal = m_databaseEnvironment->set_flags(m_databaseEnvironment, DB_LOG_INMEMORY, true);
                if (retVal != 0) {
                    clog << "Error setting log subsystem to in-memory: " << ::db_strerror(retVal) << endl;
                    return;
                }

                // Specifiy the size of the in-memory log buffer.
                retVal = m_databaseEnvironment->set_lg_bsize(m_databaseEnvironment, 10 * 1024 * 1024);
                if (retVal != 0) {
                    clog << "Error increasing the log buffer size: " << ::db_strerror(retVal) << endl;
                    return;
                }

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

            void BerkeleyDBKeyValueDatabaseInMemory::setupDatabase() {
                // Create database.
                int32_t retVal = ::db_create(&m_database, m_databaseEnvironment, 0);
                if (retVal != 0) {
                    clog << "Error creating database: " << ::db_strerror(retVal) << endl;
                    return;
                }

                // Open in-memory-database.
                const string databaseName = "inMemoryDatabase";
                uint32_t databaseFlags = DB_CREATE/* | DB_AUTO_COMMIT*/;

                retVal = m_database->open(m_database, NULL /*TXN pointer*/, NULL /*Filename*/, databaseName.c_str() /*Logical databasename*/, DB_BTREE, databaseFlags, 0 /*File mode*/);
                if (retVal != 0) {
                    clog << "Error opening database: " << ::db_strerror(retVal) << endl;
                    return;
                }

                // Configure the cache file.
                ::DB_MPOOLFILE *mpoolFile;
                mpoolFile = m_database->get_mpf(m_database);
                retVal = mpoolFile->set_flags(mpoolFile, DB_MPOOL_NOFILE, true);
                if (retVal != 0) {
                    clog << "Attempt failed to configure for no backing of temp files: " << ::db_strerror(retVal) << endl;
                    return;
                }
            }

            DB* BerkeleyDBKeyValueDatabaseInMemory::getDatabase() const {
                return m_database;
            }

        }
    }
} // core::wrapper::BerkeleyDB

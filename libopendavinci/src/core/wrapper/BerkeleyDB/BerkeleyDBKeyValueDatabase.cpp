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

#include "core/wrapper/BerkeleyDB/BerkeleyDBKeyValueDatabase.h"
#include "core/wrapper/MutexFactory.h"

namespace core {
    namespace wrapper {
        namespace BerkeleyDB {

            using namespace std;

            BerkeleyDBKeyValueDatabase::BerkeleyDBKeyValueDatabase() : m_mutex(NULL) {
                m_mutex = MutexFactory::createMutex();
                if (m_mutex == NULL) {
                    throw std::string("[BerkeleyDB] Error creating mutex");
                }
            }

            BerkeleyDBKeyValueDatabase::~BerkeleyDBKeyValueDatabase() {
                if (m_mutex) {
                    delete m_mutex;
                    m_mutex=NULL;
                }
            }

            void BerkeleyDBKeyValueDatabase::put(const int32_t &key, const string &value) {
                m_mutex->lock();
                    ::DBT databaseKey;
                    ::DBT databaseValue;

                    memset(&databaseKey, 0, sizeof(DBT));
                    memset(&databaseValue, 0, sizeof(DBT));

                    databaseKey.data = (void*) & key;
                    databaseKey.size = sizeof(int);

                    databaseValue.data = (char*)(value.c_str());
                    databaseValue.size = (uint32_t)value.length();

                    // Store key/value.
                    int32_t retVal = getDatabase()->put(getDatabase(), NULL, &databaseKey, &databaseValue, 0);
                    if (retVal != 0) {
                        clog << "Error putting key/value into the database: " << ::db_strerror(retVal) << endl;
                    }
                m_mutex->unlock();
            }

            const string BerkeleyDBKeyValueDatabase::get(const int32_t &key) const {
                m_mutex->lock();
                    ::DBT databaseKey;
                    ::DBT databaseValue;

                    memset(&databaseKey, 0, sizeof(DBT));
                    memset(&databaseValue, 0, sizeof(DBT));

                    databaseKey.data = (void*) & key;
                    databaseKey.size = sizeof(int);

                    databaseValue.flags = DB_DBT_MALLOC;

                    // Retrieve key/value.
                    int32_t retVal = getDatabase()->get(getDatabase(), NULL, &databaseKey, &databaseValue, 0);
                    if ( (retVal != 0) && (retVal != DB_NOTFOUND) ) {
                        clog << "Error getting key/value from the database: " << ::db_strerror(retVal) << endl;
                        return "";
                    }

                    // Try to create a string from the given data and size.
                    string value((char*)databaseValue.data, databaseValue.size);
                    free(databaseValue.data);
                m_mutex->unlock();
                return value;
            }

        }
    }
} // core::wrapper::BerkeleyDB

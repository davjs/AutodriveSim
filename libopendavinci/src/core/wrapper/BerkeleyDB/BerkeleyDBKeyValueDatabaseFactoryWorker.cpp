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

#include "core/wrapper/KeyValueDatabaseFactoryWorker.h"
#include "core/wrapper/KeyValueDatabaseLibraryProducts.h"

#include "core/wrapper/BerkeleyDB/BerkeleyDBKeyValueDatabaseFactoryWorker.h"
#include "core/wrapper/BerkeleyDB/BerkeleyDBKeyValueDatabaseFile.h"
#include "core/wrapper/BerkeleyDB/BerkeleyDBKeyValueDatabaseInMemory.h"

namespace core {
    namespace wrapper {

        SharedPointer<KeyValueDatabase> KeyValueDatabaseFactoryWorker<KeyValueDatabaseBerkeleyDB>::createKeyValueDatabase(const string &fileName)
        {
            SharedPointer<KeyValueDatabase> keyValueDatabase;
            if (fileName != "") {
                keyValueDatabase = SharedPointer<KeyValueDatabase>(new BerkeleyDB::BerkeleyDBKeyValueDatabaseFile(fileName));
            } else {
                keyValueDatabase = SharedPointer<KeyValueDatabase>(new BerkeleyDB::BerkeleyDBKeyValueDatabaseInMemory());
            }
            return keyValueDatabase;
        }

    }
} // core::wrapper::BerkeleyDB

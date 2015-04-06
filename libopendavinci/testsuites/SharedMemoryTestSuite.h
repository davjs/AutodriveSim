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

#ifndef CORE_SHAREDMEMORYTESTSUITE_H_
#define CORE_SHAREDMEMORYTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include "core/SharedPointer.h"
#include "core/data/SharedData.h"
#include "core/wrapper/SharedMemory.h"
#include "core/wrapper/SharedMemoryFactory.h"

using namespace std;

class SharedMemoryTest : public CxxTest::TestSuite {
    public:
        void testSharedData1() {
            core::data::SharedData sd;

            stringstream sstr;
            sstr << sd;

            core::data::SharedData sd2;
            sstr >> sd2;
            TS_ASSERT(sd2.getName() == "");
            TS_ASSERT(sd2.getSize() == 0);
        }

        void testSharedData2() {
            core::data::SharedData sd("abc", 10);

            stringstream sstr;
            sstr << sd;

            core::data::SharedData sd2;
            sstr >> sd2;
            TS_ASSERT(sd2.getName() == "abc");
            TS_ASSERT(sd2.getSize() == 10);
        }

        void testSharedData3() {
            core::data::SharedData sd;
            sd.setName("def");
            sd.setSize(22);

            stringstream sstr;
            sstr << sd;

            core::data::SharedData sd2;
            sstr >> sd2;
            TS_ASSERT(sd2.getName() == "def");
            TS_ASSERT(sd2.getSize() == 22);
        }

        void testSharedMemory() {
            core::SharedPointer<core::wrapper::SharedMemory> memClient;

            core::SharedPointer<core::wrapper::SharedMemory> memServer = core::wrapper::SharedMemoryFactory::createSharedMemory("SharedMemoryTest", 10);
            TS_ASSERT(memServer->isValid());
            TS_ASSERT(memServer->getSize() == 10);
            memServer->lock();
            for (uint32_t i = 0; i < memServer->getSize(); i++) {
                *(((char*)(memServer->getSharedMemory())) + i) = ('A' + i);
            }
            memServer->unlock();

            TS_ASSERT(!memClient.isValid());

            memClient = core::wrapper::SharedMemoryFactory::attachToSharedMemory("SharedMemoryTest");
            TS_ASSERT(memClient->isValid());
            TS_ASSERT(memClient->getSize() == 10);
            memClient->lock();
            for (uint32_t i = 0; i < memClient->getSize(); i++) {
                char c = *(((char*)(memClient->getSharedMemory())) + i);
                TS_ASSERT(c == (char)('A' + i));
            }
            memClient->unlock();
        }

};

#endif /*CORE_SHAREDMEMORYTESTSUITE_H_*/

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

#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/AbstractProtocol.h"

namespace core {
    namespace wrapper {

        AbstractProtocol::AbstractProtocol() :
            m_stringSenderMutex(),
            m_stringSender(NULL)
        {
            m_stringSenderMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_stringSenderMutex.get() == NULL) {
                throw std::string("(SerialPort) Error creating mutex for string sender.");
            }
        }

        AbstractProtocol::~AbstractProtocol() {
            setStringSender(NULL);
        }

        void AbstractProtocol::setStringSender(StringSender* sender) {
            m_stringSenderMutex->lock();
                m_stringSender = sender;
            m_stringSenderMutex->unlock();
        }

        void AbstractProtocol::sendByStringSender(const string &data) {
            if (data.length() > 0) {
                m_stringSenderMutex->lock();
                    if (m_stringSender != NULL) {
                        m_stringSender->send(data);
                    }
                m_stringSenderMutex->unlock();
            }
        }

    }
}


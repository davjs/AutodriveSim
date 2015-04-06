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

#include "core/base/Lock.h"
#include "core/exceptions/Exceptions.h"
#include "core/io/StreamFactory.h"

namespace core {
    namespace io {

        using namespace std;
        using namespace base;
        using namespace exceptions;

        // Initialize singleton instance.
        Mutex StreamFactory::m_singletonMutex;
        StreamFactory* StreamFactory::m_singleton = NULL;

        StreamFactory::StreamFactory() :
                m_listOfInputStreams(),
                m_listOfOutputStreams() {}

        StreamFactory::~StreamFactory() {
            // Clean up output streams.
            vector<istream*>::iterator it = m_listOfInputStreams.begin();
            while (it != m_listOfInputStreams.end()) {
                istream *in = (*it);

                // De-allocate memory.
                OPENDAVINCI_CORE_DELETE_POINTER(in);

                // Iterate.
                it++;
            }
            m_listOfInputStreams.clear();

            // Clean up output streams.
            vector<ostream*>::iterator jt = m_listOfOutputStreams.begin();
            while (jt != m_listOfOutputStreams.end()) {
                ostream *out = (*jt);

                // Flush output stream.
                if (out != NULL) {
                    out->flush();
                }

                // De-allocate memory.
                OPENDAVINCI_CORE_DELETE_POINTER(out);

                // Iterate.
                jt++;
            }
            m_listOfOutputStreams.clear();

            StreamFactory::m_singleton = NULL;
        }

        StreamFactory& StreamFactory::getInstance() {
            {
                Lock l(StreamFactory::m_singletonMutex);
                if (StreamFactory::m_singleton == NULL) {
                    StreamFactory::m_singleton = new StreamFactory();
                }
            }

            return (*StreamFactory::m_singleton);
        }

        istream& StreamFactory::getInputStream(const URL &url) throw (InvalidArgumentException) {
            if (!url.isValid()) {
                stringstream s;
                s << "Given URL: " << url.toString() << " is invalid.";
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, s.str());
            }

            istream *in = NULL;
            if (url.getProtocol() == Protocol::FILEPROTOCOL) {
                in = new fstream(url.getResource().c_str(), ios::in | ios::binary);

                if (!in->good()) {
                    (dynamic_cast<fstream*>(in))->close();
                    OPENDAVINCI_CORE_DELETE_POINTER(in);
                }
            }

            if (in == NULL) {
                stringstream s;
                s << "No input stream created for the given URL: " << url.toString() << ".";
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, s.str());
            }

            m_listOfInputStreams.push_back(in);
            return (*in);
        }

        ostream& StreamFactory::getOutputStream(const URL &url) throw (InvalidArgumentException) {
            if (!url.isValid()) {
                stringstream s;
                s << "Given URL: " << url.toString() << " is invalid.";
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, s.str());
            }

            ostream *out = NULL;
            if (url.getProtocol() == Protocol::FILEPROTOCOL) {
                out = new fstream(url.getResource().c_str(), ios::out | ios::binary | ios::trunc);

                if (!out->good()) {
                    (dynamic_cast<fstream*>(out))->close();
                    OPENDAVINCI_CORE_DELETE_POINTER(out);
                }
            }

            if (out == NULL) {
                stringstream s;
                s << "No output stream created for the given URL: " << url.toString() << ".";
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, s.str());
            }

            m_listOfOutputStreams.push_back(out);
            return (*out);
        }

    }
} // core::io

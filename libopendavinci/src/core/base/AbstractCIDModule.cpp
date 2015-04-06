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

#include "core/base/AbstractCIDModule.h"
#include "core/base/CommandLineParser.h"
#include "core/base/Lock.h"
#include "core/base/Thread.h"

namespace core {
    namespace base {

        using namespace std;
        using namespace exceptions;

        AbstractCIDModule::AbstractCIDModule(const int32_t &argc, char **argv) throw (InvalidArgumentException) :
                m_frequency(1),
                m_identifier(),
                m_mulitcastGroup(),
                m_CID(0),
                m_verbose(false),
                m_profiling(false) {
            parseCommandLine(argc, argv);
        }

        AbstractCIDModule::~AbstractCIDModule() {}

        void AbstractCIDModule::parseCommandLine(const int32_t &argc, char **argv) throw (InvalidArgumentException) {
            if (argc <= 1) {
                errno = 0;
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException,
                                              "Invalid number of arguments. At least a conference group id (--cid=) needed.");
            }

            CommandLineParser cmdParser;
            cmdParser.addCommandLineArgument("id");
            cmdParser.addCommandLineArgument("cid");
            cmdParser.addCommandLineArgument("freq");
            cmdParser.addCommandLineArgument("verbose");
            cmdParser.addCommandLineArgument("profiling");

            cmdParser.parse(argc, argv);

            CommandLineArgument cmdArgumentID = cmdParser.getCommandLineArgument("id");
            CommandLineArgument cmdArgumentCID = cmdParser.getCommandLineArgument("cid");
            CommandLineArgument cmdArgumentFREQ = cmdParser.getCommandLineArgument("freq");
            CommandLineArgument cmdArgumentVERBOSE = cmdParser.getCommandLineArgument("verbose");
            CommandLineArgument cmdArgumentPROFILING = cmdParser.getCommandLineArgument("profiling");

            if (cmdArgumentID.isSet()) {
                m_identifier = cmdArgumentID.getValue<string>();
            }

            if (cmdArgumentFREQ.isSet()) {
                m_frequency = cmdArgumentFREQ.getValue<float>();

                if ( fabs(m_frequency) < 1e-5  ) {
                    errno = 0;
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException,
                                                  "Runtime frequency must be greater than 0.");
                }
            }
            else {
                clog << "No runtime frequency set. Assuming a frequency of 1 Hz." << endl;
            }

            if (cmdArgumentCID.isSet()) {
                m_CID = cmdArgumentCID.getValue<int>();

                if ( (m_CID <= 1) || (m_CID >= 254) ) {
                    errno = 0;
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException,
                                                  "The conference group id has to be in range [2, 254].");
                }

                m_mulitcastGroup = "225.0.0." + cmdArgumentCID.getValue<string>();
            } else {
                errno = 0;
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException,
                                              "No conference group id specified");
            }

            if (cmdArgumentVERBOSE.isSet()) {
                m_verbose = true;
            }

            if (cmdArgumentPROFILING.isSet()) {
                m_profiling = true;
            }
        }

        uint32_t AbstractCIDModule::getCID() const {
            return m_CID;
        }

        float AbstractCIDModule::getFrequency() const {
            return m_frequency;
        }

        const string AbstractCIDModule::getIdentifier() const {
            return m_identifier;
        }

        const string AbstractCIDModule::getMultiCastGroup() const {
            return m_mulitcastGroup;
        }

    }
} // core::base

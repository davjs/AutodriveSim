/**
 * rec2stdout - Dump the content of a .rec file to console (part of simulation environment)
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <sstream>

#include "core/macros.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/data/Container.h"
#include "core/io/URL.h"
#include "core/io/StreamFactory.h"

#include "hesperia/decorator/Data2StringStream.h"

#include "Rec2Stdout.h"

namespace rec2stdout {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace core::io;
    using namespace hesperia::decorator;

    Rec2Stdout::Rec2Stdout(const int32_t &argc, char **argv) :
        ConferenceClientModule(argc, argv, "Rec2Stdout") {}

    Rec2Stdout::~Rec2Stdout() {}

    void Rec2Stdout::setUp() {}

    void Rec2Stdout::tearDown() {}

    ModuleState::MODULE_EXITCODE Rec2Stdout::body() {
        const KeyValueConfiguration kvc = getKeyValueConfiguration();

        // Read the URL of the file to replay.
        URL url(kvc.getValue<string>("rec2stdout.input"));

        // Get the stream using the StreamFactory with the given URL.
        istream &in = StreamFactory::getInstance().getInputStream(url);

        // Seek to the beginning of the input stream.
        in.clear();
        in.seekg(ios::beg);

        // The "current" container contains the data to be used for visualization...
        Container current;
        while ( (getModuleState() == ModuleState::RUNNING) && (in.good()) ) {
            stringstream out;
            Data2StringStream d2sstr(out);

            in >> current;
            d2sstr.toStringStream(current);

            if (out.str().size() > 0) {
                cout << out.str() << endl;
            }
        }

        return ModuleState::OKAY;
    }
} // rec2stdout

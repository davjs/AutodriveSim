/**
 * player - Tool for playing back recorded data
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

#include <cmath>

#include "core/base/Thread.h"
#include "core/io/URL.h"
#include "core/data/player/PlayerCommand.h"
#include "tools/player/Player.h"

#include "PlayerModule.h"

namespace player {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace core::io;
    using namespace tools::player;

    PlayerModule::PlayerModule(const int32_t &argc, char **argv) :
        ConferenceClientModule(argc, argv, "player"),
        m_playerControl() {}

    PlayerModule::~PlayerModule() {}

    void PlayerModule::setUp() {}

    void PlayerModule::tearDown() {}

    void PlayerModule::wait() {
        AbstractModule::wait();
    }

    ModuleState::MODULE_EXITCODE PlayerModule::body() {
        // Check if the player is remotely controlled.
        bool remoteControl = (getKeyValueConfiguration().getValue<bool>("player.remoteControl") != 0);

        // Read the URL of the file to replay.
        URL url(getKeyValueConfiguration().getValue<string>("player.input"));

        // Read the scaling factor.
        double timeScale = getKeyValueConfiguration().getValue<double>("player.timeScale");
        timeScale = (fabs(timeScale) > 1e-5 ? fabs(timeScale) : 1.0);

        // Do we have to rewind the stream on EOF?
        bool autoRewind = (getKeyValueConfiguration().getValue<int>("player.autoRewind") != 0);

        // Size of the memory buffer.
        const uint32_t MEMORY_SEGMENT_SIZE = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.memorySegmentSize");

        // Number of memory segments.
        const uint32_t NUMBER_OF_SEGMENTS = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.numberOfMemorySegments");

        // Run player in asynchronous mode with data caching in background.
        const bool THREADING = true;

        // Add FIFOQueue for controlling the player.
        addDataStoreFor(Container::PLAYER_COMMAND, m_playerControl);

        // Construct player.
        Player player(url, autoRewind, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING);

        // The next container to be sent.
        Container nextContainerToBeSent;

        // Delay between two containers.
        uint32_t delay = 0;

        // If no remote control, simply play the stuff.
        bool playing = (!remoteControl);
        bool doStep = false;

        // The main loop.
        while (getModuleState() == ModuleState::RUNNING) {
            if (playing) {
                // Get container to be sent.
                nextContainerToBeSent = player.getNextContainerToBeSent();

                // Get delay to wait _after_ sending the container.
                delay = player.getDelay() * timeScale;

                // Here, the container is sent while discarding player commands.
                if ( (nextContainerToBeSent.getDataType() != Container::UNDEFINEDDATA) &&
                        (nextContainerToBeSent.getDataType() != Container::PLAYER_COMMAND) ) {

                    // Process next token only if there's no new command.
                    if (!remoteControl || (m_playerControl.isEmpty())) {
                        cerr << "SENT " << nextContainerToBeSent.toString() << " (delay was " << delay << " us): " << nextContainerToBeSent.getReceivedTimeStamp().toString() << endl;

                        getConference().send(nextContainerToBeSent);
                    }

                    // Don't wait while stepping.
                    if (!doStep) {
                        Thread::usleep(delay);
                    }
                }
            }

            // If the last cycle was during a step, disable the stepwise playing and check for remote control.
            if (doStep) {
                playing = false;
                doStep = false;
            }

            // Check remote control.
            if (remoteControl) {
                if (!(m_playerControl.isEmpty())) {
                    Container container = m_playerControl.leave();

                    core::data::player::PlayerCommand pc;
                    pc = container.getData<core::data::player::PlayerCommand>();

                    cerr << "Player: " << pc.toString() << endl;

                    switch (pc.getCommand()) {
                        case core::data::player::PlayerCommand::PLAY:
                            playing = true;
                            break;
                        case core::data::player::PlayerCommand::PAUSE:
                            playing = false;
                            break;
                        case core::data::player::PlayerCommand::STEP_FORWARD:
                            playing = true;
                            doStep = true;
                            break;
                        case core::data::player::PlayerCommand::REWIND:
                            player.rewind();
                            playing = false;
                            break;
                    }
                }
            }

            // If replaying is finished, exit.
            if (!remoteControl && !player.hasMoreData()) {
                break;
            }
        }

        return ModuleState::OKAY;
    }

} // player

#!/bin/bash
# OpenDaVinci Launcher

FREQ="20"
CID="111"

cd /opt/odv/bin 

# Start OpenDaVinci components, autodrivesim & the recorder
gnome-terminal --tab --title="supercomponent" -e "./supercomponent --cid="$CID --tab --title="vehicle" -e "./vehicle --cid="$CID" --freq="$FREQ --tab --title="cockpit" -e "./cockpit --cid="$CID --tab --title="camgen" -e "./camgen --cid="$CID" --freq="$FREQ --tab --title="irus" -e "./irus --cid="$CID" --freq="$FREQ --tab --title="AutodriveSim" -e "./AutodriveSim --cid="$CID" --freq="$FREQ --tab --title="Recorder" -e "./recorder --cid="$CID" --freq="$FREQ




#!/bin/bash 
cd build
make all
make install
cd /opt/msv/bin
echo "auto control."
xterm -e ./supercomponent --cid=111 --freq=20 & xterm -e ./cockpit --cid=111 & xterm -e ./vehicle --cid=111 --freq=20 & xterm -e ./camgen --cid=111 --freq=20 & xterm -e ./irus --cid=111 --freq=20 & xterm -e ./lanedetector --cid=111 --freq=20 & xterm -e ./driver --cid=111 --freq=20

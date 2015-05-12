#! /bin/sh
(cd /opt/odv/bin \
; ./supercomponent --cid=111 --freq=20 > /dev/null 2>&1 & \
./cockpit --cid=111 > /dev/null 2>&1 & \
xterm -e ./vehicle --cid=111 --freq=20 & \
./camgen --cid=111 --freq=20 > /dev/null 2>&1 & \
./irus --cid=111 --freq=20 > /dev/null 2>&1 & \
./lanedetector --cid=111 --freq=20)
wait

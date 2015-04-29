#!/usr/bin/env bash
./generateDataStructures.sh
(cd build && cmake -D CMAKE_INSTALL_PREFIX=/opt/odv/ .. && make all && make install)

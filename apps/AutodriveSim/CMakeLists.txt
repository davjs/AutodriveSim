#
# Mini-Smart-Vehicles.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (AutodriveSim)

# OpenCV libraries.
#FIND_PACKAGE(OpenCV REQUIRED)

SET (OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

SET (HESPERIA_LIBS hesperia)
SET (VEHICLECONTEXT_LIBS vehiclecontext)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libdata_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)
INCLUDE_DIRECTORIES (${libvehiclecontext_SOURCE_DIR}/include)

IF("${PANDABOARD}" STREQUAL "YES")
    SET (CMAKE_C_FLAGS "-pipe -ansi -D PANDABOARD=1")
    SET (CMAKE_CXX_FLAGS "-pipe -ansi -D PANDABOARD=1")

    INCLUDE_DIRECTORIES (/opt/PandaBoard-SD/usr/include)
    LINK_DIRECTORIES (/opt/PandaBoard/lib /opt/PandaBoard-SD/usr/lib /opt/PandaBoard-SD/usr/lib/arm-linux-gnueabi /opt/PandaBoard-SD/usr/lib/lapack /opt/PandaBoard-SD/usr/lib/libblas)

    SET (LIBS ${LIBS} glib-2.0)
    SET (CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath-link=/opt/PandaBoard-SD/lib:/opt/PandaBoard-SD/usr/lib:/opt/PandaBoard-SD/lib/arm-linux-gnueabi:/opt/PandaBoard-SD/usr/lib/arm-linux-gnueabi")
ENDIF("${PANDABOARD}" STREQUAL "YES")

# Recipe for building "AutodriveSim".
FILE(GLOB_RECURSE AutodriveSim-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (AutodriveSimlib STATIC ${AutodriveSim-sources})
ADD_EXECUTABLE (AutodriveSim "${CMAKE_CURRENT_SOURCE_DIR}/apps/MainModule.cpp")
TARGET_LINK_LIBRARIES (AutodriveSim AutodriveSimlib ${DATA_LIBS} ${OPENDAVINCI_LIBS} ${LIBS} ${OpenCV_LIBS}) 

# Recipe for installing "lanedetector".
INSTALL(TARGETS AutodriveSim RUNTIME DESTINATION bin)

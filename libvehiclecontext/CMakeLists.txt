#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (libvehiclecontext)

IF (NOT "${PANDABOARD}" STREQUAL "YES")
    # Set include directories (config.h is generated to ${CMAKE_CURRENT_BINARY_DIR}/include/core").
    INCLUDE_DIRECTORIES (${libopendavinci_BINARY_DIR}/include)

    INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
    INCLUDE_DIRECTORIES (${libhesperia_SOURCE_DIR}/include)
    INCLUDE_DIRECTORIES (${libdata_SOURCE_DIR}/include)
    INCLUDE_DIRECTORIES (include)

    # Recipe for building "vehiclecontext".
    FILE(GLOB_RECURSE libvehiclecontext-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    ADD_LIBRARY (vehiclecontext STATIC ${libvehiclecontext-sources})
    TARGET_LINK_LIBRARIES (vehiclecontext hesperia ${DATA_LIBS} ${OPENDAVINCI_LIBS} ${LIBS}) 
ENDIF(NOT "${PANDABOARD}" STREQUAL "YES")


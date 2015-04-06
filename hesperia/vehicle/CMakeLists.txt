#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (vehicle)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libhesperia_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "vehicle".
FILE(GLOB_RECURSE vehicle-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (vehiclelib STATIC ${vehicle-sources})
ADD_EXECUTABLE (vehicle "${CMAKE_CURRENT_SOURCE_DIR}/apps/vehicle.cpp")
TARGET_LINK_LIBRARIES (vehicle vehiclelib hesperia ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "vehicle".
INSTALL(TARGETS vehicle RUNTIME DESTINATION bin)


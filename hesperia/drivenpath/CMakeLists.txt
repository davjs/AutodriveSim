#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (drivenpath)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libhesperia_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "drivenpath".
FILE(GLOB_RECURSE drivenpath-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (drivenpathlib STATIC ${drivenpath-sources})
ADD_EXECUTABLE (drivenpath "${CMAKE_CURRENT_SOURCE_DIR}/apps/drivenpath.cpp")
TARGET_LINK_LIBRARIES (drivenpath drivenpathlib hesperia ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "drivenpath".
INSTALL(TARGETS drivenpath RUNTIME DESTINATION bin)


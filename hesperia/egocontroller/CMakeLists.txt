#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (egocontroller)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libhesperia_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "egocontroller".
FILE(GLOB_RECURSE egocontroller-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (egocontrollerlib STATIC ${egocontroller-sources})
ADD_EXECUTABLE (egocontroller "${CMAKE_CURRENT_SOURCE_DIR}/apps/egocontroller.cpp")
TARGET_LINK_LIBRARIES (egocontroller egocontrollerlib hesperia ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "egocontroller".
INSTALL(TARGETS egocontroller RUNTIME DESTINATION bin)


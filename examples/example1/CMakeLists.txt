#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example1)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example1".
FILE(GLOB_RECURSE example1-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example1 ${example1-sources})
TARGET_LINK_LIBRARIES (example1 ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "example1".
INSTALL(TARGETS example1 RUNTIME DESTINATION bin) 

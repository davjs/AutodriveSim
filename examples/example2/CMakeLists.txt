#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example2)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example2".
FILE(GLOB_RECURSE example2-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example2 ${example2-sources})
TARGET_LINK_LIBRARIES (example2 ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "example2".
INSTALL(TARGETS example2 RUNTIME DESTINATION bin) 

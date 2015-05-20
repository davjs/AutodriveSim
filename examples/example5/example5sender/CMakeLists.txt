#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example5sender)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example5sender".
FILE(GLOB_RECURSE example5sender-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example5sender ${example5sender-sources})
TARGET_LINK_LIBRARIES (example5sender ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "example5sender".
INSTALL(TARGETS example5sender RUNTIME DESTINATION bin) 

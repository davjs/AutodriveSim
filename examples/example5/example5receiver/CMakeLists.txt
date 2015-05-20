#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example5receiver)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example5receiver".
FILE(GLOB_RECURSE example5receiver-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example5receiver ${example5receiver-sources})
TARGET_LINK_LIBRARIES (example5receiver ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "example5receiver".
INSTALL(TARGETS example5receiver RUNTIME DESTINATION bin) 

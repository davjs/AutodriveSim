#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example7receiver)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example7receiver".
FILE(GLOB_RECURSE example7receiver-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example7receiver ${example7receiver-sources} ${CMAKE_CURRENT_SOURCE_DIR}/../Example7Data.cpp)
TARGET_LINK_LIBRARIES (example7receiver ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "example7receiver".
INSTALL(TARGETS example7receiver RUNTIME DESTINATION bin) 

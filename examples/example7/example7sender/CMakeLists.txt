#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example7sender)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example7sender".
FILE(GLOB_RECURSE example7sender-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example7sender ${example7sender-sources} ${CMAKE_CURRENT_SOURCE_DIR}/../Example7Data.cpp)
TARGET_LINK_LIBRARIES (example7sender ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "example7sender".
INSTALL(TARGETS example7sender RUNTIME DESTINATION bin) 

#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example3receiver)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example3receiver".
FILE(GLOB_RECURSE example3receiver-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example3receiver ${example3receiver-sources} ${CMAKE_CURRENT_SOURCE_DIR}/../Example3Data.cpp)
TARGET_LINK_LIBRARIES (example3receiver ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "example3receiver".
INSTALL(TARGETS example3receiver RUNTIME DESTINATION bin) 

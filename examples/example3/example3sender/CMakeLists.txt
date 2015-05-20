#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example3sender)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example3sender".
FILE(GLOB_RECURSE example3sender-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example3sender ${example3sender-sources} ${CMAKE_CURRENT_SOURCE_DIR}/../Example3Data.cpp)
TARGET_LINK_LIBRARIES (example3sender ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "example3sender".
INSTALL(TARGETS example3sender RUNTIME DESTINATION bin) 

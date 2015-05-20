#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example6sender)

SET (EXAMPLE6DATA_LIBS libexample6data)
INCLUDE_DIRECTORIES (${libexample6data_SOURCE_DIR}/include)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example6sender".
FILE(GLOB_RECURSE example6sender-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example6sender ${example6sender-sources})
TARGET_LINK_LIBRARIES (example6sender ${EXAMPLE6DATA_LIBS} ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "example6sender".
INSTALL(TARGETS example6sender RUNTIME DESTINATION bin) 

#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example6receiver)

SET (EXAMPLE6DATA_LIBS libexample6data)
INCLUDE_DIRECTORIES (${libexample6data_SOURCE_DIR}/include)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example6receiver".
FILE(GLOB_RECURSE example6receiver-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example6receiver ${example6receiver-sources})
TARGET_LINK_LIBRARIES (example6receiver ${EXAMPLE6DATA_LIBS} ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "example6receiver".
INSTALL(TARGETS example6receiver RUNTIME DESTINATION bin) 

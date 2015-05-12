#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (parking)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libdata_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "parking".
FILE(GLOB_RECURSE parking-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_LIBRARY (parkinglib STATIC ${parking-sources})
ADD_EXECUTABLE (parking "${CMAKE_CURRENT_SOURCE_DIR}/MainModule.cpp")
TARGET_LINK_LIBRARIES (parking parkinglib ${DATA_LIBS} ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "parking".
INSTALL(TARGETS parking RUNTIME DESTINATION bin)

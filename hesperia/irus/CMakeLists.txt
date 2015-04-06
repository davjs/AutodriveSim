#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (irus)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libdata_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libhesperia_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "irus".
FILE(GLOB_RECURSE irus-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (iruslib STATIC ${irus-sources})
ADD_EXECUTABLE (irus "${CMAKE_CURRENT_SOURCE_DIR}/apps/irus.cpp")
TARGET_LINK_LIBRARIES (irus iruslib hesperia ${DATA_LIBS} ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "irus".
INSTALL(TARGETS irus RUNTIME DESTINATION bin)


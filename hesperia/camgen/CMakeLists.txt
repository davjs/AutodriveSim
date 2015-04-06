#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (camgen)

SET (LIBS ${LIBS} GL GLU glut)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libhesperia_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "camgen".
FILE(GLOB_RECURSE camgen-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (camgenlib STATIC ${camgen-sources})
ADD_EXECUTABLE (camgen "${CMAKE_CURRENT_SOURCE_DIR}/apps/camgen.cpp")
TARGET_LINK_LIBRARIES (camgen camgenlib hesperia ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "camgen".
INSTALL(TARGETS camgen RUNTIME DESTINATION bin)


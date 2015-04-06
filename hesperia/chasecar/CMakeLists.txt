#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (chasecar)

SET (LIBS ${LIBS} GL GLU glut)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libhesperia_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "chasecar".
FILE(GLOB_RECURSE chasecar-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (chasecarlib STATIC ${chasecar-sources})
ADD_EXECUTABLE (chasecar "${CMAKE_CURRENT_SOURCE_DIR}/apps/chasecar.cpp")
TARGET_LINK_LIBRARIES (chasecar chasecarlib hesperia ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "chasecar".
INSTALL(TARGETS chasecar RUNTIME DESTINATION bin)


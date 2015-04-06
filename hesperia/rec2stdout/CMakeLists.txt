#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (rec2stdout)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libhesperia_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "rec2stdout".
FILE(GLOB_RECURSE rec2stdout-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (rec2stdoutlib STATIC ${rec2stdout-sources})
ADD_EXECUTABLE (rec2stdout "${CMAKE_CURRENT_SOURCE_DIR}/apps/rec2stdout.cpp")
TARGET_LINK_LIBRARIES (rec2stdout rec2stdoutlib hesperia ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "rec2stdout".
INSTALL(TARGETS rec2stdout RUNTIME DESTINATION bin)


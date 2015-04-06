#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

INCLUDE(CheckIncludeFiles)
INCLUDE(CheckIncludeFileCXX)

IF(UNIX)
    IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        SET (THIRDPARTY_LIBS pthread rt)
    ELSE("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        SET (THIRDPARTY_LIBS pthread)
    ENDIF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
ENDIF(UNIX)

# Set 3rd party libraries shipped with this distribution.
SET (THIRDPARTY_LIBS ${THIRDPARTY_LIBS} ziplib zlib dblib)

# Set libraries to link.
SET (OPENDAVINCI_LIBS opendavinci)

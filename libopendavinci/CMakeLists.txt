#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (libopendavinci)

###############################################################################
# Include directories for shipped BerkeleyDB.
INCLUDE_DIRECTORIES (${libzip_SOURCE_DIR}/include)
IF(UNIX)
    INCLUDE_DIRECTORIES (${libdb_SOURCE_DIR}/include-POSIX)
ENDIF(UNIX)

IF(WIN32)
    INCLUDE_DIRECTORIES (${libdb_SOURCE_DIR}/include-WIN32)
ENDIF(WIN32)

###############################################################################
# Check for some necessary include headers.
IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    MESSAGE("(libopendavinci): Enable RT for Linux.")
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_LINUX_RT")
ENDIF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")

###############################################################################
# Set include directories (config.h is generated to ${CMAKE_CURRENT_BINARY_DIR}/include/core").
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/include)
INCLUDE_DIRECTORIES (include)

LINK_DIRECTORIES (${zlib_BINARY_DIR})
LINK_DIRECTORIES (${libzip_BINARY_DIR})
LINK_DIRECTORIES (${libdb_BINARY_DIR})

###############################################################################
# Collect all source files.
FILE(GLOB_RECURSE libopendavinci-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

###############################################################################
# Remove POSIX files on WIN32.
IF(WIN32)
    # Set flag for exporting symbols.
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DOPENDAVINCI_EXPORTS")
    
    # Exclude POSIX files.
    FOREACH(item ${libopendavinci-sources})
      IF(${item} MATCHES "POSIX.+.cpp")
        LIST(REMOVE_ITEM libopendavinci-sources ${item})
      ENDIF()
    ENDFOREACH()
ENDIF()

# Uncomment the following line to compile the WIN32 sources.
#SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Remove WIN32 files on POSIX.
IF(UNIX)
    # Exclude WIN32 files.
    FOREACH(item ${libopendavinci-sources})
      IF(${item} MATCHES "WIN32.+.cpp")
        LIST(REMOVE_ITEM libopendavinci-sources ${item})
      ENDIF()
    ENDFOREACH()
ENDIF()

###############################################################################
ADD_LIBRARY (opendavinci STATIC ${libopendavinci-sources})
TARGET_LINK_LIBRARIES(opendavinci ${THIRDPARTY_LIBS})

###############################################################################
# Recipe for installing "libopendavinci".
INSTALL(TARGETS opendavinci DESTINATION lib)

# Install header files.
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include PATTERN ".svn" EXCLUDE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

###############################################################################
# Enable CxxTest for all available testsuites.
IF(CXXTEST_FOUND)
	FILE(GLOB libopendavinci-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")

    FOREACH(testsuite ${libopendavinci-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

	    CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
	    TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite opendavinci ${OPENDAVINCI_LIBS} ${LIBS} ${THIRDPARTY_LIBS})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)

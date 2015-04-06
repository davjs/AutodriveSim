#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (libhesperia)

FIND_PACKAGE( Boost REQUIRED )
IF(NOT Boost_FOUND)
    MESSAGE("Boost is required to build hesperia.")
ENDIF(NOT Boost_FOUND)

IF(Boost_FOUND)
    LINK_DIRECTORIES ( ${Boost_LIBRARY_DIRS} )
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
ENDIF(Boost_FOUND)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

###############################################################################
# Collect all source files.
FILE(GLOB_RECURSE libhesperia-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

###############################################################################
ADD_LIBRARY (hesperia STATIC ${libhesperia-sources})
TARGET_LINK_LIBRARIES(hesperia ${THIRDPARTY_LIBS})

###############################################################################
# Recipe for installing "libhesperia".
INSTALL(TARGETS hesperia DESTINATION lib)

# Install header files.
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include PATTERN ".svn" EXCLUDE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

###############################################################################
# Enable CxxTest for all available testsuites.
IF(CXXTEST_FOUND)
	FILE(GLOB libhesperia-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")

    FOREACH(testsuite ${libhesperia-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

	    CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
	    TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite hesperia ${OPENDAVINCI_LIBS} ${LIBS} ${THIRDPARTY_LIBS})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)


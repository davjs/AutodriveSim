#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (player)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "player".
FILE(GLOB_RECURSE player-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (playerlib STATIC ${player-sources})
ADD_EXECUTABLE (player "${CMAKE_CURRENT_SOURCE_DIR}/apps/player.cpp")
TARGET_LINK_LIBRARIES (player playerlib ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "player".
INSTALL(TARGETS player RUNTIME DESTINATION bin LIBRARY DESTINATION lib)

# Enable CxxTest for all available testsuites.
IF(CXXTEST_FOUND)
    FILE(GLOB player-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")
    
    FOREACH(testsuite ${player-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

        CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
        TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite playerlib ${OPENDAVINCI_LIBS} ${LIBS})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)

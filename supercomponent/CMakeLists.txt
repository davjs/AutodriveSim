#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (supercomponent)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "supercomponent".
FILE(GLOB_RECURSE supercomponent-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (supercomponentlib STATIC ${supercomponent-sources})
ADD_EXECUTABLE (supercomponent "${CMAKE_CURRENT_SOURCE_DIR}/apps/supercomponent.cpp")
TARGET_LINK_LIBRARIES (supercomponent supercomponentlib ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "supercomponent".
INSTALL(TARGETS supercomponent RUNTIME DESTINATION bin)
INSTALL_FILES(/bin FILES configuration)

# Enable CxxTest for all available testsuites.
IF(CXXTEST_FOUND)
    FILE(GLOB supercomponent-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")
    
    FOREACH(testsuite ${supercomponent-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

        CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
        TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite supercomponentlib ${OPENDAVINCI_LIBS} ${LIBS})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)

#
# This software is open source. Please see COPYING and AUTHORS for further information.
#
PROJECT (libdata)
# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)
# Recipe for building libdata.
FILE(GLOB_RECURSE libdata-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (data STATIC ${libdata-sources})
# Recipe for installing libdata.
INSTALL(TARGETS data DESTINATION lib)
# Install header files.
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include/libdata)
IF(CXXTEST_FOUND)
FILE(GLOB libdata-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")
FOREACH(testsuite ${libdata-testsuites})
    STRING(REPLACE "/" ";" testsuite-list ${testsuite})
    LIST(LENGTH testsuite-list len)
    MATH(EXPR lastItem "${len}-1")
    LIST(GET testsuite-list "${lastItem}" testsuite-short)
	    CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
	    TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite data ${OPENDAVINCI_LIBS} ${LIBS})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)

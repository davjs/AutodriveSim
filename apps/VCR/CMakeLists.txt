#
# Mini-Smart-Vehicles.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (2013-DIT-168-VCR)

# OpenCV libraries.
SET (OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (../cc-data/include)
INCLUDE_DIRECTORIES (include)

IF("${PANDABOARD}" STREQUAL "YES")
    SET (CMAKE_C_FLAGS "-pipe -ansi -D PANDABOARD=1")
    SET (CMAKE_CXX_FLAGS "-pipe -ansi -D PANDABOARD=1")

    INCLUDE_DIRECTORIES (/opt/PandaBoard-SD/usr/include)
    LINK_DIRECTORIES (/opt/PandaBoard/lib /opt/PandaBoard-SD/usr/lib /opt/PandaBoard-SD/usr/lib/arm-linux-gnueabi /opt/PandaBoard-SD/usr/lib/lapack /opt/PandaBoard-SD/usr/lib/libblas)

    SET (LIBS ${LIBS} glib-2.0)
    SET (CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath-link=/opt/PandaBoard-SD/lib:/opt/PandaBoard-SD/usr/lib:/opt/PandaBoard-SD/lib/arm-linux-gnueabi:/opt/PandaBoard-SD/usr/lib/arm-linux-gnueabi")
ENDIF("${PANDABOARD}" STREQUAL "YES")

# Recipe for building "VCR".
FILE(GLOB_RECURSE VCR-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (VCRlib STATIC ${VCR-sources})
ADD_EXECUTABLE (VCR "${CMAKE_CURRENT_SOURCE_DIR}/apps/MainModule.cpp")
TARGET_LINK_LIBRARIES (VCR VCRlib ${CCDATA_LIBS} ${OPENDAVINCI_LIBS} ${LIBS} ${OpenCV_LIBS}) 

# Recipe for installing "VCR".
INSTALL(TARGETS VCR RUNTIME DESTINATION bin/2013/DIT-168) 

# Enable CxxTest for all available testsuites.
IF(CXXTEST_FOUND)
    FILE(GLOB VCR-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")
    
    FOREACH(testsuite ${VCR-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

        CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
        TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite VCRlib ${CCDATA_LIBS} ${OPENDAVINCI_LIBS} ${LIBS} ${OpenCV_LIBS})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)

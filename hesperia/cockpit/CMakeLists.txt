#
# Mini-Smart-Vehicles.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (cockpit)

# Qt4 libraries.
FIND_PACKAGE(Qt4 REQUIRED)

# Include the Qt4 include headers and libraries definitions.
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

# Libraries to link against.
SET (LIBS ${LIBS} QtCore QtGui QtOpenGL GL GLU glut)


IF("${PANDABOARD}" STREQUAL "YES")
    SET (CMAKE_C_FLAGS "-march=armv7-a -pipe -O2 -Wall -W -D_REENTRANT -DQT_WEBKIT -DQT_NO_DEBUG -DQT_CORE_LIB -DQT_SHARED -Wno-deprecated -D PANDABOARD=1")
    SET (CMAKE_CXX_FLAGS "-march=armv7-a -pipe -O2 -Wall -W -D_REENTRANT -DQT_WEBKIT -DQT_NO_DEBUG -DQT_CORE_LIB -DQT_SHARED -Wno-deprecated -D PANDABOARD=1")

    INCLUDE_DIRECTORIES (${PANDABOARD-ROOT}/usr/include)
    LINK_DIRECTORIES (${PANDABOARD-ROOT}/lib ${PANDABOARD-ROOT}/usr/lib ${PANDABOARD-ROOT}/usr/lib/arm-linux-gnueabi ${PANDABOARD-ROOT}/usr/lib/lapack ${PANDABOARD-ROOT}/usr/lib/libblas)

    SET (LIBS ${LIBS} EGL glib-2.0)
    SET (CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath-link=${PANDABOARD-ROOT}/lib:${PANDABOARD-ROOT}/usr/lib:${PANDABOARD-ROOT}/lib/arm-linux-gnueabi:${PANDABOARD-ROOT}/usr/lib/arm-linux-gnueabi")
ELSE("${PANDABOARD}" STREQUAL "YES")
    SET (LIBS ${LIBS} qwt-qt4)
ENDIF("${PANDABOARD}" STREQUAL "YES")

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libdata_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (${libhesperia_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for generating MOC files.
FILE(GLOB_RECURSE cockpit-headers "${CMAKE_CURRENT_SOURCE_DIR}/include" *.h)
QT4_WRAP_CPP(cockpit-headers-moc ${cockpit-headers})

# Recipe for building "cockpit".
FILE(GLOB_RECURSE cockpit-sources "${CMAKE_CURRENT_SOURCE_DIR}/src" *.cpp)

# Translations.
SET(myapp_TRANSLATIONS
    cockpit_de_DE.ts
    cockpit_en_US.ts
)

set(FILES_TO_TRANSLATE
    ${cockpit-sources}
    ${cockpit-headers-moc}
)

QT4_CREATE_TRANSLATION(QM_FILES ${FILES_TO_TRANSLATE} ${myapp_TRANSLATIONS})
QT4_ADD_TRANSLATION(QM ${myapp_TRANSLATIONS})

# Build the binary.
ADD_LIBRARY (cockpitlib STATIC ${cockpit-sources} ${cockpit-headers-moc})
ADD_EXECUTABLE (cockpit "${CMAKE_CURRENT_SOURCE_DIR}/apps/MainModule.cpp" ${QM})
TARGET_LINK_LIBRARIES (cockpit cockpitlib hesperia ${DATA_LIBS} ${OPENDAVINCI_LIBS} ${LIBS}) 

# Recipe for installing "cockpit".
INSTALL(TARGETS cockpit RUNTIME DESTINATION bin) 

# Enable CxxTest for all available testsuites.
IF(CXXTEST_FOUND)
    FILE(GLOB cockpit-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")
    
    FOREACH(testsuite ${cockpit-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

        CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
        TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite cockpitlib hesperia ${DATA_LIBS} ${OPENDAVINCI_LIBS} ${LIBS})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)


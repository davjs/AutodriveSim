#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

# Add subdirectories.
ADD_SUBDIRECTORY (example1)
ADD_SUBDIRECTORY (example2)
ADD_SUBDIRECTORY (example3)

IF(UNIX)
    IF((NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin") AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD") AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "NetBSD") AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "OpenBSD"))
        # Don't build the Kalman filter on Darwin as it requires OpenCV.
        IF (NOT "${PANDABOARD}" STREQUAL "YES")
	    ADD_SUBDIRECTORY (example4)
        ENDIF(NOT "${PANDABOARD}" STREQUAL "YES")

        # Don't build the Serial Port example on Darwin due to missing libraries.
        ADD_SUBDIRECTORY (example5)
    ENDIF()
ENDIF(UNIX)

#ADD_SUBDIRECTORY (example6) # Please see example6/README.TXT before enabling this target.

ADD_SUBDIRECTORY (example7)


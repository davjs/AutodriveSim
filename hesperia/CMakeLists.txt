#
# Mini-Smart-Vehicles.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

IF (NOT "${PANDABOARD}" STREQUAL "YES")
    # Add subdirectories.
    ADD_SUBDIRECTORY (libhesperia)

    # hesperia depends on OpenCV.
    SET (OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)
    SET (LIBS ${LIBS} ${OpenCV_LIBS})

    ADD_SUBDIRECTORY (camgen)
    ADD_SUBDIRECTORY (cockpit)
    ADD_SUBDIRECTORY (chasecar)
    ADD_SUBDIRECTORY (drivenpath)
    ADD_SUBDIRECTORY (egocontroller)
    ADD_SUBDIRECTORY (irus)
    ADD_SUBDIRECTORY (rec2stdout)
    ADD_SUBDIRECTORY (vehicle)

    # Installing scenarios and models.
    FILE(GLOB SCNX "Scenarios/*.scnx")
    INSTALL(FILES ${SCNX} DESTINATION bin/Scenarios)

    FILE(GLOB OBJX "Scenarios/Evaluation/*.scnx")
    INSTALL(FILES ${OBJX} DESTINATION bin/Scenarios/Evaluation)

    FILE(GLOB OBJX "Scenarios/Models/*.objx")
    INSTALL(FILES ${OBJX} DESTINATION bin/Scenarios/Models)
ENDIF(NOT "${PANDABOARD}" STREQUAL "YES")


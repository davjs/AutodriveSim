# Mini-Smart-Vehicles sources.
# Disable QT and OpenCV apps on platforms missing those libraries.
IF((NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin") AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD") AND (NOT WIN32) AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "NetBSD") AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "OpenBSD"))
    # Application for receiving data from hesperia or a USB camera.
    ADD_SUBDIRECTORY (lanedetector)

    # Application for connecting to a serial embedded software/hardware board (STM32F4 Discovery Board or Arduino).
    ADD_SUBDIRECTORY (proxy)

    # Application to compute steering wheel values and acceleration/braking values.
    ADD_SUBDIRECTORY (driver)

    # Application for recording a video of the driving performance.
    ADD_SUBDIRECTORY (VCR)
ENDIF()

# Special target to simplify the rsync command.
IF("${PANDABOARD}" STREQUAL "YES")
ADD_CUSTOM_TARGET(push2meili-1
#    COMMAND rsync -ave ssh /opt/msv-ARM/ meili@192.168.0.100:/opt/msv/
    COMMAND rsync -ave ssh /opt/msv-ARM/ meili@192.168.0.100:/opt/msv/bin/msv
    DEPENDS cc-data sensorboard lanedetector driver proxy
)

ADD_CUSTOM_TARGET(push2meili-2
#    COMMAND rsync -ave ssh /opt/msv-ARM/ meili@192.168.0.101:/opt/msv/
    COMMAND rsync -ave ssh /opt/msv-ARM/ meili@192.168.0.101:/opt/msv/bin/msv
    DEPENDS cc-data sensorboard lanedetector driver proxy
)
ENDIF("${PANDABOARD}" STREQUAL "YES")


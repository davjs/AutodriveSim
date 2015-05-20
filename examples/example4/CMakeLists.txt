#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (example4)

# OpenCV libraries.
SET (OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

# Include directories from core.
INCLUDE_DIRECTORIES (${libopendavinci_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

# Recipe for building "example4".
FILE(GLOB_RECURSE example4-sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_EXECUTABLE (example4 ${example4-sources})
TARGET_LINK_LIBRARIES (example4 ${OPENDAVINCI_LIBS} ${LIBS} ${OpenCV_LIBS}) 

# Recipe for installing "example4".
INSTALL(TARGETS example4 RUNTIME DESTINATION bin) 

SET(CMAKE_SYSTEM_NAME Linux)

# This flag sets further include and library paths in dependent CMakeLists.txt
SET(PANDABOARD YES)

# This flag sets the root path of the PandaBoard's SD root path
SET(PANDABOARD-ROOT /opt/PandaBoard-SD)

# Specify the cross compiler.
SET(CMAKE_C_COMPILER   /usr/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)

# Specify the location of the target environment.
SET(CMAKE_FIND_ROOT_PATH /opt/PandaBoard-SD)

# Specify the search directory for programs in the build host directories.
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)


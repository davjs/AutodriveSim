#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (zlib)

INCLUDE_DIRECTORIES (include)

SET (zlib-sources
    src/adler32.c
    src/compress.c
    src/crc32.c
    src/gzio.c
    src/uncompr.c
    src/deflate.c
    src/trees.c
    src/zutil.c
    src/inflate.c
    src/infback.c
    src/inftrees.c
    src/inffast.c
)

ADD_LIBRARY (zlib STATIC ${zlib-sources})


project(zlib)

set(zlib_HEADER_FILES
    "crc32.h"
    "deflate.h"
    "gzguts.h"
    "inffast.h"
    "inffixed.h"
    "inflate.h"
    "inftrees.h"
    "trees.h"
    "zconf.h"
    "zlib.h"
    "zutil.h"
)

set(zlib_SOURCE_FILES
    "adler32.c"
    "compress.c"
    "crc32.c"
    "deflate.c"
    "infback.c"
    "inffast.c"
    "inflate.c"
    "inftrees.c"
    "trees.c"
    "uncompr.c"
    "zutil.c"
)

add_library(zlib ${zlib_HEADER_FILES} ${zlib_SOURCE_FILES})
target_include_directories(zlib PUBLIC "${zlib_SOURCE_DIR}")
set_property(TARGET "zlib" PROPERTY FOLDER "third_party")

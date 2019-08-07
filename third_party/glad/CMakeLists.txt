# http://glad.dav1d.de/#profile=core&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&language=c-debug&loader=on

find_package(OpenGL REQUIRED)

set(glad_HEADER_FILES
    "include/glad/glad.h"
    "include/KHR/khrplatform.h"
)

set(glad_SOURCE_FILES
    "src/glad.c"
)

add_library(glad STATIC ${glad_HEADER_FILES} ${glad_SOURCE_FILES})
target_include_directories(glad PUBLIC "include")
target_link_libraries(glad ${OPENGL_LIBRARIES})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # This switch allows us to link to glad statically with the symbols in the data section, not in the header section.
    # https://github.com/libigl/libigl/issues/751
    target_compile_options(glad PRIVATE "-fno-common")
endif()


set(FREETYPE2_ROOT_DIR "" CACHE PATH "freetype2 source root directory")
if(NOT FREETYPE2_ROOT_DIR)
    message(FATAL_ERROR "freetype2 not found. Please set FREETYPE2_ROOT_DIR.")
endif()

add_subdirectory("${FREETYPE2_ROOT_DIR}" "freetype2")

set_property(TARGET freetype PROPERTY FOLDER third_party/freetype2)
set_property(TARGET dist PROPERTY FOLDER third_party/freetype2)

target_include_directories(freetype PUBLIC "${freetype_SOURCE_DIR}/include")
target_include_directories(freetype PRIVATE "${zlib_BINARY_DIR}")

target_compile_definitions(freetype PRIVATE "-D_CRT_SECURE_NO_WARNINGS")


add_subdirectory("glfw-3.2.1" "third_party/glfw")
add_subdirectory("zlib-1.2.11" "third_party/zlib")
add_subdirectory("libpng-1.6.33" "third_party/libpng")

# freetype2

add_subdirectory("freetype2-2.6.3" "third_party/freetype2")
set_property(TARGET freetype PROPERTY FOLDER third_party/freetype2)
set_property(TARGET dist PROPERTY FOLDER third_party/freetype2)
target_include_directories(freetype PUBLIC "${freetype_SOURCE_DIR}/include")
target_include_directories(freetype PRIVATE "${zlib_BINARY_DIR}")
target_compile_definitions(freetype PRIVATE "-D_CRT_SECURE_NO_WARNINGS")

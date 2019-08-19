
add_subdirectory("glad" "third_party/glad")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory("glfw-3.3" "third_party/glfw")

add_subdirectory("zlib-1.2.11" "third_party/zlib")
add_subdirectory("libpng-1.6.33" "third_party/libpng")

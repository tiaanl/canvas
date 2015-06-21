project("glad")

find_package("OpenGL" REQUIRED)

add_library("glad"
  "include/glad/glad.h"
  "include/glad/glad_wgl.h"
  "include/KHR/khrplatform.h"
  "src/glad.c"
  "src/glad_wgl.c"
)

target_include_directories("glad" PUBLIC "${glad_SOURCE_DIR}/include")
target_link_libraries("glad" ${OPENGL_LIBRARIES})

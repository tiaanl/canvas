project("glad")

find_package("OpenGL" REQUIRED)

set(glad_SOURCE_FILES
  "include/glad/glad.h"
  "include/KHR/khrplatform.h"
  "src/glad.c"
)

if(WIN32)
  list(APPEND glad_SOURCE_FILES
  	"include/glad/glad_wgl.h"
  	"src/glad_wgl.c"
  )
endif()


add_library("glad" ${glad_SOURCE_FILES})

target_include_directories("glad" PUBLIC "${glad_SOURCE_DIR}/include")
target_link_libraries("glad" ${OPENGL_LIBRARIES})

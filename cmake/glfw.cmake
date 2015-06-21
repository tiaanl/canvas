
set(GLFW_ROOT_DIR "" CACHE PATH "GLFW source root directory")
if(NOT GLFW_ROOT_DIR)
  message(FATAL_ERROR "GLFW not found. Please set GLFW_ROOT_DIR.")
endif()

add_subdirectory("${GLFW_ROOT_DIR}" "glfw")
target_include_directories("glfw" PUBLIC "${GLFW_SOURCE_DIR}/include")
set_property(TARGET "glfw" PROPERTY FOLDER "glfw")

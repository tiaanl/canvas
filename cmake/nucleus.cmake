
set(NUCLEUS_ROOT_DIR "" CACHE PATH "Nucleus source root directory")
if(NOT NUCLEUS_ROOT_DIR)
  message(FATAL_ERROR "Nucleus not found. Please set NUCLEUS_ROOT_DIR.")
endif()

add_subdirectory("${NUCLEUS_ROOT_DIR}" "nucleus")

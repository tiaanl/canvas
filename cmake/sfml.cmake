
set(SFML_ROOT_DIR "" CACHE PATH "SFML source root directory")
if(NOT SFML_ROOT_DIR)
  message(FATAL_ERROR "SFML not found. Please set SFML_ROOT_DIR.")
endif()

if(NOT BUILD_SHARED_LIBS)
  add_definitions("-DSFML_STATIC")
endif()

add_subdirectory("${SFML_ROOT_DIR}" "sfml")

target_include_directories("sfml-window" PUBLIC "${SFML_SOURCE_DIR}/include")

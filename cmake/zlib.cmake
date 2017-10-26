
set(ZLIB_ROOT_DIR "" CACHE PATH "ZLIB source root directory")
if(NOT ZLIB_ROOT_DIR)
  message(FATAL_ERROR "ZLIB not found. Please set ZLIB_ROOT_DIR.")
endif()

add_subdirectory("${ZLIB_ROOT_DIR}" "zlib")
target_include_directories("zlib" PUBLIC "${ZLIB_ROOT_DIR}")
set_property(TARGET "zlib" PROPERTY FOLDER "third_party")
set_property(TARGET "example" PROPERTY FOLDER "third_party")
set_property(TARGET "minigzip" PROPERTY FOLDER "third_party")
set_property(TARGET "zlibstatic" PROPERTY FOLDER "third_party")

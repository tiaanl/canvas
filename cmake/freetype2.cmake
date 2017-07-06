
set(FREETYPE2_ROOT_DIR "" CACHE PATH "freetype2 source root directory")
if(NOT FREETYPE2_ROOT_DIR)
    message(FATAL_ERROR "freetype2 not found. Please set FREETYPE2_ROOT_DIR.")
endif()

add_subdirectory("${FREETYPE2_ROOT_DIR}" "freetype2")
# target_include_directories("freetype2" PUBLIC "${FREETYPE2_ROOT_DIR}/include")
# set_property(TARGET "freetype2" PROPERTY FOLDER "freetype2")

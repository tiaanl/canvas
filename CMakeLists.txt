cmake_minimum_required(VERSION 3.2)
project("canvas")

# General options

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
endif()

# Dependencies

option(JUNCTIONS_BUILD_DEPENDENCIES "Build all dependencies with this library")
if(JUNCTIONS_BUILD_DEPENDENCIES)
  include("cmake/nucleus.cmake")
  include("cmake/sfml.cmake")
endif()

if(NUCLEUS_BUILD_UNITTESTS)
  option("JUNCTIONS_BUILD_UNITTESTS" "Enable unit testing for this library.")
endif()

# canvas

set("canvas_INCLUDE_FILES"
  "include/canvas/app.h"
  "include/canvas/opengl.h"
  "include/canvas/rendering/canvas.h"
  "include/canvas/utils/color.h"
  "include/canvas/utils/pos.h"
  "include/canvas/utils/rect.h"
  "include/canvas/utils/size.h"
  "include/canvas/windows/event.h"
  "include/canvas/windows/window.h"
  "include/canvas/windows/window_delegate.h"
  "include/canvas/windows/window_style.h"
)

set("canvas_SOURCE_FILES"
  "src/app.cpp"
  "src/rendering/canvas.cpp"
  "src/windows/window.cpp"
  "src/windows/window_delegate.cpp"
)

add_library("canvas" STATIC ${canvas_INCLUDE_FILES} ${canvas_SOURCE_FILES})
target_link_libraries("canvas" "nucleus" "sfml-main" "sfml-window" "sfml-system")
target_include_directories("canvas" PUBLIC "${canvas_SOURCE_DIR}/include")

add_executable("minimal" WIN32 MACOSX_BUNDLE "examples/minimal/minimal.cpp")
target_link_libraries("minimal" "canvas")

cmake_minimum_required(VERSION 3.2)
project("canvas")

include("cmake/nucleus.cmake")

set("canvas_INCLUDE_FILES"
  "include/canvas/utils/pos.h"
  "include/canvas/utils/rect.h"
  "include/canvas/utils/size.h"
  "include/canvas/windows/context.h"
  "include/canvas/windows/context_settings.h"
  "include/canvas/windows/event.h"
  "include/canvas/windows/video_mode.h"
  "include/canvas/windows/window.h"
  "include/canvas/windows/window_detail.h"
  "include/canvas/windows/window_handle.h"
  "include/canvas/windows/window_style.h"
)

set("canvas_SOURCE_FILES"
  "src/windows/video_mode.cpp"
  "src/windows/window.cpp"
  "src/windows/window_detail.cpp"
)

if(WIN32)
  list(APPEND "canvas_INCLUDE_FILES"
    "include/canvas/windows/win/message_pump_win.h"
    "include/canvas/windows/win/window_detail_win.h"
  )

  list(APPEND "canvas_SOURCE_FILES"
    "src/windows/win/message_pump_win.cpp"
    "src/windows/win/window_detail_win.cpp"
    "src/windows/win/video_mode_win.cpp"
  )
endif()

add_library("canvas" STATIC ${canvas_INCLUDE_FILES} ${canvas_SOURCE_FILES})
target_link_libraries("canvas" "nucleus")
target_include_directories("canvas" PUBLIC "${canvas_SOURCE_DIR}/include")

add_executable("minimal" "examples/minimal/minimal.cpp")
target_link_libraries("minimal" "canvas")

cmake_minimum_required(VERSION 3.19)

if (TARGET canvas)
    return()
endif ()

project(canvas)

option(CANVAS_BUILD_EXAMPLES "Build canvas examples" OFF)

add_subdirectory(../nucleus nucleus)
add_subdirectory(../floats floats)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

set(HEADER_FILES
    include/canvas/app.h
    include/canvas/debug/debug_font.h
    include/canvas/debug/debug_interface.h
    include/canvas/debug/profile_printer.h
    include/canvas/opengl.h
    include/canvas/renderer/command.h
    include/canvas/renderer/immediate_renderer.h
    include/canvas/renderer/line_renderer.h
    include/canvas/renderer/renderer.h
    include/canvas/renderer/types.h
    include/canvas/renderer/uniform_buffer.h
    include/canvas/renderer/vertex_definition.h
    include/canvas/renderer/immediate_mesh.h
    include/canvas/renderer/pipeline.h
    include/canvas/renderer/pipeline_builder.h
    include/canvas/renderer/texture_slots.h
    include/canvas/static_data/all.h
    include/canvas/utils/color.h
    include/canvas/utils/gl_check.h
    include/canvas/utils/geometry.h
    include/canvas/utils/immediate_shapes.h
    include/canvas/utils/shader_source.h
    include/canvas/windows/event.h
    include/canvas/windows/keyboard.h
    include/canvas/windows/window.h
    include/canvas/windows/window_delegate.h
    include/canvas/windows/window_style.h
    include/canvas/windows/keyboard_event_handler_interface.h
    include/canvas/windows/mouse_event_handler_interface.h
    include/canvas/message_loop/message_pump_ui.h
    )

set(SOURCE_FILES
    src/debug/debug_font.cpp
    src/debug/debug_interface.cpp
    src/debug/profile_printer.cpp
    src/renderer/immediate_renderer.cpp
    src/renderer/line_renderer.cpp
    src/renderer/renderer.cpp
    src/renderer/uniform_buffer.cpp
    src/renderer/vertex_definition.cpp
    src/renderer/immediate_mesh.cpp
    src/renderer/pipeline.cpp
    src/renderer/pipeline_builder.cpp
    src/renderer/texture_slots.cpp
    src/static_data/MonoFont.cpp
    src/utils/color.cpp
    src/utils/gl_check.cpp
    src/utils/geometry.cpp
    src/utils/immediate_shapes.cpp
    src/utils/shader_source.cpp
    src/windows/window.cpp
    src/windows/window_delegate.cpp
    src/message_loop/message_pump_ui.cpp
    )

nucleus_add_library(canvas ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(canvas PUBLIC nucleus floats glfw)
target_link_libraries(canvas PRIVATE glad::glad)
target_compile_definitions(canvas PUBLIC -DUNICODE -D_CRT_SECURE_NO_WARNINGS)

set(TESTS_FILES
    tests/Renderer/uniform_buffer_tests.cpp
    tests/Renderer/vertex_definition_tests.cpp
    )

nucleus_add_executable(canvas_tests ${TESTS_FILES})
target_link_libraries(canvas_tests PRIVATE canvas tests_main)

if (CANVAS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

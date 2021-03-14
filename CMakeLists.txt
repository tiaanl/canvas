cmake_minimum_required(VERSION 3.16)

if (TARGET canvas)
    return()
endif ()

project(canvas)

option(CANVAS_BUILD_EXAMPLES "Build canvas examples" OFF)

add_subdirectory(../nucleus nucleus)
add_subdirectory(../floats floats)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

set(canvas_HEADER_FILES
    include/canvas/App.h
    include/canvas/Debug/DebugFont.h
    include/canvas/Debug/DebugInterface.h
    include/canvas/Debug/ProfilePrinter.h
    include/canvas/OpenGL.h
    include/canvas/Renderer/Command.h
    include/canvas/Renderer/ImmediateRenderer.h
    include/canvas/Renderer/LineRenderer.h
    include/canvas/Renderer/Renderer.h
    include/canvas/Renderer/Types.h
    include/canvas/Renderer/UniformBuffer.h
    include/canvas/Renderer/VertexDefinition.h
    include/canvas/StaticData/All.h
    include/canvas/Utils/Color.h
    include/canvas/Utils/Geometry.h
    include/canvas/Utils/GLCheck.h
    include/canvas/Utils/ImmediateShapes.h
    include/canvas/Utils/ShaderSource.h
    include/canvas/Windows/Event.h
    include/canvas/Windows/Keyboard.h
    include/canvas/Windows/KeyboardEventHandlerInterface.h
    include/canvas/Windows/MouseEventHandlerInterface.h
    include/canvas/Windows/Window.h
    include/canvas/Windows/WindowDelegate.h
    include/canvas/Windows/WindowStyle.h
    )

set(canvas_SOURCE_FILES
    src/Debug/DebugFont.cpp
    src/Debug/DebugInterface.cpp
    src/Debug/ProfilePrinter.cpp
    src/Renderer/ImmediateRenderer.cpp
    src/Renderer/LineRenderer.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/UniformBuffer.cpp
    src/Renderer/VertexDefinition.cpp
    src/StaticData/MonoFont.cpp
    src/Utils/Color.cpp
    src/Utils/GLCheck.cpp
    src/Utils/Geometry.cpp
    src/Utils/ImmediateShapes.cpp
    src/Utils/ShaderSource.cpp
    src/Windows/Window.cpp
    src/Windows/WindowDelegate.cpp
    )

nucleus_add_library(canvas ${canvas_HEADER_FILES} ${canvas_SOURCE_FILES})
target_link_libraries(canvas PUBLIC nucleus floats glfw)
target_link_libraries(canvas PRIVATE glad::glad)
target_compile_definitions(canvas PUBLIC -DUNICODE -D_CRT_SECURE_NO_WARNINGS)

set(canvasTests_SOURCE_FILES
    tests/Renderer/UniformBufferTests.cpp
    tests/Renderer/VertexDefinitionTests.cpp
    )

nucleus_add_executable(canvasTests ${canvasTests_SOURCE_FILES})
target_link_libraries(canvasTests PRIVATE canvas testsMain)

if (CANVAS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

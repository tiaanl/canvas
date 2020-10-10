cmake_minimum_required(VERSION 3.16)

if (TARGET canvas)
    return()
endif ()

project(canvas)

option(CANVAS_BUILD_EXAMPLES "Build canvas examples" OFF)

add_subdirectory(../nucleus nucleus)

find_package(glfw3 CONFIG REQUIRED)

set(canvas_HEADER_FILES
    include/canvas/App.h
    include/canvas/Debug/DebugFont.h
    include/canvas/Debug/DebugInterface.h
    include/canvas/Debug/ProfilePrinter.h
    include/canvas/Math/Angle.h
    include/canvas/Math/Common.h
    include/canvas/Math/Intersection.h
    include/canvas/Math/Mat3.h
    include/canvas/Math/Mat4.h
    include/canvas/Math/Plane.h
    include/canvas/Math/Quaternion.h
    include/canvas/Math/Ray.h
    include/canvas/Math/Transform.h
    include/canvas/Math/Vec2.h
    include/canvas/Math/Vec3.h
    include/canvas/Math/Vec4.h
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
    include/canvas/Utils/Pos.h
    include/canvas/Utils/Rect.h
    include/canvas/Utils/ShaderSource.h
    include/canvas/Utils/Size.h
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
    src/Math/Angle.cpp
    src/Math/Mat3.cpp
    src/Math/Mat4.cpp
    src/Math/Quaternion.cpp
    src/Math/Transform.cpp
    src/Math/Vec2.cpp
    src/Math/Vec3.cpp
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
    src/glad/glad.c
    )

nucleus_add_library(canvas ${canvas_HEADER_FILES} ${canvas_SOURCE_FILES})
target_include_directories(canvas PRIVATE src/glad)
target_link_libraries(canvas nucleus glfw)
target_compile_definitions(canvas PUBLIC -DUNICODE -D_CRT_SECURE_NO_WARNINGS)

find_package(Catch2 CONFIG REQUIRED)

set(canvasTests_SOURCE_FILES
    tests/Main.cpp
    tests/Math/Mat4Tests.cpp
    tests/Math/TransformTests.cpp
    tests/Math/Vec2Tests.cpp
    tests/Math/Vec3Tests.cpp
    tests/Math/Vec4Tests.cpp
    tests/Renderer/UniformBufferTests.cpp
    tests/Renderer/VertexDefinitionTests.cpp
    )

nucleus_add_executable(canvasTests ${canvasTests_SOURCE_FILES})
target_link_libraries(canvasTests canvas Catch2::Catch2)

if (CANVAS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

cmake_minimum_required(VERSION 3.2)

if(TARGET canvas)
    return()
endif()

project("canvas")

# Options

option(CANVAS_BUILD_EXAMPLES "Build canvas examples?" ON)
set(CMAKE_CXX_STANDARD 14)

# Dependencies

include("cmake/nucleus.cmake")
add_subdirectory(third_party "third_party")

# canvas

set(canvas_HEADER_FILES
    "include/canvas/App.h"
    "include/canvas/Math/Common.h"
    "include/canvas/Math/Intersection.h"
    "include/canvas/Math/Mat4.h"
    "include/canvas/Math/Plane.h"
    "include/canvas/Math/Ray.h"
    "include/canvas/Math/Transform.h"
    "include/canvas/Math/Vec2.h"
    "include/canvas/Math/Vec3.h"
    "include/canvas/Math/Vec4.h"
    "include/canvas/OpenGL.h"
    "include/canvas/Renderer/Command.h"
    "include/canvas/Renderer/LineRenderer.h"
    "include/canvas/Renderer/Renderer.h"
    "include/canvas/Renderer/Types.h"
    "include/canvas/Renderer/UniformBuffer.h"
    "include/canvas/Renderer/VertexDefinition.h"
    "include/canvas/Rendering/Font.h"
    "include/canvas/Utils/Color.h"
    "include/canvas/Utils/Geometry.h"
    "include/canvas/Utils/GLCheck.h"
    "include/canvas/Utils/Image.h"
    "include/canvas/Utils/Pos.h"
    "include/canvas/Utils/Rect.h"
    "include/canvas/Utils/ScopedOpenGLEnable.h"
    "include/canvas/Utils/ShaderSource.h"
    "include/canvas/Utils/Size.h"
    "include/canvas/Windows/Event.h"
    "include/canvas/Windows/Keyboard.h"
    "include/canvas/Windows/KeyboardEventHandlerInterface.h"
    "include/canvas/Windows/MouseEventHandlerInterface.h"
    "include/canvas/Windows/Window.h"
    "include/canvas/Windows/WindowDelegate.h"
    "include/canvas/Windows/WindowStyle.h"
    )

set(canvas_SOURCE_FILES
    "src/Math/Mat4.cpp"
    "src/Math/Transform.cpp"
    "src/Renderer/LineRenderer.cpp"
    "src/Renderer/Renderer.cpp"
    "src/Renderer/UniformBuffer.cpp"
    "src/Renderer/VertexDefinition.cpp"
    "src/Rendering/Font.cpp"
    "src/Utils/Color.cpp"
    "src/Utils/Geometry.cpp"
    "src/Utils/GLCheck.cpp"
    "src/Utils/Image.cpp"
    "src/Utils/ShaderSource.cpp"
    "src/Windows/Window.cpp"
    "src/Windows/WindowDelegate.cpp"
    )

add_library(canvas STATIC ${canvas_HEADER_FILES} ${canvas_SOURCE_FILES})
target_link_libraries(canvas PUBLIC nucleus glfw glad libpng zlib)
target_include_directories(canvas PUBLIC "${canvas_SOURCE_DIR}/include")
target_compile_definitions(canvas PUBLIC "-DUNICODE")
set_target_properties(canvas PROPERTIES
    CXX_STANDARD 14
    FOLDER canvas
    )

add_subdirectory(tests "tests")

if(CANVAS_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

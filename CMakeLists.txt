cmake_minimum_required(VERSION 3.2)

if(TARGET canvas)
    return()
endif()

project("canvas")

# Options

option(CANVAS_BUILD_EXAMPLES "Build canvas examples?")
set(CMAKE_CXX_STANDARD 14)

# Dependencies

include("cmake/nucleus.cmake")
add_subdirectory(third_party "third_party")

# canvas

set(canvas_HEADER_FILES
    "include/canvas/App.h"
    "include/canvas/Math/Mat4.h"
    "include/canvas/Math/Ray.h"
    "include/canvas/Math/Transform.h"
    "include/canvas/Math/Vec2.h"
    "include/canvas/Math/Vec3.h"
    "include/canvas/Math/Vec4.h"
    "include/canvas/OpenGL.h"
    "include/canvas/Renderer/BufferDefinition.h"
    "include/canvas/Renderer/RenderCommand.h"
    "include/canvas/Renderer/Renderer.h"
    "include/canvas/Renderer/RenderGroup.h"
    "include/canvas/Renderer/Types.h"
    "include/canvas/Rendering/Font.h"
    "include/canvas/Utils/Color.h"
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
    "src/Renderer/BufferDefinition.cpp"
    "src/Renderer/Renderer.cpp"
    "src/Renderer/RenderGroup.cpp"
    "src/Rendering/Font.cpp"
    "src/Utils/GLCheck.cpp"
    "src/Utils/Image.cpp"
    "src/Utils/ShaderSource.cpp"
    "src/Windows/Window.cpp"
    "src/Windows/WindowDelegate.cpp"
    )

add_library(canvas STATIC ${canvas_HEADER_FILES} ${canvas_SOURCE_FILES})
target_link_libraries(canvas nucleus glfw glad freetype libpng zlib)
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

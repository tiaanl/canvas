cmake_minimum_required(VERSION 3.2)
project("canvas")

# Options

option(CANVAS_BUILD_EXAMPLES "Build canvas examples?")

# Dependencies

include("cmake/nucleus.cmake")
include("cmake/glad.cmake")

# Compiler Settings

include("${NUCLEUS_ROOT_DIR}/cmake/gcc.cmake")
include("${NUCLEUS_ROOT_DIR}/cmake/msvc.cmake")
include("${NUCLEUS_ROOT_DIR}/cmake/win32.cmake")

add_subdirectory(third_party "third_party")

# canvas

set(canvas_HEADER_FILES
    "include/canvas/app.h"
    "include/canvas/math/mat4.h"
    "include/canvas/math/transform.h"
    "include/canvas/math/vec2.h"
    "include/canvas/math/vec3.h"
    "include/canvas/math/vec4.h"
    "include/canvas/opengl.h"
    "include/canvas/rendering/canvas.h"
    "include/canvas/rendering/Command.h"
    "include/canvas/rendering/font.h"
    "include/canvas/rendering/geometry.h"
    "include/canvas/rendering/program.h"
    "include/canvas/rendering/shader.h"
    "include/canvas/Primitives/Sprite.h"
    "include/canvas/Primitives/Text.h"

    "include/canvas/Resources/ResourceManager.h"
    "include/canvas/Resources/TextureResource.h"

    "include/canvas/rendering/texture.h"
    "include/canvas/rendering/vertex.h"
    "include/canvas/rendering/vertex_buffer_object.h"
    "include/canvas/utils/color.h"
    "include/canvas/utils/gl_check.h"
    "include/canvas/utils/image.h"
    "include/canvas/utils/pos.h"
    "include/canvas/utils/rect.h"
    "include/canvas/utils/size.h"
    "include/canvas/utils/ScopedOpenGLEnable.h"
    "include/canvas/windows/event.h"
    "include/canvas/windows/keyboard.h"
    "include/canvas/windows/window.h"
    "include/canvas/windows/window_delegate.h"
    "include/canvas/windows/window_style.h"
    "include/canvas/windows/KeyboardEventHandlerInterface.h"
    "include/canvas/windows/MouseEventHandlerInterface.h"
)

set(canvas_SOURCE_FILES
    "src/app.cpp"

    "src/rendering/canvas.cpp"
    "src/rendering/Command.cpp"
    "src/rendering/font.cpp"
    "src/rendering/geometry.cpp"
    "src/rendering/program.cpp"
    "src/rendering/shader.cpp"

    "src/Resources/ResourceManager.cpp"
    "src/Resources/TextureResource.cpp"

    "src/Primitives/Sprite.cpp"
    "src/Primitives/Text.cpp"
    "src/rendering/texture.cpp"
    "src/rendering/vertex_buffer_object.cpp"
    "src/utils/gl_check.cpp"
    "src/utils/image.cpp"
    "src/windows/window.cpp"
    "src/windows/window_delegate.cpp"
)

add_library(canvas STATIC ${canvas_HEADER_FILES} ${canvas_SOURCE_FILES})
target_link_libraries(canvas nucleus glfw glad freetype libpng zlib)
target_include_directories(canvas PUBLIC "${canvas_SOURCE_DIR}/include")
set_property(TARGET canvas PROPERTY FOLDER canvas)

add_subdirectory(tests "canvas_tests")

if (CANVAS_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

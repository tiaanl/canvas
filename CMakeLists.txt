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
	"include/canvas/Resources/Resource.h"
    "include/canvas/App.h"
    "include/canvas/Math/Mat4.h"
    "include/canvas/Math/Transform.h"
    "include/canvas/Math/Vec2.h"
    "include/canvas/Math/Vec3.h"
    "include/canvas/Math/Vec4.h"
    "include/canvas/OpenGL.h"
    "include/canvas/Primitives/Sprite.h"
    "include/canvas/Primitives/Text.h"
    "include/canvas/Rendering/Canvas.h"
    "include/canvas/Rendering/Command.h"
    "include/canvas/Rendering/Font.h"
    "include/canvas/Rendering/Geometry.h"
    "include/canvas/Rendering/Program.h"
    "include/canvas/Rendering/Shader.h"
    "include/canvas/Rendering/Texture.h"
    "include/canvas/Rendering/Vertex.h"
    "include/canvas/Rendering/VertexBufferObject.h"
    "include/canvas/Resources/ResourceCache.h"
    "include/canvas/Resources/ResourceManager.h"
    "include/canvas/Utils/Color.h"
    "include/canvas/Utils/GLCheck.h"
    "include/canvas/Utils/Image.h"
    "include/canvas/Utils/Pos.h"
    "include/canvas/Utils/Rect.h"
    "include/canvas/Utils/ScopedOpenGLEnable.h"
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
    "src/Primitives/Sprite.cpp"
    "src/Primitives/Text.cpp"
    "src/Rendering/Canvas.cpp"
    "src/Rendering/Command.cpp"
    "src/Rendering/Font.cpp"
    "src/Rendering/Geometry.cpp"
    "src/Rendering/Program.cpp"
    "src/Rendering/Shader.cpp"
    "src/Rendering/Texture.cpp"
    "src/Rendering/VertexBufferObject.cpp"
    "src/Resources/ResourceManager.cpp"
    "src/Utils/GLCheck.cpp"
    "src/Utils/Image.cpp"
    "src/Windows/Window.cpp"
    "src/Windows/WindowDelegate.cpp"
    )

add_library(canvas STATIC ${canvas_HEADER_FILES} ${canvas_SOURCE_FILES})
target_link_libraries(canvas nucleus glfw glad freetype libpng zlib)
target_include_directories(canvas PUBLIC "${canvas_SOURCE_DIR}/include")
set_target_properties(canvas PROPERTIES
    CXX_STANDARD 14
    FOLDER canvas
    )

add_subdirectory(tests "tests")

if(CANVAS_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

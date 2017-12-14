
#ifndef CANVAS_RENDERING_CANVAS_H_
#define CANVAS_RENDERING_CANVAS_H_

#include "canvas/OpenGL.h"
#include "canvas/Rendering/Command.h"
#include "canvas/Utils/Color.h"
#include "canvas/Utils/Size.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"

namespace ca {

class Window;

class Canvas {
public:
  explicit Canvas(Window* window);
  ~Canvas();

  // Get the size of the render area of the canvas.
  ca::Size<I32> getSize() const;

  // Clear the entire surface of the canvas with the specified color.
  void clear(const Color& color);

  Command* render(GLuint program, GLuint vertexArray, GLenum primitiveType, GLint first, GLint count);

  void render();

private:
  // The window we will paint to.
  Window* m_window;

  // All the commands we want to render out.
  nu::DynamicArray<Command> m_commands;

  DISALLOW_COPY_AND_ASSIGN(Canvas);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_CANVAS_H_


#ifndef CANVAS_RENDERING_CANVAS_H_
#define CANVAS_RENDERING_CANVAS_H_

#include "canvas/opengl.h"
#include "canvas/rendering/Command.h"
#include "canvas/utils/color.h"
#include "canvas/utils/size.h"
#include "nucleus/macros.h"

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

  std::vector<Command> m_commands;

  DISALLOW_COPY_AND_ASSIGN(Canvas);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_CANVAS_H_

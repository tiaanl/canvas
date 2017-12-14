
#include "canvas/rendering/canvas.h"

#include "canvas/utils/gl_check.h"
#include "canvas/windows/window.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

Canvas::Canvas(Window* window) : m_window(window) {
  // When the canvas is created, we set the window's context to active.
  m_window->activateContext();
}

Canvas::~Canvas() {}

ca::Size<I32> Canvas::getSize() const {
  DCHECK(m_window);
  return m_window->getClientSize();
}

void Canvas::clear(const Color& color) {
  glClearColor(static_cast<float>(color.r) / 255, static_cast<float>(color.g) / 255, static_cast<float>(color.b) / 255,
               static_cast<float>(color.a) / 255);
  glClear(GL_COLOR_BUFFER_BIT);
}

Command* Canvas::render(GLuint program, GLuint vertexArray, GLenum primitiveType, GLint first, GLint count) {
  // Add a new command.
  m_commands.emplaceBack(program, vertexArray, primitiveType, first, count);

  // Return the command we just added.
  return &m_commands.last();
}

void Canvas::render() {
  for (Command& command : m_commands) {
    command.execute();
  }

  m_commands.clear();
}

}  // namespace ca

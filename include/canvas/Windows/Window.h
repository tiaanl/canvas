
#ifndef CANVAS_WINDOWS_WINDOW_H_
#define CANVAS_WINDOWS_WINDOW_H_

#include "canvas/Debug/DebugInterface.h"
#include "canvas/Renderer/Renderer.h"
#include "canvas/Windows/WindowDelegate.h"
#include "nucleus/Macros.h"
#include "nucleus/Memory/ScopedPtr.h"
#include "nucleus/Text/StringView.h"

typedef struct GLFWwindow GLFWwindow;

namespace ca {

class Window {
public:
  NU_DELETE_COPY_AND_MOVE(Window);

  Window();
  ~Window();

  // Creates the window and initializes the renderer.
  bool initialize(WindowDelegate* delegate);

  // Get the client size of the window.
  const ca::Size& getClientSize() const {
    return m_clientSize;
  }

  Renderer* getRenderer() const {
    return const_cast<Renderer*>(&m_renderer);
  }

  // Process any pending events for this window.  Returns false if the window should stop processing
  // messages.
  bool processEvents();

  // Activate this window's rendering context.
  void activateContext();

  // Request that the window paint it's contents.
  void paint();

private:
  // Callbacks
  static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
  static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
  static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
  static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

  // The window delegate we pass events to.
  WindowDelegate* m_delegate = nullptr;

  // Our internal pointer to the window's implementation.
  GLFWwindow* m_window = nullptr;

  // The renderer we use to render anything to this window.
  Renderer m_renderer;

  // The debug interface we use to render details to the developer.
  DebugInterface m_debugInterface{&m_renderer, {1600, 900}};

  // Size of the client area of the window.
  Size m_clientSize;

  // Last frame's FPS.
  F64 m_lastFPS = 0.0;
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_H_

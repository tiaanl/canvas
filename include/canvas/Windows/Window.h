
#ifndef CANVAS_WINDOWS_WINDOW_H_
#define CANVAS_WINDOWS_WINDOW_H_

#include "WindowDelegate.h"
#include "nucleus/Allocators/Allocator.h"
#include "nucleus/Macros.h"
#include "nucleus/Memory/Allocated.h"

typedef struct GLFWwindow GLFWwindow;

namespace ca {

class Window {
public:
  // Factory function to create a window with the specified delegate.
  static nu::Allocated<Window> create(nu::Allocator* allocator, WindowDelegate* delegate, const std::string& title);

  // Construct a new window with the specified delegate.  Use the static factory function `create` in stead.
  explicit Window(WindowDelegate* delegate);

  // Cleanup.
  ~Window();

  // Get the client size of the window.
  ca::Size<I32> getClientSize() const;

  // Process any pending events for this window.  Returns false if the window
  // should stop processing messages.
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
  WindowDelegate* m_delegate;

  // Our internal pointer to the window's implementation.
  GLFWwindow* m_window;

  DISALLOW_IMPLICIT_CONSTRUCTORS(Window);
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_H_

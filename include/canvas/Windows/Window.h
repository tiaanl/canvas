
#ifndef CANVAS_WINDOWS_WINDOW_H_
#define CANVAS_WINDOWS_WINDOW_H_

#include <memory>

#include "WindowDelegate.h"
#include "canvas/Renderer/RenderContext.h"
#include "nucleus/Allocators/Allocated.h"
#include "nucleus/Allocators/Allocator.h"
#include "nucleus/Macros.h"
#include "nucleus/Memory/ScopedPtr.h"
#include "nucleus/Text/StringView.h"

typedef struct GLFWwindow GLFWwindow;

namespace ca {

class Window {
public:
  COPY_DELETE(Window);
  MOVE_DELETE(Window);

  // Factory function to create a window with the specified delegate.
  static nu::ScopedPtr<Window> create(WindowDelegate* delegate, const nu::StringView& title);

  Window() = delete;

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
  template <typename T, typename... Args>
  friend nu::ScopedPtr<T> nu::makeScopedPtr(Args&&...);

  // Callbacks
  static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
  static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
  static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
  static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

  // Construct a new window with the specified delegate.
  explicit Window(WindowDelegate* delegate);

  // The window delegate we pass events to.
  WindowDelegate* m_delegate;

  // Our internal pointer to the window's implementation.
  GLFWwindow* m_window;

  // RenderContext wrapping the rendering system.
  RenderContext m_renderContext;

  // The renderer we use to render anything to this window.
  Renderer m_renderer;
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_H_

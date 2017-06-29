// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef CANVAS_WINDOWS_WINDOW_H_
#define CANVAS_WINDOWS_WINDOW_H_

#include <memory>

#include "nucleus/macros.h"

#include "canvas/windows/window_delegate.h"

typedef struct GLFWwindow GLFWwindow;

namespace ca {

class Window {
public:
  // Factory function to create a window with the specified delegate.
  static std::unique_ptr<Window> create(WindowDelegate* delegate,
                                        const std::string& title);

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
  // Construct a new window with the specified delegate.
  Window(WindowDelegate* delegate);

  // Callbacks
  static void frameBufferSizeCallback(GLFWwindow* window, int width,
                                      int height);
  static void cursorPositionCallback(GLFWwindow* window, double xpos,
                                     double ypos);
  static void mouseButtonCallback(GLFWwindow* window, int button, int action,
                                  int mods);
  static void scrollCallback(GLFWwindow* window, double xOffset,
                             double yOffset);
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                          int mods);

  // The window delegate we pass events to.
  WindowDelegate* m_delegate;

  // Our internal pointer to the window's implementation.
  GLFWwindow* m_window;

  DISALLOW_IMPLICIT_CONSTRUCTORS(Window);
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_H_

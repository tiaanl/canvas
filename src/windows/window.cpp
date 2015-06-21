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

#include "canvas/windows/window.h"

#include "nucleus/logging.h"
#include "nucleus/types.h"

#include "canvas/opengl.h"
#include "canvas/rendering/canvas.h"

#include <GLFW/glfw3.h>

namespace ca {

namespace {

inline Window* getUserPointer(GLFWwindow* window) {
  return static_cast<Window*>(glfwGetWindowUserPointer(window));
}

}  // namespace

// static
std::unique_ptr<Window> Window::create(WindowDelegate* delegate,
                                       const std::string& title) {
  DCHECK(delegate) << "Can't create a window with no delegate.";

  auto newWindow = std::unique_ptr<Window>(new Window(delegate));

  // Initialize GLFW.
  if (!glfwInit()) {
    return nullptr;
  }

  // Create the window.
  newWindow->m_window = glfwCreateWindow(800, 480, delegate->getTitle().c_str(),
                                         nullptr, nullptr);

  // Set up the callbacks for the window.
  glfwSetWindowUserPointer(newWindow->m_window, newWindow.get());
  glfwSetFramebufferSizeCallback(newWindow->m_window, frameBufferSizeCallback);
  glfwSetCursorPosCallback(newWindow->m_window, cursorPositionCallback);
  glfwSetMouseButtonCallback(newWindow->m_window, mouseButtonCallback);

  // Make the new window the current context.
  glfwMakeContextCurrent(newWindow->m_window);

  // Enable v-sync.
  glfwSwapInterval(1);

  // Initialize glad, so we can use GL extensions.
  gladLoadGL();

  // Let the delegate know we were just created.
  delegate->onWindowCreated();

  // We send a window resized to the delegate as well so that it can do any
  // setup needed.
  Size<u32> clientSize{800, 480};
  delegate->onWindowResized(clientSize);

  return newWindow;
}

Window::~Window() {
  glfwDestroyWindow(m_window);

  glfwTerminate();
}

bool Window::processEvents() {
  // Handle events...
  glfwPollEvents();

  // ...and tell the caller if event processing should continue or not.
  return !glfwWindowShouldClose(m_window);
}

void Window::activateContext() {
  glfwMakeContextCurrent(m_window);
}

void Window::paint() {
  // Create the canvas we will be painting on.
  Canvas canvas(this);

  // Tell the delegate to paint.
  m_delegate->onPaint(&canvas);

  // Swap buffers.
  glfwSwapBuffers(m_window);
}

Window::Window(WindowDelegate* delegate) : m_delegate(delegate) {
}

// static
void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  Window* windowPtr = getUserPointer(window);

  // We set up the viewport for the window before letting the delegate know the
  // size changed.
  glViewport(0, 0, width, height);

  Size<u32> windowSize(width, height);
  windowPtr->m_delegate->onWindowResized(windowSize);
}

// static
void Window::cursorPositionCallback(GLFWwindow* window, double xPos,
                                    double yPos) {
  Window* windowPtr = getUserPointer(window);

  // Send the event to the delegate.
  Pos<i32> mousePos{static_cast<i32>(std::round(xPos)),
                    static_cast<i32>(std::round(yPos))};
  MouseEvent evt{Event::MouseMoved, mousePos};
  windowPtr->m_delegate->onMouseMoved(evt);
}

// static
void Window::mouseButtonCallback(GLFWwindow* window, int button, int action,
                                 int mods) {
  Window* windowPtr = getUserPointer(window);

  double xPos, yPos;
  glfwGetCursorPos(window, &xPos, &yPos);
  Pos<i32> mousePos{static_cast<i32>(std::round(xPos)),
                    static_cast<i32>(std::round(yPos))};

  if (action == GLFW_PRESS) {
    MouseEvent evt{Event::MousePressed, mousePos};
    windowPtr->m_delegate->onMousePressed(evt);
  } else if (action == GLFW_RELEASE) {
    MouseEvent evt{Event::MouseReleased, mousePos};
    windowPtr->m_delegate->onMouseReleased(evt);
  }
}

}  // namespace ca

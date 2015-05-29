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

#include <GL/glew.h>

#include "nucleus/logging.h"
#include "nucleus/types.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"

#include "canvas/rendering/canvas.h"

namespace ca {

#define IMPL static_cast<sf::Window*>(m_impl)

// static
std::unique_ptr<Window> Window::create(WindowDelegate* delegate,
                                       const std::string& title) {
  DCHECK(delegate) << "Can't create a window with no delegate.";

  auto newWindow = std::unique_ptr<Window>(new Window(delegate));

  sf::ContextSettings settings{0u, 0u, 0u, 3u, 1u, sf::ContextSettings::Core};

  // Create the implementation of the window.
  newWindow->m_impl = new sf::Window{sf::VideoMode{800, 480, 32}, title,
                                     sf::Style::Default, settings};

  // Once a window is created, we have to make sure then GLEW is initialized.
  static bool glewInitialized = false;
  if (!glewInitialized) {
    glewInitialized = true;
    glewInit();
  }

  // Let the delegate know we were just created.
  delegate->onWindowCreated();

  // We send a window resized to the delegate as well so that it can do any
  // setup needed.
  Size<u32> clientSize{800, 480};
  delegate->onWindowResized(clientSize);

  return newWindow;
}

Window::~Window() {
}

bool Window::isOpen() const {
  return IMPL->isOpen();
}

void Window::processEvents() {
  sf::Event sfEvent;
  while (IMPL->pollEvent(sfEvent)) {
    switch (sfEvent.type) {
      case sf::Event::Closed:
        IMPL->close();
        break;

      case sf::Event::Resized: {
        Size<u32> clientSize{sfEvent.size.width, sfEvent.size.height};
        glViewport(0, 0, clientSize.width, clientSize.height);
        m_delegate->onWindowResized(clientSize);
      } break;

      case sf::Event::MouseMoved: {
        MouseEvent event{Event::MouseMoved, Pos<i32>{sfEvent.mouseMove.x,
                                                         sfEvent.mouseMove.y}};
        m_delegate->onMouseMoved(event);
      } break;

      case sf::Event::MouseButtonPressed: {
        MouseEvent event{
            Event::MousePressed,
            Pos<i32>{sfEvent.mouseButton.x, sfEvent.mouseButton.y}};
        m_delegate->onMousePressed(event);
      } break;

      case sf::Event::MouseButtonReleased: {
        MouseEvent event{
            Event::MouseReleased,
            Pos<i32>{sfEvent.mouseButton.x, sfEvent.mouseButton.y}};
        m_delegate->onMousePressed(event);
      } break;

      default:
        break;
    }
  }
}

void Window::activateContext() {
  IMPL->setActive(true);
}

void Window::paint() {
  // Create the canvas we will be painting on.
  Canvas canvas(this);

  // Tell the delegate to paint.
  m_delegate->onPaint(&canvas);

  // Swap buffers.
  IMPL->display();
}

Window::Window(WindowDelegate* delegate) : m_delegate(delegate) {
}

}  // namespace ca
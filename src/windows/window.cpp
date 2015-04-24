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

#include <nucleus/logging.h>

namespace ca {

namespace {

Window* g_fullscreenWindow = nullptr;

}  // namespace

Window::Window() {
}

Window::Window(VideoMode mode, const std::string& title, uint32_t style,
               const ContextSettings& settings) {
  create(mode, title, style, settings);
}

Window::Window(WindowHandle handle, const ContextSettings& settings) {
  create(handle, settings);
}

Window::~Window() {
  close();
}

void Window::create(VideoMode mode, const std::string& title, uint32_t style,
                    const ContextSettings& settings) {
  // Destroy the previous window.
  close();

  // Fullscreen style required some tests.
  if (IS_BIT_SET(style, WindowStyleFullscreen)) {
    // Make sure there isn't already a fullscreen window.  (only one is allowed)
    if (g_fullscreenWindow) {
      LOG(Error) << "Creating two fullscreen windows is not allowed, switching "
                    "to windowed mode.";
      style &= ~WindowStyleFullscreen;
    } else {
      // Make sure that the chosed video mode is compatible.
      if (!mode.isValid()) {
        LOG(Error) << "The requested video mode is not available, switching to "
                      "a valid mode.";
        mode = VideoMode::getFullscreenModes()[0];
      }

      // Update the fullscreen window.
      g_fullscreenWindow = this;
    }
  }

// Check the validity of the style according to the underlying platform.
#if OS(IOS) || OS(ANDROID)
  if (IS_BIT_SET(style, WindowStyleFullscreen)) {
    style &= ~WindowStyleTitleBar;
  } else {
    style |= Style::TitleBar;
  }
#else
  if (IS_BIT_SET(style, WindowStyleClose) ||
      IS_BIT_SET(style, WindowStyleResize)) {
    style |= WindowStyleTitleBar;
  }
#endif

  // Recreate the window.
  m_detail =
      std::move(detail::WindowDetail::create(mode, title, style, settings));

  // Recreate the context.

  // Perform common initializations.
  initialize();
}

void Window::create(WindowHandle handle, const ContextSettings& settings) {
  // Destroy the previous window implementation.
  close();

  // Recreate the window implementation.
  m_detail = std::move(detail::WindowDetail::create(handle));

  // Recreate the context.

  // Perform common initializations.
  initialize();
}

void Window::close() {
  // Delete the context.
  // m_context.reset();

  // Delete the window detail.
  m_detail.reset();

  // Update the fullscreen window.
  if (this == g_fullscreenWindow) {
    g_fullscreenWindow = nullptr;
  }
}

bool Window::isOpen() const {
  return !!m_detail;
}

const ContextSettings& Window::getContextSettings() const {
  static const ContextSettings empty;
#if 0
  return m_context ? m_context->getSettings() : empty;
#else
  return empty;
#endif
}

Pos<int32_t> Window::getPosition() const {
  return m_detail ? m_detail->getPosition() : Pos<int32_t>();
}

void Window::setPosition(const Pos<int32_t>& pos) {
  if (m_detail) {
    m_detail->setPosition(pos);
  }
}

Size<uint32_t> Window::getSize() const {
  return m_size;
}

void Window::setSize(const Size<uint32_t>& size) {
  if (m_detail) {
    m_detail->setSize(size);

    // Cache the new size.
    m_size = size;

    // Notify the derived class.
    onResize();
  }
}

void Window::setTitle(const std::string& title) {
  if (m_detail) {
    m_detail->setTitle(title);
  }
}

void Window::setVisible(bool visible) {
  if (m_detail) {
    m_detail->setVisible(visible);
  }
}

void Window::setVerticalSyncEnabled(bool enabled) {
#if 0
  if (m_detail) {
    m_context->setVerticalSyncEnabled(enabled);
  }
#endif  // 0
}

void Window::setMouseCursorVisible(bool visible) {
  if (m_detail) {
    m_detail->setMouseCursorVisible(visible);
  }
}

void Window::setKeyRepeatEnabled(bool enabled) {
  if (m_detail) {
    m_detail->setKeyRepeatEnabled(enabled);
  }
}

bool Window::setActive(bool active) {
#if 0
  if (m_context) {
    if (m_context->setActive(active)) {
      return true;
    } else {
      LOG(Error) << "Failed to activate the window's context.";
      return false;
    }
  } else {
    return false;
  }
#endif  // 0
  return false;
}

void Window::requestFocus() {
  if (m_detail) {
    m_detail->requestFocus();
  }
}

bool Window::hasFocus() const {
  return m_detail && m_detail->hasFocus();
}

void Window::swapBuffers() {
  // Display the back buffer on screen.
  if (setActive(true)) {
#if 0
    m_context->swapBuffers();
#endif  // 0
  }
}

WindowHandle Window::getNativeHandle() const {
  return m_detail ? m_detail->getNativeHandle() : 0;
}

void Window::onCreate() {
  // No default behaviour.
}

void Window::onResize() {
  // No default behaviour.
}

void Window::initialize() {
  // Set up default behaviours to get a consistent behaviour across different
  // OS's.
  setVisible(true);
  setMouseCursorVisible(true);
  setVerticalSyncEnabled(false);
  setKeyRepeatEnabled(true);

  // Get and cache the initial size of the window.
  m_size = m_detail->getSize();

  // Activate the window.
  setActive(true);

  // Notify the derived classes.
  onCreate();
}

}  // namespace ca

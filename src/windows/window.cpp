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

void Window::create(VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings) {
  // Destroy the previous window.
  close();

  // Fullscreen style required some tests.
  if (IS_BIT_SET(style, WindowStyleFullscreen)) {
    // Make sure there isn't already a fullscreen window.  (only one is allowed)
    if (g_fullscreenWindow) {
      LOG(Error) << "Creating two fullscreen windows is not allowed, switching to windowed mode.";
      style &= ~WindowStyleFullscreen;
    } else {
      // Make sure that the chosed video mode is compatible.
      if (!mode.isValid()) {
        LOG(Error) << "The requested video mode is not available, switching to a valid mode.";
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
  if (IS_BIT_SET(style, WindowStyleClose) || IS_BIT_SET(style, WindowStyleResize)) {
    style |= WindowStyleTitleBar;
  }
#endif

  // Create the window.

  // Recreate the context.

  // Perform common initializations.
  initialize();
}

}  // namespace ca

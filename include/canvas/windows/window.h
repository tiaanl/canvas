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

namespace ca {

class Window {
public:
  // Factory function to create a window with the specified delegate.
  static std::unique_ptr<Window> create(WindowDelegate* delegate,
                                        const std::string& title);

  // Cleanup.
  ~Window();

  // Returns true if this window is still open and on the screen.
  bool isOpen() const;

  // Process any pending events for this window.
  void processEvents();

  // Activate this window's rendering context.
  void activateContext();

  // Request that the window paint it's contents.
  void paint();

private:
  // Construct a new window with the specified delegate.
  Window(WindowDelegate* delegate);

  // The window delegate we pass events to.
  WindowDelegate* m_delegate;

  // Our internal pointer to the window's implementation.
  void* m_impl{nullptr};

  DISALLOW_IMPLICIT_CONSTRUCTORS(Window);
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_H_

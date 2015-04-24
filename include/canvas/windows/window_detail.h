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

#ifndef CANVAS_WINDOWS_WINDOW_DETAIL_H_
#define CANVAS_WINDOWS_WINDOW_DETAIL_H_

#include <memory>

#include "canvas/utils/pos.h"
#include "canvas/utils/size.h"
#include "canvas/windows/context_settings.h"
#include "canvas/windows/video_mode.h"
#include "canvas/windows/window_handle.h"

namespace ca {

namespace detail {

class WindowDetail {
public:
  // Create a new window depending on the current OS.
  static std::unique_ptr<WindowDetail> create(VideoMode mode,
                                              const std::string& title,
                                              uint32_t style,
                                              const ContextSettings& settings);

  // Create a new window from an existing native handle, depending on the
  // current OS.
  static std::unique_ptr<WindowDetail> create(WindowHandle handle);

  virtual ~WindowDetail();

  // Get the OS-specific handle of the window.
  virtual WindowHandle getNativeHandle() const = 0;

  // Get the position of the window.
  virtual Pos<int32_t> getPosition() const = 0;

  // Set the position of the window on screen.
  virtual void setPosition(const Pos<int32_t>& position) = 0;

  // Get the client size of the window.
  virtual Size<uint32_t> getSize() const = 0;

  // Set the size of the rendering region of the window.
  virtual void setSize(const Size<uint32_t>& size) = 0;

  // Set the title of the window.
  virtual void setTitle(const std::string& title) = 0;

  // Show or hide the window.
  virtual void setVisible(bool visible) = 0;

  // Show or hide the mouse cursor.
  virtual void setMouseCursorVisible(bool visible) = 0;

  // Enable or disable automatic key-repeat.
  virtual void setKeyRepeatEnabled(bool enabled) = 0;

  // Request the current window to be made the active foreground window.
  virtual void requestFocus() = 0;

  // Check whether this window has input focus.
  virtual bool hasFocus() const = 0;

protected:
  WindowDetail();
};

}  // namespace detail

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_DETAIL_H_

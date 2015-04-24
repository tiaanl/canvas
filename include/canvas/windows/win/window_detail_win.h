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

#ifndef CANVAS_WINDOWS_WIN_WINDOW_DETAIL_WIN_H_
#define CANVAS_WINDOWS_WIN_WINDOW_DETAIL_WIN_H_

#include <nucleus/macros.h>
#include <nucleus/win/windows_mixin.h>

#include "canvas/windows/window_detail.h"

namespace ca {
 
namespace detail {

class WindowDetailWin : public WindowDetail {
public:
  // Create the window.
  WindowDetailWin(VideoMode mode, const std::string& title, uint32_t style,
                  const ContextSettings& settings);

  // Construct the window from an existing native handle.
  WindowDetailWin(WindowHandle handle);

  ~WindowDetailWin() override;

  // Override: WindowDetail
  WindowHandle getNativeHandle() const override;
  Pos<int32_t> getPosition() const override;
  void setPosition(const Pos<int32_t>& pos) override;
  Size<uint32_t> getSize() const override;
  void setSize(const Size<uint32_t>& size) override;
  void setTitle(const std::string& title) override;
  void setVisible(bool visible) override;
  void setMouseCursorVisible(bool visible) override;
  void setKeyRepeatEnabled(bool enabled) override;
  void requestFocus() override;
  bool hasFocus() const override;

private:
  // Register the window class.
  void registerWindowClass();

  // Switch to fullscreen more.
  void switchToFullscreen(const VideoMode& mode);

  // Free all the graphical resources attached to the window.
  void cleanup();

  // Process a WIN32 event.
  void processEvent(UINT message, WPARAM wParam, LPARAM lParam);

  // Enable or disable tracking for the mouse cursor leaving the window.
  void setMouseTracking(bool track);

  // Convert a WIN32 virtual key code to an internal key code.
#if 0
  static Keyboard::Key virtualKeyCodeToInternalKeyCode(WPARAM key,
                                                       LPARAM flags);
#endif  // 0

  // Message callback that will receive all WIN32 messages.
  static LRESULT CALLBACK
  onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

  // WIN32 handle of the window.
  HWND m_handle = nullptr;

  // Stores the original event callback function of the window.
  LONG_PTR m_callback = 0;

  // Automatic key-repeat state for keydown events.
  bool m_keyRepeatEnabled = true;

  // The last handled size of the window.
  Size<uint32_t> m_lastSize;

  // Whether the window is being resized or not.
  bool m_isResizing = false;

  // First half of the currogate pair, in case we're receiving a unicode
  // character in two events.
  uint16_t m_surrogate = 0;

  // Mouse is inside the window?
  bool m_mouseInside = false;

  DISALLOW_IMPLICIT_CONSTRUCTORS(WindowDetailWin);
};

}  // namespace detail

}  // namespace ca

#endif  // CANVAS_WINDOWS_WIN_WINDOW_DETAIL_WIN_H_

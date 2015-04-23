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

#include <nucleus/macros.h>

#include "canvas/utils/pos.h"
#include "canvas/utils/size.h"
#include "canvas/windows/context_settings.h"
#include "canvas/windows/video_mode.h"
#include "canvas/windows/window_handle.h"
#include "canvas/windows/window_style.h"

namespace ca {

class Window {
public:
  Window();

  // Construct a new window with the specified settings.
  Window(VideoMode mode, const std::string& title,
         uint32_t style = WindowStyleDefault,
         const ContextSettings& settings = ContextSettings());

  // Construct a new window from an existing native window handle, with optional
  // settings.
  explicit Window(WindowHandle handle,
                  const ContextSettings& settings = ContextSettings());

  // Destruct the window.
  ~Window();

  // Create or recreate the window.
  void create(VideoMode mode, const std::string& title,
              uint32_t style = WindowStyle::WindowStyleDefault,
              const ContextSettings& settings = ContextSettings());

  // Create or recreate the window from an existing native window handle, with
  // optional settings.
  void create(WindowHandle handle,
              const ContextSettings& settings = ContextSettings());

  // Close the window and destroy all the attached resources.
  void close();

  // Return true if the window is open.
  bool isOpen() const;

  // Get the settings of the OpenGL context of the window.
  const ContextSettings& getContextSettings() const;

  // Pop the event on top of the event queue, if any, and return it.
  // bool pollEvent(Event& event);

  // Wait for an event and return it.
  // bool waitEvent(Event& event);

  // Get the position of the window.
  Pos<int32_t> getPosition() const;

  // Set the position of the window on the screen.
  void setPosition(const Pos<int32_t>& pos);

  // Get the size of the rendering region of the window.
  Size<uint32_t> getSize() const;

  // Set the size of the rendering region of the window.
  void setSize(const Size<uint32_t>& size);

  // Set the title of the window.
  void setTitle(const std::string& title);

  // Show or hide the window.
  void setVisible(bool visible);

  // Enable or disable vertical sync on this window.
  void setVerticalSyncEnabled(bool enabled);

  // Show or hide the mouse cursor.
  void setMouseCursorVisible(bool visible);

  // Enable or disable automatic key-repeat.
  void setKeyRepeatEnabled(bool enabled);

  // Activate or deactivate the window as the current target for OpenGL
  // rendering.
  bool setActive(bool active);

  // Request the current window to be made the active foreground window.
  void requestFocus();

  // Check whether this window has the input focus.
  bool hasFocus() const;

  // Swap the OpenGL rendering buffer with the buffer that is currently
  // displaying on the screen.  Draw!
  void swapBuffers();

  // Get the native window handle of this window.
  WindowHandle getNativeHandle() const;

private:
  // Function called after the window has been created.
  void onCreate();

  // Function called after the window has been resized.
  void onResize();

  // Processes an event before it is sent to the user.
  // bool filterEvent(const Event& event);

  // Perform some common internal initializations.
  void initialize();

  // Platform-specific implemantation of the OpenGL context.
  // std::unique_ptr<GlContext> m_context;

  // Current size of the window.
  Size<uint32_t> m_size;

  DISALLOW_COPY_AND_ASSIGN(Window);
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_H_

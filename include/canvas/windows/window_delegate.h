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

#ifndef CANVAS_WINDOWS_WINDOW_DELEGATE_H_
#define CANVAS_WINDOWS_WINDOW_DELEGATE_H_

#include "nucleus/macros.h"

#include "canvas/utils/size.h"
#include "canvas/windows/event.h"

namespace ca {

class Canvas;

class WindowDelegate {
public:
  WindowDelegate() = default;

  virtual ~WindowDelegate() {}

  // Get the title of the window.
  const std::string& getTitle() const { return m_title; }

  // Called right after the window was created.  Return false if the app
  // creation failed.
  virtual bool onWindowCreated();

  // Called when the size of the window changed.
  virtual void onWindowResized(const Size<u32>& size);

  // Called when the window wants to paint to it's canvas.
  virtual void onPaint(Canvas* canvas) = 0;

  // Mouse events.
  virtual void onMouseMoved(const MouseEvent& evt);
  virtual void onMousePressed(const MouseEvent& evt);
  virtual void onMouseReleased(const MouseEvent& evt);
  virtual void onMouseWheel(const MouseWheelEvent& evt);
  virtual void onKeyPressed(const KeyEvent& evt);
  virtual void onKeyReleased(const KeyEvent& evt);

protected:
  // The title that appears in the window title bar.
  std::string m_title;//{"Canvas Window"};

private:
  DISALLOW_COPY_AND_ASSIGN(WindowDelegate);
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_DELEGATE_H_

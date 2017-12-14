
#ifndef CANVAS_WINDOWS_WINDOW_DELEGATE_H_
#define CANVAS_WINDOWS_WINDOW_DELEGATE_H_

#include "nucleus/Macros.h"

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

  // Called right after the window was created.  Return false if the app creation failed.
  virtual bool onWindowCreated();

  // Called when the size of the window changed.
  virtual void onWindowResized(const Size<U32>& size);

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
  std::string m_title;

private:
  DISALLOW_COPY_AND_ASSIGN(WindowDelegate);
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_DELEGATE_H_

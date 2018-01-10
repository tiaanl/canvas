
#ifndef CANVAS_WINDOWS_WINDOW_DELEGATE_H_
#define CANVAS_WINDOWS_WINDOW_DELEGATE_H_

#include <string>

#include "canvas/Utils/Size.h"
#include "canvas/Windows/Event.h"
#include "nucleus/Macros.h"
#include "nucleus/Text/String.h"

namespace ca {

class Canvas;

class WindowDelegate {
public:
  explicit WindowDelegate(const std::string& title) : m_title(title) {}

  virtual ~WindowDelegate() = default;

  // Get the title of the window.
  const std::string& getTitle() const {
    return m_title;
  }

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
  nu::Allocator* m_allocator;

  // The title that appears in the window title bar.
  std::string m_title;

private:
  COPY_DELETE(WindowDelegate);
  MOVE_DELETE(WindowDelegate);
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_DELEGATE_H_

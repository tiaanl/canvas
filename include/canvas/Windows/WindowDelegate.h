
#ifndef CANVAS_WINDOWS_WINDOW_DELEGATE_H_
#define CANVAS_WINDOWS_WINDOW_DELEGATE_H_

#include "canvas/Utils/Size.h"
#include "canvas/Windows/Event.h"
#include "nucleus/Macros.h"
#include "nucleus/Text/StaticString.h"

#include <string>

namespace ca {

class Renderer;

class WindowDelegate {
public:
  explicit WindowDelegate(const nu::StringView& title) : m_title(title) {}

  virtual ~WindowDelegate() = default;

  // Get the title of the window.
  nu::StringView getTitle() const {
    return nu::StringView{m_title.getData(), m_title.getLength()};
  }

  // Called right after the window was created.  Return false if the app creation failed.
  virtual bool onWindowCreated(Renderer* renderContext);

  // Called when the size of the window changed.
  virtual void onWindowResized(const Size& size);

  virtual void onRender(Renderer* renderer) = 0;

  // Mouse events.
  virtual void onMouseMoved(const MouseEvent& evt);
  virtual void onMousePressed(const MouseEvent& evt);
  virtual void onMouseReleased(const MouseEvent& evt);
  virtual void onMouseWheel(const MouseWheelEvent& evt);
  virtual void onKeyPressed(const KeyEvent& evt);
  virtual void onKeyReleased(const KeyEvent& evt);

protected:
  // The title that appears in the window title bar.
  nu::StaticString<128> m_title;

private:
  DELETE_COPY_AND_MOVE(WindowDelegate);
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_DELEGATE_H_

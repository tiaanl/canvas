
#ifndef CANVAS_WINDOWS_MOUSE_EVENT_HANDLER_H_
#define CANVAS_WINDOWS_MOUSE_EVENT_HANDLER_H_

#include "Event.h"

namespace ca {

class MouseEventHandlerInterface {
public:
  virtual void onMouseMoved(const MouseEvent& evt) = 0;
  virtual bool onMousePressed(const MouseEvent& evt) = 0;
  virtual void onMouseReleased(const MouseEvent& evt) = 0;
  virtual void onMouseWheel(const MouseWheelEvent& evt) = 0;
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_MOUSE_EVENT_HANDLER_H_

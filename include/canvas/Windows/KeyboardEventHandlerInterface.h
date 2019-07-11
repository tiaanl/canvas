
#ifndef CANVAS_WINDOWS_KEYBOARD_EVENT_HANDLER_H_
#define CANVAS_WINDOWS_KEYBOARD_EVENT_HANDLER_H_

#include "Event.h"

namespace ca {

class KeyboardEventHandlerInterface {
public:
  virtual void onKeyPressed(const KeyEvent& evt) = 0;
  virtual void onKeyReleased(const KeyEvent& evt) = 0;
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_KEYBOARD_EVENT_HANDLER_H_

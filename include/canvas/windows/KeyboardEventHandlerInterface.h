
#ifndef CANVAS_WINDOWS_KEYBOARDVENTHANDLER_H_
#define CANVAS_WINDOWS_KEYBOARDVENTHANDLER_H_

#include "canvas/windows/event.h"

namespace ca {

class KeyboardEventHandlerInterface {
public:
  virtual void onKeyPressed(const KeyEvent& evt) = 0;
  virtual void onKeyReleased(const KeyEvent& evt) = 0;
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_KEYBOARDVENTHANDLER_H_

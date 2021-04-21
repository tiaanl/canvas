#pragma once

#include "Event.h"

namespace ca {

class KeyboardEventHandlerInterface {
public:
  virtual void on_key_pressed(const KeyEvent& evt) = 0;
  virtual void on_key_released(const KeyEvent& evt) = 0;
};

}  // namespace ca

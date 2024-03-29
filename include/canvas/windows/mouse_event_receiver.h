#pragma once

#include "canvas/windows/event.h"

namespace ca {

class MouseEventReceiver {
public:
  virtual void on_mouse_moved(const MouseEvent& evt) = 0;
  virtual bool on_mouse_pressed(const MouseEvent& evt) = 0;
  virtual void on_mouse_released(const MouseEvent& evt) = 0;
  virtual void on_mouse_wheel(const MouseWheelEvent& evt) = 0;
};

}  // namespace ca

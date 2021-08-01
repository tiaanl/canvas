
#include "canvas/windows/window_delegate.h"

namespace ca {

class Window;

bool WindowDelegate::on_window_created(Window* window) {
  return true;
}

void WindowDelegate::on_tick(F32 delta) {}

void WindowDelegate::on_window_resized(const fl::Size& size) {}

void WindowDelegate::on_mouse_moved(const MouseEvent& evt) {
  for (auto handler : mouse_input_handlers_) {
    handler->on_mouse_moved(evt);
  }
}

bool WindowDelegate::on_mouse_pressed(const MouseEvent& evt) {
  for (auto handler : mouse_input_handlers_) {
    handler->on_mouse_pressed(evt);
  }

  return false;
}

void WindowDelegate::on_mouse_released(const MouseEvent& evt) {
  for (auto handler : mouse_input_handlers_) {
    handler->on_mouse_released(evt);
  }
}

void WindowDelegate::on_mouse_wheel(const MouseWheelEvent& evt) {
  for (auto handler : mouse_input_handlers_) {
    handler->on_mouse_wheel(evt);
  }
}

void WindowDelegate::on_key_pressed(const KeyEvent& evt) {
  for (auto handler : keyboard_input_handlers_) {
    handler->on_key_pressed(evt);
  }
}

void WindowDelegate::on_key_released(const KeyEvent& evt) {
  for (auto handler : keyboard_input_handlers_) {
    handler->on_key_released(evt);
  }
}

void WindowDelegate::add_mouse_event_receiver(MouseEventReceiver* handler) {
  mouse_input_handlers_.emplaceBack(handler);
}

void WindowDelegate::remove_mouse_event_receiver(MouseEventReceiver* handler) {
  mouse_input_handlers_.remove(handler);
}

void WindowDelegate::add_keyboard_event_receiver(KeyboardEventReceiver* handler) {
  keyboard_input_handlers_.emplaceBack(handler);
}

void WindowDelegate::remove_keyboard_event_receiver(KeyboardEventReceiver* handler) {
  keyboard_input_handlers_.remove(handler);
}

}  // namespace ca

#pragma once

#include <floats/size.h>
#include <nucleus/containers/dynamic_array.h>
#include <nucleus/macros.h>
#include <nucleus/text/static_string.h>

#include <string>

#include "canvas/windows/event.h"
#include "canvas/windows/keyboard_event_receiver.h"
#include "canvas/windows/mouse_event_receiver.h"

namespace ca {

class Renderer;
class Window;

class WindowDelegate : public MouseEventReceiver, public KeyboardEventReceiver {
  NU_DELETE_COPY_AND_MOVE(WindowDelegate);

public:
  explicit WindowDelegate(nu::StringView title) : title_(title) {}

  virtual ~WindowDelegate() = default;

  // Get the title of the window.
  NU_NO_DISCARD nu::StringView title() const {
    return title_.view();
  }

  // Called right after the window was created.  Return false if the app creation failed.
  virtual bool on_window_created(Window* window);

  // Called when the size of the window changed.
  virtual void on_window_resized(const fl::Size& size);

  // Called on every frame, delta being the ratio to get to 60 fps.
  virtual void on_tick(F32 delta);

  virtual void on_render(Renderer* renderer) = 0;

  void add_mouse_event_receiver(MouseEventReceiver* handler);
  void remove_mouse_event_receiver(MouseEventReceiver* handler);

  void add_keyboard_event_receiver(KeyboardEventReceiver* handler);
  void remove_keyboard_event_receiver(KeyboardEventReceiver* handler);

  // Override: MouseEventReceiver
  void on_mouse_moved(const MouseEvent& evt) override;
  bool on_mouse_pressed(const MouseEvent& evt) override;
  void on_mouse_released(const MouseEvent& evt) override;
  void on_mouse_wheel(const MouseWheelEvent& evt) override;

  // Override: KeyboardEventReceiver
  void on_key_pressed(const KeyEvent& evt) override;
  void on_key_released(const KeyEvent& evt) override;

protected:
  // The title that appears in the window title bar.
  nu::StaticString<128> title_;

  // A list of mouse input listeners.
  nu::DynamicArray<MouseEventReceiver*> mouse_input_handlers_;

  // A List of keyboard input listeners.
  nu::DynamicArray<KeyboardEventReceiver*> keyboard_input_handlers_;
};

}  // namespace ca


#ifndef CANVAS_WINDOWS_WINDOW_DELEGATE_H_
#define CANVAS_WINDOWS_WINDOW_DELEGATE_H_

#include <string>

#include "canvas/Windows/Event.h"
#include "canvas/Windows/keyboard_event_handler_interface.h"
#include "canvas/Windows/mouse_event_handler_interface.h"
#include "floats/Size.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"
#include "nucleus/Text/StaticString.h"

namespace ca {

class Renderer;
class Window;

class WindowDelegate : public MouseEventHandlerInterface, public KeyboardEventHandlerInterface {
  NU_DELETE_COPY_AND_MOVE(WindowDelegate);

public:
  explicit WindowDelegate(nu::StringView title) : m_title(title) {}

  virtual ~WindowDelegate() = default;

  // Get the title of the window.
  nu::StringView getTitle() const {
    return m_title.view();
  }

  // Called right after the window was created.  Return false if the app creation failed.
  virtual bool onWindowCreated(Window* window);

  // Called when the size of the window changed.
  virtual void onWindowResized(const fl::Size& size);

  // Called on every frame, delta being the ratio to get to 60 fps.
  virtual void tick(F32 delta);

  virtual void onRender(Renderer* renderer) = 0;

  void add_mouse_event_handler(MouseEventHandlerInterface* handler);
  void remove_mouse_event_handler(MouseEventHandlerInterface* handler);

  void add_keyboard_event_handler(KeyboardEventHandlerInterface* handler);
  void remove_keyboard_event_handler(KeyboardEventHandlerInterface* handler);

  // Override: MouseEventHandlerInterface
  void on_mouse_moved(const MouseEvent& evt) override;
  bool on_mouse_pressed(const MouseEvent& evt) override;
  void on_mouse_released(const MouseEvent& evt) override;
  void on_mouse_wheel(const MouseWheelEvent& evt) override;

  // Override: KeyboardEventHandlerInterface
  void on_key_pressed(const KeyEvent& evt) override;
  void on_key_released(const KeyEvent& evt) override;

protected:
  // The title that appears in the window title bar.
  nu::StaticString<128> m_title;

  // A list of mouse input listeners.
  nu::DynamicArray<MouseEventHandlerInterface*> mouse_input_handlers_;

  // A List of keyboard input listeners.
  nu::DynamicArray<KeyboardEventHandlerInterface*> keyboard_input_handlers_;
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_DELEGATE_H_

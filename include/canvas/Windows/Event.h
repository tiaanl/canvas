
#ifndef CANVAS_WINDOWS_EVENT_H_
#define CANVAS_WINDOWS_EVENT_H_

#include "Keyboard.h"
#include "floats/Pos.h"
#include "nucleus/Types.h"

namespace ca {

struct Event {
  enum Type {
    MouseMoved,
    MousePressed,
    MouseDragged,
    MouseReleased,
    MouseWheel,
    KeyPressed,
    KeyReleased,
  };

  Type type;

  Event(Type type) : type(type) {}
};

struct KeyEvent : Event {
  Key key;

  KeyEvent(Type type, Key key) : Event(type), key(key) {}
};

struct PositionEvent : Event {
  fl::Pos pos;

  PositionEvent(Type type, const fl::Pos& pos) : Event(type), pos(pos) {}
};

struct MouseEvent : PositionEvent {
  enum class Button : U32 {
    None,
    Left,
    Middle,
    Right,
  } button;

  MouseEvent(Type type, const fl::Pos& pos, Button button)
    : PositionEvent(type, pos), button(button) {}
};

struct MouseWheelEvent : PositionEvent {
  fl::Pos wheelOffset;

  MouseWheelEvent(Type type, const fl::Pos& pos, fl::Pos& wheelOffset)
    : PositionEvent(type, pos), wheelOffset(wheelOffset) {}
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_EVENT_H_

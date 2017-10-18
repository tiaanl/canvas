
#ifndef CANVAS_WINDOWS_EVENT_H_
#define CANVAS_WINDOWS_EVENT_H_

#include "nucleus/types.h"

#include "canvas/utils/pos.h"
#include "canvas/windows/keyboard.h"

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
  Pos<I32> pos;

  PositionEvent(Type type, const Pos<I32>& pos) : Event(type), pos(pos) {}
};

struct MouseEvent : PositionEvent {
  enum Button {
    None,
    Left,
    Middle,
    Right,
  } button;

  MouseEvent(Type type, const Pos<I32>& pos, Button button) : PositionEvent(type, pos), button(button) {}
};

struct MouseWheelEvent : PositionEvent {
  Pos<I32> wheelOffset;

  MouseWheelEvent(Type type, const Pos<I32>& pos, Pos<I32>& wheelOffset)
    : PositionEvent(type, pos), wheelOffset(wheelOffset) {}
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_EVENT_H_

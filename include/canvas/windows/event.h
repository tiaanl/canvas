// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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

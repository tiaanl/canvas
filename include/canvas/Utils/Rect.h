
#ifndef CANVAS_UTILS_RECT_H_
#define CANVAS_UTILS_RECT_H_

#include "Pos.h"
#include "Size.h"

namespace ca {

template <typename T>
struct Rect {
  Pos<T> pos;
  Size<T> size;

  Rect() = default;

  Rect(T x, T y, T width, T height) : pos(x, y), size(width, height) {}

  Rect(const Pos<T>& pos, const Size<T>& size) : pos(pos), size(size) {}

  // Return true if the position is contained within this rectangle.
  bool contains(const Pos<T>& p) const {
    return (p.x >= pos.x && p.x < pos.x + size.width) && (p.y >= pos.y && p.y < pos.y + size.height);
  }
};

}  // namespace ca

#endif  // CANVAS_UTILS_RECT_H_

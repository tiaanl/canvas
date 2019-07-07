
#ifndef CANVAS_UTILS_RECT_H_
#define CANVAS_UTILS_RECT_H_

#include "Pos.h"
#include "Size.h"

namespace ca {

struct Rect {
  Pos pos;
  Size size;

  Rect() = default;

  Rect(I32 x, I32 y, I32 width, I32 height) : pos(x, y), size(width, height) {}

  Rect(const Pos& pos, const Size& size) : pos(pos), size(size) {}

  // Return true if the position is contained within this rectangle.
  bool contains(const Pos& p) const {
    return (p.x >= pos.x && p.x < pos.x + size.width) &&
           (p.y >= pos.y && p.y < pos.y + size.height);
  }
};

}  // namespace ca

#endif  // CANVAS_UTILS_RECT_H_

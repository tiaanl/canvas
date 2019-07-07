
#ifndef CANVAS_UTILS_SIZE_H_
#define CANVAS_UTILS_SIZE_H_

#include "nucleus/Types.h"

namespace ca {

struct Size {
  I32 width = 0;
  I32 height = 0;

  Size() = default;

  Size(I32 width, I32 height) : width(width), height(height) {}

  bool operator==(const Size& right) const {
    return width == right.width && height == right.height;
  }

  bool operator!=(const Size& right) const {
    return !(*this == right);
  }
};

}  // namespace ca

#endif  // CANVAS_UTILS_SIZE_H_

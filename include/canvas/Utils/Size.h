
#ifndef CANVAS_UTILS_SIZE_H_
#define CANVAS_UTILS_SIZE_H_

#include <ostream>

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

inline std::ostream& operator<<(std::ostream& os, const Size& value) {
  os << "{" << value.width << ", " << value.height << "}";
  return os;
}

}  // namespace ca

#endif  // CANVAS_UTILS_SIZE_H_

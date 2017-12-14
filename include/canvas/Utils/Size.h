
#ifndef CANVAS_UTILS_SIZE_H_
#define CANVAS_UTILS_SIZE_H_

namespace ca {

template <typename T>
struct Size {
  T width = 0;
  T height = 0;

  Size() {}

  Size(T width, T height) : width(width), height(height) {}

  bool operator==(const Size& right) const { return width == right.width && height == right.height; }

  bool operator!=(const Size& right) const { return !(*this == right); }
};

}  // namespace ca

#endif  // CANVAS_UTILS_SIZE_H_

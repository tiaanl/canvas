
#ifndef CANVAS_UTILS_COLOR_H_
#define CANVAS_UTILS_COLOR_H_

#include "nucleus/Types.h"

namespace ca {

struct Color {
  U8 r;
  U8 g;
  U8 b;
  U8 a;

  // Construct a color with default values.
  Color() : r{0}, g{0}, b{0}, a{255} {}

  // Construct a color without alpha component.
  Color(U8 r, U8 g, U8 b, U8 a = 255) : r{r}, g{g}, b{b}, a{a} {}
};

}  // namespace ca

#endif  // CANVAS_UTILS_COLOR_H_

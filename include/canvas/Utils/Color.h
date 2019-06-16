
#ifndef CANVAS_UTILS_COLOR_H_
#define CANVAS_UTILS_COLOR_H_

#include "nucleus/Types.h"

namespace ca {

struct Color {
  static Color white;
  static Color red;
  static Color green;
  static Color blue;

  F32 r = 0.0f;
  F32 g = 0.0f;
  F32 b = 0.0f;
  F32 a = 1.0f;

  Color() = default;
  Color(F32 r, F32 g, F32 b) : r{r}, g{g}, b{b}, a{1.0f} {}
  Color(F32 r, F32 g, F32 b, F32 a) : r{r}, g{g}, b{b}, a{a} {}
};

}  // namespace ca

#endif  // CANVAS_UTILS_COLOR_H_

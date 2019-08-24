
#ifndef CANVAS_UTILS_COLOR_H_
#define CANVAS_UTILS_COLOR_H_

#include "nucleus/Types.h"

namespace ca {

struct Color {
  static Color black;
  static Color red;
  static Color yellow;
  static Color green;
  static Color blue;
  static Color white;

  F32 r;
  F32 g;
  F32 b;
  F32 a;

  Color(F32 r, F32 g, F32 b, F32 a = 1.0f) : r{r}, g{g}, b{b}, a{a} {}
};

}  // namespace ca

#endif  // CANVAS_UTILS_COLOR_H_

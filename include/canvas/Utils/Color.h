
#ifndef CANVAS_UTILS_COLOR_H_
#define CANVAS_UTILS_COLOR_H_

#include "nucleus/Types.h"

namespace ca {

struct Color {
  F32 r;
  F32 g;
  F32 b;
  F32 a;
};

inline Color color() {
  Color result;

  result.r = 0;
  result.g = 0;
  result.b = 0;
  result.a = 255;

  return result;
}

inline Color color(F32 r, F32 g, F32 b, F32 a) {
  Color result;

  result.r = r;
  result.g = g;
  result.b = b;
  result.a = a;

  return result;
}

}  // namespace ca

#endif  // CANVAS_UTILS_COLOR_H_

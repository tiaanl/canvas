#pragma once

#include <ostream>

#include "nucleus/types.h"

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

inline std::ostream& operator<<(std::ostream& os, const Color& value) {
  os << "{" << value.r << ", " << value.g << ", " << value.b << ", " << value.a << "}";
  return os;
}

}  // namespace ca

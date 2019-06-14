
#ifndef CANVAS_MATH_COMMON_H_
#define CANVAS_MATH_COMMON_H_

#include "nucleus/Types.h"

#include <cmath>

namespace ca {

constexpr F32 kPi = 3.1415926535897932384626433832795f;
constexpr F32 kNearZero = 1.0f / static_cast<F32>(1 << 28);

inline F32 squareRoot(F32 x) {
  return std::sqrtf(x);
}

inline F32 absolute(F32 x) {
  return x < 0.0f ? -x : x;
}

inline bool nearZero(F32 x) {
  return absolute(x) < kNearZero;
}

}  // namespace ca

#endif  // CANVAS_MATH_COMMON_H_

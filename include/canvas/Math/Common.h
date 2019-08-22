
#ifndef CANVAS_MATH_COMMON_H_
#define CANVAS_MATH_COMMON_H_

#include "nucleus/Types.h"

#include <cmath>

namespace ca {

constexpr F32 kPi = 3.1415926535897932384626433832795f;
constexpr F32 kNearZero = 0.00001f;  // 1.0f / static_cast<F32>(1U << 16U);

inline F32 sine(F32 radians) {
  return std::sinf(radians);
}

inline F32 arcSine(F32 radians) {
  return std::asinf(radians);
}

inline F32 cosine(F32 radians) {
  return std::cosf(radians);
}

inline F32 arcCosine(F32 radians) {
  return std::acosf(radians);
}

inline F32 tangent(F32 radians) {
  return std::tanf(radians);
}

inline F32 arcTangent(F32 radians) {
  return std::atanf(radians);
}

inline F32 arcTangent2(F32 y, F32 x) {
  return std::atan2f(y, x);
}

inline F32 degreesToRadians(F32 degrees) {
  return degrees / 180.0f * kPi;
}

inline F32 radiansToDegrees(F32 radians) {
  return radians * 180.0f / kPi;
}

inline F32 round(F32 x) {
  return std::roundf(x);
}

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

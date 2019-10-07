
#ifndef CANVAS_MATH_COMMON_H_
#define CANVAS_MATH_COMMON_H_

#include "canvas/Math/Angle.h"
#include "canvas/Utils/Size.h"
#include "nucleus/Logging.h"
#include "nucleus/Types.h"

#include <algorithm>
#include <cmath>

namespace ca {

constexpr F32 kNearZero = 0.00001f;  // 1.0f / static_cast<F32>(1U << 16U);

inline F32 sine(F32 radians) {
  return std::sinf(radians);
}

inline F32 sine(Angle angle) {
  return sine(angle.radians());
}

inline F32 arcSine(F32 radians) {
  return std::asinf(radians);
}

inline F32 arcSine(Angle angle) {
  return arcSine(angle.radians());
}

inline F32 cosine(F32 radians) {
  return std::cosf(radians);
}

inline F32 cosine(Angle angle) {
  return cosine(angle.radians());
}

inline F32 arcCosine(F32 radians) {
  return std::acosf(radians);
}

inline F32 arcCosine(Angle angle) {
  return arcCosine(angle.radians());
}

inline F32 tangent(F32 radians) {
  return std::tanf(radians);
}

inline F32 tangent(Angle angle) {
  return tangent(angle.radians());
}

inline F32 arcTangent(F32 radians) {
  return std::atanf(radians);
}

inline F32 arcTangent(Angle angle) {
  return arcTangent(angle.radians());
}

inline F32 arcTangent2(F32 y, F32 x) {
  return std::atan2f(y, x);
}

inline Angle arcTangent2Angle(F32 y, F32 x) {
  return ca::radians(arcTangent2(y, x));
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

inline F32 clamp(F32 value, F32 min, F32 max) {
  DCHECK(min < max) << "min value should be less than max value";

  return std::min(max, std::max(value, min));
}

template <typename T>
inline auto max(const T& x, const T& y) -> T {
  return x < y ? y : x;
}

template <>
inline auto max<ca::Size>(const ca::Size& x, const ca::Size& y) -> ca::Size {
  return ca::Size{max(x.width, y.width), max(x.height, y.height)};
}

}  // namespace ca

#endif  // CANVAS_MATH_COMMON_H_

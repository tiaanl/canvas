#ifndef CANVAS_MATH_MAT3_H_
#define CANVAS_MATH_MAT3_H_

#include "canvas/Math/Vec3.h"

namespace ca {

struct Mat3 {
  static Mat3 identity;

  Vec3 col[3];

  // Construct from axes.
  Mat3(const Vec3& right, const Vec3& up, const Vec3& forward) : col{right, up, forward} {}
};

inline Mat3 fromRotationAxis(const Vec3& axis, F32 rotationInDegrees) {
  return Mat3::identity;
}

}  // namespace ca

#endif  // CANVAS_MATH_MAT3_H_

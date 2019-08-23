#ifndef CANVAS_MATH_ANGLE_H_
#define CANVAS_MATH_ANGLE_H_

#include "nucleus/Types.h"

namespace ca {

constexpr F32 kPi = 3.1415926535897932384626433832795f;

inline F32 degreesToRadians(F32 degrees) {
  return degrees / 180.0f * kPi;
}

inline F32 radiansToDegrees(F32 radians) {
  return radians * 180.0f / kPi;
}

class Angle {
public:
  static Angle zero;

  static Angle fromDegrees(F32 degrees) {
    return Angle{degreesToRadians(degrees)};
  }

  static Angle fromRadians(F32 radians) {
    return Angle{radians};
  }

  F32 degrees() const {
    return radiansToDegrees(m_radians);
  }

  F32 radians() const {
    return m_radians;
  }

  friend Angle operator+(Angle left, Angle right) {
    return Angle{left.m_radians + right.m_radians};
  }

  Angle& operator+=(Angle right) {
    m_radians += right.m_radians;
    return *this;
  }

  Angle& operator+=(F32 right) {
    m_radians += right;
    return *this;
  }

  friend Angle operator*(Angle left, F32 right) {
    return Angle{left.m_radians * right};
  }

  friend Angle operator/(Angle left, F32 right) {
    return Angle{left.m_radians / right};
  }

private:
  explicit Angle(F32 radians) : m_radians{radians} {}

  F32 m_radians;
};

inline Angle degrees(F32 degrees) {
  return Angle::fromDegrees(degrees);
}

inline Angle radians(F32 radians) {
  return Angle::fromRadians(radians);
}

}  // namespace ca

#endif  // CANVAS_MATH_ANGLE_H_

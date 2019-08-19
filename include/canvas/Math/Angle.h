#ifndef CANVAS_MATH_ANGLE_H_
#define CANVAS_MATH_ANGLE_H_

#include "canvas/Math/Common.h"
#include "nucleus/Types.h"

namespace ca {

class Angle {
public:
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

  Angle& operator+=(F32 right) {
    m_radians += right;
    return *this;
  }

private:
  explicit Angle(F32 radians) : m_radians{radians} {}

  F32 m_radians;
};

}  // namespace ca

#endif  // CANVAS_MATH_ANGLE_H_

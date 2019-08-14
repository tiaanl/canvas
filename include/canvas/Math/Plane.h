#ifndef CANVAS_MATH_PLANE_H_
#define CANVAS_MATH_PLANE_H_

#include "canvas/Math/Vec3.h"

namespace ca {

struct Plane {
  ca::Vec3 normal;
  F32 distance;
};

}  // namespace ca

#endif  // CANVAS_MATH_PLANE_H_

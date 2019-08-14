#ifndef CANVAS_MATH_RAY_H_
#define CANVAS_MATH_RAY_H_

#include "canvas/Math/Vec3.h"

namespace ca {

struct Ray {
  ca::Vec3 origin;
  ca::Vec3 direction;
};

}  // namespace ca

#endif  // CANVAS_MATH_RAY_H_

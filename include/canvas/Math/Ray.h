
#ifndef CANVAS_MATH_RAY_H_
#define CANVAS_MATH_RAY_H_

#include "canvas/Math/Vec3.h"

namespace ca {

struct Ray {
    // The origin of the ray.
    Vec3 origin;

    // The direction the ray is pointing.
    Vec3 direction;
};

}  // namespace ca

#endif  // CANVAS_MATH_RAY_H_

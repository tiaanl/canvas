
#ifndef CANVAS_GEOMETRY_PLANE_H_
#define CANVAS_GEOMETRY_PLANE_H_

#include "canvas/Math/Vec3.h"

namespace ca {

// r = any point on the plane.s
// dotProduct(r - point, normal) == 0
struct Plane {
    // A point on the plane.
    Vec3 point;

    // The normal direction of the plane.
    Vec3 normal;
};

}  // namespace ca

#endif  // CANVAS_GEOMETRY_PLANE_H_

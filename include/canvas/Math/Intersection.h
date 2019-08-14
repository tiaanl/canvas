#ifndef CANVAS_MATH_INTERSECTION_H_
#define CANVAS_MATH_INTERSECTION_H_

#include "canvas/Math/Plane.h"
#include "canvas/Math/Ray.h"

namespace ca {

struct IntersectionResult {
  bool didIntersect;
  ca::Vec3 position;
};

inline IntersectionResult intersection(const Plane& plane, const Ray& ray) {
  auto w = (plane.normal * plane.distance) - ray.origin;

  F32 k = dotProduct(w, plane.normal) / dotProduct(ray.direction, plane.normal);

  auto intersection = ray.origin + ray.direction * k;

  return {k >= 0.0f && k <= 1.0f, intersection};
}

}  // namespace ca

#endif  // CANVAS_MATH_INTERSECTION_H_

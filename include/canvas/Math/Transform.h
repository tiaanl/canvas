#ifndef CANVAS_MATH_TRANSFORM_H_
#define CANVAS_MATH_TRANSFORM_H_

#include "canvas/Math/Mat4.h"
#include "canvas/Utils/Rect.h"

namespace ca {

Mat4 scaleMatrix(F32 scale);
Mat4 scaleMatrix(const Vec3& scale);

Mat4 translationMatrix(const Vec3& translate);
Mat4 rotationMatrix(const Vec3& axis, F32 degrees);

Mat4 orthographicProjection(F32 left, F32 right, F32 top, F32 bottom, F32 near, F32 far);
Mat4 perspectiveProjection(F32 fieldOfView, F32 aspectRatio, F32 near, F32 far);

}  // namespace ca

#endif  // CANVAS_MATH_TRANSFORM_H_

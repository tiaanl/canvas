#ifndef CANVAS_MATH_TRANSFORM_H_
#define CANVAS_MATH_TRANSFORM_H_

#include "canvas/Math/Mat4.h"
#include "canvas/Utils/Rect.h"

namespace ca {

Mat4 orthographicProjection(F32 left, F32 right, F32 top, F32 bottom, F32 near, F32 far);

}  // namespace ca

#endif  // CANVAS_MATH_TRANSFORM_H_

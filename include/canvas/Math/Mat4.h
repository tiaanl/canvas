#ifndef CANVAS_MATH_MAT4_H_
#define CANVAS_MATH_MAT4_H_

#include "canvas/Math/Vec4.h"

namespace ca {

struct Mat4 {
  static Mat4 identity;

  Vec4 col[4];

  Mat4(const Vec4& col1, const Vec4& col2, const Vec4& col3, const Vec4& col4)
    : col{col1, col2, col3, col4} {}

  Mat4(const Vec3& right, const Vec3& up, const Vec3& forward)
    : col{{right, 0.0f}, {up, 0.0f}, {forward, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}} {}
};

Mat4 operator*(const Mat4& left, const Mat4& right);
Vec4 operator*(const Mat4& left, const Vec4& right);
Vec4 operator*(const Vec4& left, const Mat4& right);

Mat4 transpose(const Mat4& m);
Mat4 inverse(const Mat4& m);

}  // namespace ca

#endif  // CANVAS_MATH_MAT4_H_

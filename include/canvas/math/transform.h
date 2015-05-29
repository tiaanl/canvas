// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef CANVAS_MATH_TRANSFORM_H_
#define CANVAS_MATH_TRANSFORM_H_

#include "canvas/math/mat4.h"
#include "canvas/math/vec3.h"

namespace ca {

inline Mat4 translate(const Mat4& mat, const Vec3& vec) {
  Mat4 result{mat};
  result[3] = Vec4{vec, 1.f};
  return result;
}

inline Mat4 rotate(const Mat4& mat, f32 radians, const Vec3& v) {
  const f32 a = radians;
  const f32 c = std::cosf(radians);
  const f32 s = std::sinf(radians);

  Vec3 axis(normalize(v));
  Vec3 temp(axis * (1.f - c));

  Mat4 rotate;

  rotate[0][0] = c + temp[0] * axis[0];
  rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
  rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

  rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
  rotate[1][1] = c + temp[1] * axis[1];
  rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

  rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
  rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
  rotate[2][2] = c + temp[2] * axis[2];

  Mat4 result;
  result[0] =
      mat[0] * rotate[0][0] + mat[1] * rotate[0][1] + mat[2] * rotate[0][2];
  result[1] =
      mat[0] * rotate[1][0] + mat[1] * rotate[1][1] + mat[2] * rotate[1][2];
  result[2] =
      mat[0] * rotate[2][0] + mat[1] * rotate[2][1] + mat[2] * rotate[2][2];
  result[3] = mat[3];

  return result;
}

inline Mat4 scale(const Mat4& mat, const Vec3& scale) {
  Mat4 result;
  result[0] = mat[0] * scale[0];
  result[1] = mat[1] * scale[1];
  result[2] = mat[2] * scale[2];
  result[3] = mat[3];
  return result;
}

Mat4 ortho(f32 left, f32 right, f32 bottom, f32 top) {
  Mat4 result;

  result[0][0] = 2.0f / (right - left);
  result[1][1] = 2.0f / (top - bottom);
  result[2][2] = -1.0f;
  result[3][0] = -(right + left) / (right - left);
  result[3][1] = -(top + bottom) / (top - bottom);

  return result;
}

Mat4 ortho(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar) {
  Mat4 result;

  result[0][0] = 2.0f / (right - left);
  result[1][1] = 2.0f / (top - bottom);
  result[2][2] = -2.0f / (zFar - zNear);
  result[3][0] = -(right + left) / (right - left);
  result[3][1] = -(top + bottom) / (top - bottom);
  result[3][2] = -(zFar + zNear) / (zFar - zNear);

  return result;
}

}  // namespace ca

#endif  // CANVAS_MATH_TRANSFORM_H_

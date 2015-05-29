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

inline Mat4 translation(const Vec3& vec) {
  Mat4 result;  // identity
  result[3] = Vec4{vec, 1.f};
  return result;
}

inline Mat4 rotation(f32 degrees, const Vec3& rot) {
  const f32 c{std::cosf(degrees)};
  const f32 s{std::sinf(degrees)};

  const Vec3 axis{normalize(rot)};
  const Vec3 t{axis * (1.f - c)};

  Mat4 result;
  result[0][0] = c + t[0] * axis[0];
  result[0][1] = 0 + t[0] * axis[1] + s * axis[2];
  result[0][2] = 0 + t[0] * axis[2] - s * axis[1];
  result[0][3] = 0;

  result[1][0] = 0 + t[1] * axis[0] - s * axis[2];
  result[1][1] = c + t[1] * axis[1];
  result[1][2] = 0 + t[1] * axis[2] + s * axis[0];
  result[1][3] = 0;

  result[2][0] = 0 + t[2] * axis[0] + s * axis[1];
  result[2][1] = 0 + t[2] * axis[1] - s * axis[0];
  result[2][2] = c + t[2] * axis[2];
  result[2][3] = 0;

  return result;
}

inline Mat4 scaling(const Vec3& scale) {
  return Mat4{Vec4{scale.x, 0.f, 0.f, 0.f}, Vec4{0.f, scale.y, 0.f, 0.f},
              Vec4{0.f, 0.f, scale.z, 0.f}, Vec4{0.f, 0.f, 0.f, 1.f}};
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

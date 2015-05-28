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

Mat4 translation(const Vec3& vec) {
  Mat4 result{Mat4::identity};
  result[0].w = vec[0];
  result[1].w = vec[1];
  result[2].w = vec[2];
  // result[3] = Vec4{vec[0], vec[1], vec[2], 1.0f};
  return result;
}

Mat4 rotation(float angle, const Vec3& rot) {
  Mat4 result{Mat4::identity};

  const float a = angle;
  const float c = std::cosf(a);
  const float s = std::sinf(a);

  Vec3 nRot{rot};
  nRot.normalize();
  Vec3 axis(nRot);
  Vec3 temp(axis * (1.0f - c));

  result[0][0] = c + temp[0] * axis[0];
  result[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
  result[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

  result[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
  result[1][1] = c + temp[1] * axis[1];
  result[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

  result[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
  result[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
  result[2][2] = c + temp[2] * axis[2];

  return result;
}

Mat4 scaling(float scale) {
  Mat4 result{Mat4::identity};
  result[0][0] *= scale;
  result[1][1] *= scale;
  result[2][2] *= scale;
  return result;
}

inline Mat4 ortho(float left, float right, float bottom, float top, float near,
                  float far) {
  Mat4 result{Mat4::identity};
  result[0][0] = 2.0f / (right - left);
  result[1][1] = 2.0f / (top - bottom);
  result[2][2] = -2.0f / (far - near);
  result[3][0] = -(right + left) / (right - left);
  result[3][1] = -(top + bottom) / (top - bottom);
  result[3][2] = -(far + near) / (far - near);
  return result;
}

inline Mat4 ortho(float left, float right, float bottom, float top) {
  Mat4 result{Mat4::identity};
  result[0][0] = 2.0f / (right - left);
  result[1][1] = 2.0f / (top - bottom);
  result[2][2] = -1.0f;
  result[3][0] = -(right + left) / (right - left);
  result[3][1] = -(top + bottom) / (top - bottom);
  return result;
}

}  // namespace ca

#endif  // CANVAS_MATH_TRANSFORM_H_

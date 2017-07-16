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

#include <cmath>

#include "canvas/math/mat4.h"
#include "canvas/math/vec3.h"

namespace ca {

static constexpr F32 PI = 3.14159265f;

inline Mat4 translate(const Vec3& vec) {
  Mat4 result;
  result[3] = Vec4{vec, 1.f};
  return result;
}

inline Mat4 translate(F32 x, F32 y, F32 z) {
  Mat4 result;
  result[3][0] = x;
  result[3][1] = y;
  result[3][2] = z;
  return result;
}

inline Mat4 rotate(F32 radians, const Vec3& v) {
  const F32 a = radians;
  const F32 c = std::cos(radians);
  const F32 s = std::sin(radians);

  Vec3 axis(normalize(v));
  Vec3 temp(axis * (1.f - c));

  Mat4 result;

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

inline Mat4 scale(const Vec3& scale) {
  Mat4 result;
  result[0][0] = scale.x;
  result[1][1] = scale.y;
  result[2][2] = scale.z;
  return result;
}

inline Mat4 scale(F32 x, F32 y, F32 z) {
  Mat4 result;
  result[0][0] = x;
  result[1][1] = y;
  result[2][2] = z;
  return result;
}

inline Mat4 ortho(F32 left, F32 right, F32 bottom, F32 top, F32 zNear,
                  F32 zFar) {
  Mat4 result;

  result[0][0] = 2.f / (right - left);
  result[1][1] = 2.f / (top - bottom);
  result[2][2] = -2.f / (zFar - zNear);

  result[3][0] = -(right + left) / (right - left);
  result[3][1] = -(top + bottom) / (top - bottom);
  result[3][2] = -(zFar + zNear) / (zFar - zNear);

  return result;
}

inline Mat4 ortho(F32 left, F32 right, F32 bottom, F32 top) {
  Mat4 result;

  result[0][0] = 2.f / (right - left);
  result[1][1] = 2.f / (top - bottom);
  result[2][2] = -1.f;
  result[3][0] = -(right + left) / (right - left);
  result[3][1] = -(top + bottom) / (top - bottom);

  return result;
}

inline F32 degreesToRadians(F32 deg) {
  return deg * PI / 180.f;
}

inline F32 radiansToDegrees(F32 radians) {
  return radians * 180.f / PI;
}

inline F32 angleBetweenInRadians(const Vec2& origin, const Vec2& target) {
  return std::atan2(target.x - origin.x, target.y - origin.y);
}

}  // namespace ca

#endif  // CANVAS_MATH_TRANSFORM_H_

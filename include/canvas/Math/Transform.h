
#ifndef CANVAS_MATH_TRANSFORM_H_
#define CANVAS_MATH_TRANSFORM_H_

#include <cmath>

#include "Mat4.h"
#include "Vec3.h"

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

inline Mat4 ortho(F32 left, F32 right, F32 bottom, F32 top, F32 znear, F32 zfar) {
  ca::Mat4 result;

  result[0][0] = 2.f / (right - left);
  result[0][1] = 0;
  result[0][2] = 0;
  result[0][3] = 0;
  result[1][0] = 0;
  result[1][1] = 2.f / (top - bottom);
  result[1][2] = 0;
  result[1][3] = 0;
  result[2][0] = 0;
  result[2][1] = 0;
  result[2][2] = -2.f / (zfar - znear);
  result[2][3] = 0;
  result[3][0] = -(right + left) / (right - left);
  result[3][1] = -(top + bottom) / (top - bottom);
  result[3][2] = -(zfar + znear) / (zfar - znear);
  result[3][3] = 1.f;

  return result;

#if 0
    // clang-format off
    return ca::Mat4{
            2.f / (right - left),             0.f,                              0.f,                              0.f,
            0.f,                              2.f / (top - bottom),             0.f,                              0.f,
            0.f,                              0.f,                              1.f / (zfar - znear),             0.f,
            -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(zfar + znear) / (zfar - znear), 1.f
    };
    // clang-format on
#endif  // 0
}

inline Mat4 ortho(F32 left, F32 right, F32 bottom, F32 top) {
  return ortho(left, right, bottom, top, -1.f, 1.f);
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

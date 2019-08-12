#ifndef CANVAS_MATH_VEC4_H_
#define CANVAS_MATH_VEC4_H_

#include "canvas/Math/Vec2.h"
#include "canvas/Math/Vec3.h"
#include "nucleus/Types.h"

namespace ca {

struct Vec4 {
  F32 x;
  F32 y;
  F32 z;
  F32 w;

  Vec4(F32 x, F32 y, F32 z, F32 w) : x{x}, y{y}, z{z}, w{w} {}
  Vec4(const Vec2& xy, F32 z, F32 w) : x{xy.x}, y{xy.y}, z{z}, w{w} {}
  Vec4(const Vec3& xyz, F32 w) : x{xyz.x}, y{xyz.y}, z{xyz.z}, w{w} {}

  Vec4& operator+=(const Vec4& right) {
    x += right.x;
    y += right.y;
    z += right.z;
    w += right.w;

    return *this;
  }

  Vec4& operator-=(const Vec4& right) {
    x -= right.x;
    y -= right.y;
    z -= right.z;
    w -= right.w;

    return *this;
  }

  Vec4& operator*=(F32 right) {
    x *= right;
    y *= right;
    z *= right;
    w *= right;

    return *this;
  }

  Vec4& operator/=(F32 right) {
    x /= right;
    y /= right;
    z /= right;
    w /= right;

    return *this;
  }
};

inline Vec4 operator+(const Vec4& left, const Vec4& right) {
  return Vec4{left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w};
}

inline Vec4 operator-(const Vec4& left, const Vec4& right) {
  return Vec4{left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w};
}

inline Vec4 operator*(const Vec4& left, F32 right) {
  return Vec4{left.x * right, left.y * right, left.z * right, left.w * right};
}

inline Vec4 operator/(const Vec4& left, F32 right) {
  return Vec4{left.x / right, left.y / right, left.z / right, left.w / right};
}

}  // namespace ca

#endif  // CANVAS_MATH_VEC4_H_

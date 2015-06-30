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

#ifndef CANVAS_MATH_VEC4_H_
#define CANVAS_MATH_VEC4_H_

#include <cmath>
#include <ostream>

#include "nucleus/logging.h"
#include "nucleus/types.h"

#include "canvas/math/vec2.h"
#include "canvas/math/vec3.h"

namespace ca {

struct Vec4 {
  f32 x{0.f};
  f32 y{0.f};
  f32 z{0.f};
  f32 w{0.f};

  Vec4() = default;

  Vec4(f32 scalar) : x{scalar}, y{scalar}, z{scalar}, w{scalar} {}

  Vec4(f32 x, f32 y, f32 z, f32 w)
    : x{x}, y{y}, z{z}, w{w} {}

  Vec4(const Vec3& xyz, f32 w) : x{xyz.x}, y{xyz.y}, z{xyz.z}, w{w} {}

  Vec4(const Vec2& xy, const Vec2& zw) : x{xy.x}, y{xy.y}, z{zw.x}, w{zw.y} {}

  f32& operator[](size_t index) {
    DCHECK(index <= 3);
    return (&x)[index];
  }

  f32 operator[](size_t index) const {
    DCHECK(index <= 3);
    return (&x)[index];
  }

  bool operator==(const Vec4& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }

  bool operator!=(const Vec4& other) const {
    return x != other.x || y != other.y || z != other.z || w != other.w;
  }

  Vec4 operator-() const {
    return Vec4{-x, -y, -z, -w};
  }

  Vec4 operator+(const Vec4& other) const {
    return Vec4{x + other.x, y + other.y, z + other.z, w + other.w};
  }

  Vec4& operator+=(const Vec4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
  }

  Vec4 operator-(const Vec4& other) const {
    return Vec4{x - other.x, y - other.y, z - other.z, w - other.w};
  }

  Vec4 operator-(f32 scalar) const {
    return Vec4{x - scalar, y - scalar, z - scalar, w - scalar};
  }

  Vec4& operator-=(const Vec4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
  }

  Vec4 operator*(const Vec4& other) const {
    return Vec4{x * other.x, y * other.y, z * other.z, w * other.w};
  }

  Vec4& operator*=(const Vec4& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
  }

  Vec4 operator*(f32 scalar) const {
    return Vec4{x * scalar, y * scalar, z * scalar, w * scalar};
  }

  Vec4& operator*=(f32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
  }

  Vec4 operator/(f32 scalar) const {
    return Vec4{x / scalar, y / scalar, z / scalar, w / scalar};
  }

  Vec4& operator/=(f32 scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
  }
};

inline f32 dotProduct(const Vec4& a, const Vec4& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline f32 lengthSquared(const Vec4& a) {
  return dotProduct(a, a);
}

inline f32 length(const Vec4& a) {
  return std::sqrtf(lengthSquared(a));
}

inline Vec4 normalize(const Vec4& a) {
  return a * (1.f / length(a));
}

}  // namespace ca

inline std::ostream& operator<<(std::ostream& os, const ca::Vec4& vec4) {
  os << "{" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w
     << "}";
  return os;
}

#endif  // CANVAS_MATH_VEC2_H_

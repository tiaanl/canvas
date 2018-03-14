
#ifndef CANVAS_MATH_VEC4_H_
#define CANVAS_MATH_VEC4_H_

#include <cmath>
#include <ostream>

#include "nucleus/Logging.h"
#include "nucleus/Types.h"

#include "Vec2.h"
#include "Vec3.h"

namespace ca {

struct Vec4 {
  F32 x{0.f};
  F32 y{0.f};
  F32 z{0.f};
  F32 w{0.f};

  Vec4() = default;

  Vec4(F32 scalar) : x{scalar}, y{scalar}, z{scalar}, w{scalar} {}

  Vec4(F32 x, F32 y, F32 z, F32 w) : x{x}, y{y}, z{z}, w{w} {}

  Vec4(const Vec3& xyz, F32 w) : x{xyz.x}, y{xyz.y}, z{xyz.z}, w{w} {}

  Vec4(const Vec2& xy, const Vec2& zw) : x{xy.x}, y{xy.y}, z{zw.x}, w{zw.y} {}

  F32& operator[](USize index) {
    DCHECK(index <= 3);
    return (&x)[index];
  }

  F32 operator[](USize index) const {
    DCHECK(index <= 3);
    return (&x)[index];
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

  Vec4 operator-(F32 scalar) const {
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

  Vec4 operator*(F32 scalar) const {
    return Vec4{x * scalar, y * scalar, z * scalar, w * scalar};
  }

  Vec4& operator*=(F32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
  }

  Vec4 operator/(F32 scalar) const {
    return Vec4{x / scalar, y / scalar, z / scalar, w / scalar};
  }

  Vec4& operator/=(F32 scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
  }
};

inline F32 dotProduct(const Vec4& a, const Vec4& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline F32 lengthSquared(const Vec4& a) {
  return dotProduct(a, a);
}

inline F32 length(const Vec4& a) {
  return std::sqrt(lengthSquared(a));
}

inline Vec4 normalize(const Vec4& a) {
  return a * (1.f / length(a));
}

inline bool operator==(const Vec4& left, const Vec4& right) {
  return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}

inline bool operator!=(const Vec4& left, const Vec4& right) {
  return left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w;
}

inline std::ostream& operator<<(std::ostream& os, const Vec4& vec4) {
  os << "{" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << "}";
  return os;
}

}  // namespace ca

#endif  // CANVAS_MATH_VEC2_H_

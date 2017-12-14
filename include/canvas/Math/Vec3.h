
#ifndef CANVAS_MATH_VEC3_H_
#define CANVAS_MATH_VEC3_H_

#include <cmath>

#include "nucleus/Logging.h"
#include "nucleus/Types.h"

#include "Vec2.h"

namespace ca {

struct Vec3 {
  F32 x{0.f};
  F32 y{0.f};
  F32 z{0.f};

  explicit Vec3(F32 x = 0.f, F32 y = 0.f, F32 z = 0.f) : x{x}, y{y}, z{z} {}
  Vec3(const Vec2& xy, F32 z) : x{xy.x}, y{xy.y}, z{z} {}

  F32& operator[](USize index) {
    DCHECK(index <= 2);
    return (&x)[index];
  }

  F32 operator[](USize index) const {
    DCHECK(index <= 2);
    return (&x)[index];
  }

  bool operator==(const Vec3& other) const { return x == other.x && y == other.y && z == other.z; }

  bool operator!=(const Vec3& other) const { return x != other.x || y != other.y || z != other.z; }

  Vec3 operator-() const { return Vec3{-x, -y, -z}; }

  Vec3 operator+(const Vec3& other) const { return Vec3{x + other.x, y + other.y, z + other.z}; }

  Vec3& operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  Vec3 operator-(const Vec3& other) const { return Vec3{x - other.x, y - other.y, z - other.z}; }

  Vec3& operator-=(const Vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  Vec3 operator*(F32 scalar) const { return Vec3{x * scalar, y * scalar, z * scalar}; }

  Vec3& operator*=(F32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  Vec3 operator/(F32 scalar) const { return Vec3{x / scalar, y / scalar, z / scalar}; }

  Vec3& operator/=(F32 scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }
};

inline F32 dotProduct(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 crossProduct(const Vec3& a, const Vec3& b) {
  return Vec3{a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y};
}

inline F32 lengthSquared(const Vec3& a) {
  return dotProduct(a, a);
}

inline F32 length(const Vec3& a) {
  return std::sqrt(lengthSquared(a));
}

inline Vec3 normalize(const Vec3& a) {
  return a * (1.f / length(a));
}

}  // namespace ca

#endif  // CANVAS_MATH_VEC3_H_


#ifndef CANVAS_MATH_VEC3_H_
#define CANVAS_MATH_VEC3_H_

#include <cmath>

#include "nucleus/Types.h"

namespace ca {

struct Vec3 {
  F32 x = 0.f;
  F32 y = 0.f;
  F32 z = 0.f;

  Vec3() = default;

  explicit Vec3(F32 x_, F32 y_, F32 z_) : x{x_}, y{y_}, z{z_} {}

  F32 operator[](USize index) {
    DCHECK(index < 3) << "Vec3 only has 3 members";
    return (&x)[index];
  }

  Vec3 operator-() const {
    return Vec3{-x, -y, -z};
  }

  Vec3& operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
  }

  Vec3& operator-=(const Vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
  }

  Vec3& operator*=(F32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
  }

  Vec3& operator/=(F32 scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
  }
};

inline Vec3 operator+(const Vec3& left, const Vec3& right) {
  return Vec3{left.x + right.x, left.y + right.y, left.z + right.z};
}

inline Vec3 operator-(const Vec3& left, const Vec3& right) {
  return Vec3{left.x - right.x, left.y - right.y, left.z - right.z};
}

inline Vec3 operator*(const Vec3& left, F32 scalar) {
  return Vec3{left.x * scalar, left.y * scalar, left.z * scalar};
}

inline Vec3 operator/(const Vec3& left, F32 scalar) {
  return Vec3{left.x / scalar, left.y / scalar, left.z / scalar};
}

inline bool operator==(const Vec3& left, const Vec3& right) {
  return left.x == right.x && left.y == right.y && left.z == right.z;
}

inline bool operator!=(const Vec3& left, const Vec3& right) {
  return left.x != right.x || left.y != right.y || left.z != right.z;
}

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

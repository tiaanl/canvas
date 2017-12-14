
#ifndef CANVAS_MATH_VEC2_H_
#define CANVAS_MATH_VEC2_H_

#include <cmath>

#include "nucleus/Logging.h"
#include "nucleus/Types.h"

namespace ca {

struct Vec2 {
  F32 x{0.f};
  F32 y{0.f};

  explicit Vec2(F32 x = 0.f, F32 y = 0.f) : x{x}, y{y} {}

  F32& operator[](USize index) {
    DCHECK(index <= 1);
    return (&x)[index];
  }

  F32 operator[](USize index) const {
    DCHECK(index <= 1);
    return (&x)[index];
  }

  // Comparison

  bool operator==(const Vec2& right) const { return x == right.x && y == right.y; }

  bool operator!=(const Vec2& right) const { return x != right.x || y != right.y; }

  // Arithmatic

  Vec2 operator-() const { return Vec2{-x, -y}; }

  Vec2 operator+(const Vec2& right) const { return Vec2{x + right.x, y + right.y}; }

  Vec2& operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2 operator-(const Vec2& right) const { return Vec2{x - right.x, y - right.y}; }

  Vec2& operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vec2 operator*(F32 scalar) const { return Vec2{x * scalar, y * scalar}; }

  Vec2& operator*=(F32 scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vec2 operator/(F32 scalar) const { return Vec2{x / scalar, y / scalar}; }

  Vec2& operator/=(F32 scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }
};

inline F32 dotProduct(const Vec2& a, const Vec2& b) {
  return a.x * b.x + a.y * b.y;
}

inline F32 crossProduct(const Vec2& a, const Vec2& b) {
  return a.x * b.y - b.x * a.y;
}

inline F32 lengthSquared(const Vec2& a) {
  return dotProduct(a, a);
}

inline F32 length(const Vec2& a) {
  return std::sqrt(lengthSquared(a));
}

inline Vec2 normalize(const Vec2& a) {
  return a * (1.f / length(a));
}

inline bool closeTo(const Vec2& origin, const Vec2& target, F32 distance = 0.01f) {
  Vec2 diff = origin - target;
  return (diff.x <= distance && diff.x >= -distance && diff.y <= distance && diff.y >= -distance);
}

}  // namespace ca

inline std::ostream& operator<<(std::ostream& os, const ca::Vec2& v) {
  os << "(" << v.x << ", " << v.y << ")";
  return os;
}

#endif  // CANVAS_MATH_VEC2_H_

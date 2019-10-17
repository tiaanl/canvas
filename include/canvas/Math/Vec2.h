#ifndef CANVAS_MATH_VEC2_H_
#define CANVAS_MATH_VEC2_H_

#include "canvas/Math/Common.h"
#include "nucleus/Types.h"

#include <ostream>

namespace ca {

struct Vec2 {
  static Vec2 zero;

  F32 x;
  F32 y;

  Vec2(F32 x, F32 y) noexcept : x{x}, y{y} {}

  Vec2& operator+=(const Vec2& right) {
    x += right.x;
    y += right.y;

    return *this;
  }

  Vec2& operator-=(const Vec2& right) {
    x -= right.x;
    y -= right.y;

    return *this;
  }

  Vec2& operator*=(F32 right) {
    x *= right;
    y *= right;

    return *this;
  }

  Vec2& operator/=(F32 right) {
    x /= right;
    y /= right;

    return *this;
  }
};

inline Vec2 operator+(const Vec2& left, const Vec2& right) {
  return {left.x + right.x, left.y + right.y};
}

inline Vec2 operator-(const Vec2& left, const Vec2& right) {
  return {left.x - right.x, left.y - right.y};
}

inline Vec2 operator*(const Vec2& left, F32 right) {
  return {left.x * right, left.y * right};
}

inline Vec2 operator/(const Vec2& left, F32 right) {
  return {left.x / right, left.y / right};
}

inline Vec2 operator/(const Vec2& left, const Vec2& right) {
  return {left.x / right.x, left.y / right.y};
}

inline F32 dotProduct(const Vec2& left, const Vec2& right) {
  return left.x * right.x + left.y * right.y;
}

inline F32 lengthSquared(const Vec2& v) {
  return dotProduct(v, v);
}

inline F32 length(const Vec2& v) {
  return squareRoot(lengthSquared(v));
}

inline Vec2 normalize(const Vec2& v) {
  return v * (1.0f / length(v));
}

inline Vec2 lerp(const Vec2& a, const Vec2& b, F32 t) {
  return a + (b - a) * t;
}

inline std::ostream& operator<<(std::ostream& os, const Vec2& value) {
  os << "{" << value.x << ", " << value.y << "}";
  return os;
}

}  // namespace ca

#endif  // CANVAS_MATH_VEC2_H_

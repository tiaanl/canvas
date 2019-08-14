#ifndef CANVAS_MATH_VEC2_H_
#define CANVAS_MATH_VEC2_H_

#include "nucleus/Types.h"

#include <ostream>

namespace ca {

struct Vec2 {
  F32 x;
  F32 y;

  Vec2(F32 x, F32 y) : x{x}, y{y} {}

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
  return Vec2{left.x + right.x, left.y + right.y};
}

inline Vec2 operator-(const Vec2& left, const Vec2& right) {
  return Vec2{left.x - right.x, left.y - right.y};
}

inline Vec2 operator*(const Vec2& left, F32 right) {
  return Vec2{left.x * right, left.y * right};
}

inline Vec2 operator/(const Vec2& left, F32 right) {
  return Vec2{left.x / right, left.y / right};
}

inline std::ostream& operator<<(std::ostream& os, const Vec2& value) {
  os << "{" << value.x << ", " << value.y << "}";
  return os;
}

}  // namespace ca

#endif  // CANVAS_MATH_VEC2_H_

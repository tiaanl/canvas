
#ifndef CANVAS_UTILS_POS_H_
#define CANVAS_UTILS_POS_H_

#include <ostream>

namespace ca {

struct Pos {
  I32 x = 0;
  I32 y = 0;

  Pos() = default;

  Pos(I32 x, I32 y) : x(x), y(y) {}

  bool operator==(const Pos& other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Pos& other) const {
    return x != other.x || y != other.y;
  }

  Pos operator+(const Pos& other) {
    return Pos{x + other.x, y + other.y};
  }
  Pos operator-(const Pos& other) {
    return Pos{x - other.x, y - other.y};
  }

  void operator+=(const Pos& other) {
    x += other.x;
    y += other.y;
  }
  void operator-=(const Pos& other) {
    x -= other.x;
    y -= other.y;
  }
};

inline Pos operator-(const Pos& left) {
  return Pos{-left.x, -left.y};
}

inline Pos operator+(const Pos& left, const Pos& right) {
  return Pos{left.x + right.x, left.y + right.y};
}

inline Pos operator-(const Pos& left, const Pos& right) {
  return Pos{left.x - right.x, left.y - right.y};
}

inline Pos operator*(const Pos& left, const Pos& right) {
  return Pos{left.x * right.x, left.y * right.y};
}

inline Pos operator*(const Pos& left, I32 right) {
  return Pos{left.x * right, left.y * right};
}

}  // namespace ca

inline std::ostream& operator<<(std::ostream& os, const ca::Pos& pos) {
  os << "(" << pos.x << ", " << pos.y << ")";
  return os;
}

#endif  // CANVAS_UTILS_POS_H_


#ifndef CANVAS_UTILS_POS_H_
#define CANVAS_UTILS_POS_H_

#include <ostream>

namespace ca {

template <typename T>
struct Pos {
  T x{0};
  T y{0};

  Pos() {}

  Pos(T x, T y) : x(x), y(y) {}

  bool operator==(const Pos& other) const { return x == other.x && y == other.y; }
  bool operator!=(const Pos& other) const { return x != other.x || y != other.y; }

  Pos operator+(const Pos& other) { return Pos{x + other.x, y + other.y}; }
  Pos operator-(const Pos& other) { return Pos{x - other.x, y - other.y}; }

  void operator+=(const Pos& other) {
    x += other.x;
    y += other.y;
  }
  void operator-=(const Pos& other) {
    x -= other.x;
    y -= other.y;
  }
};

template <typename T>
Pos<T> operator-(const Pos<T>& left) {
  return Pos<T>{-left.x, -left.y};
}

template <typename T>
Pos<T> operator+(const Pos<T>& left, const Pos<T>& right) {
  return Pos<T>{left.x + right.x, left.y + right.y};
}

template <typename T>
Pos<T> operator-(const Pos<T>& left, const Pos<T>& right) {
  return Pos<T>{left.x - right.x, left.y - right.y};
}

template <typename T>
Pos<T> operator*(const Pos<T>& left, const Pos<T>& right) {
  return Pos<T>{left.x * right.x, left.y * right.y};
}

template <typename T>
Pos<T> operator*(const Pos<T>& left, T right) {
  return Pos<T>{left.x * right, left.y * right};
}

}  // namespace ca

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const ca::Pos<T>& pos) {
  os << "(" << pos.x << ", " << pos.y << ")";
  return os;
}

#endif  // CANVAS_UTILS_POS_H_
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

#ifndef CANVAS_MATH_MAT4_H_
#define CANVAS_MATH_MAT4_H_

#include "nucleus/logging.h"

#include "canvas/math/vec4.h"

namespace ca {

struct Mat4 {
  // Values in column major.
  Vec4 col[4];

  Mat4() {
    col[0] = Vec4{1.f, 0.f, 0.f, 0.f};
    col[1] = Vec4{0.f, 1.f, 0.f, 0.f};
    col[2] = Vec4{0.f, 0.f, 1.f, 0.f};
    col[3] = Vec4{0.f, 0.f, 0.f, 1.f};
  }

  Mat4(f32 scale) {
    col[0] = Vec4{scale, 0.f, 0.f, 0.f};
    col[1] = Vec4{0.f, scale, 0.f, 0.f};
    col[2] = Vec4{0.f, 0.f, scale, 0.f};
    col[3] = Vec4{0.f, 0.f, 0.f, scale};
  }

  Mat4(const Vec4& col1, const Vec4& col2, const Vec4& col3, const Vec4& col4) {
    col[0] = col1;
    col[1] = col2;
    col[2] = col3;
    col[3] = col4;
  }

  Mat4(f32 c11, f32 c12, f32 c13, f32 c14, f32 c21, f32 c22, f32 c23, f32 c24,
       f32 c31, f32 c32, f32 c33, f32 c34, f32 c41, f32 c42, f32 c43, f32 c44) {
    col[0] = Vec4{c11, c12, c13, c14};
    col[1] = Vec4{c21, c22, c23, c24};
    col[2] = Vec4{c31, c32, c33, c34};
    col[3] = Vec4{c41, c42, c43, c44};
  }

  Vec4& operator[](u32 index) {
    DCHECK(index <= 3);
    return col[index];
  }

  const Vec4& operator[](u32 index) const {
    DCHECK(index <= 3);
    return col[index];
  }

  f32* asArray() { return static_cast<f32*>(&col[0].x); }
  const f32* asArray() const { return static_cast<const f32*>(&col[0].x); }

  bool operator==(const Mat4& other) const {
    for (auto i = 0; i < 4; ++i) {
      if (col[i] != other.col[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Mat4& other) const {
    for (auto i = 0; i < 4; ++i) {
      if (col[i] != other.col[i]) {
        return true;
      }
    }
    return false;
  }

  Mat4 operator+(const Mat4& other) const {
    Mat4 result;
    for (auto i = 0; i < 4; ++i) {
      result[i] = col[i] + other.col[i];
    }
    return result;
  }

  Mat4& operator+=(const Mat4& other) {
    for (auto i = 0; i < 4; ++i) {
      col[i] += other.col[i];
    }
    return *this;
  }

  Mat4 operator-(const Mat4& other) const {
    Mat4 result;
    for (auto i = 0; i < 4; ++i)
      result[i] = col[i] - other.col[i];
    return result;
  }

  Mat4& operator-=(const Mat4& other) {
    for (auto i = 0; i < 4; ++i) {
      col[i] -= other.col[i];
    }
    return *this;
  }

  Mat4 operator*(const Mat4& right) const {
    Mat4 result;

    result[0][0] = col[0][0] * right[0][0] + col[1][0] * right[0][1] + col[2][0] * right[0][2] + col[3][0] * right[0][3];
    result[0][1] = col[0][1] * right[0][0] + col[1][1] * right[0][1] + col[2][1] * right[0][2] + col[3][1] * right[0][3];
    result[0][2] = col[0][2] * right[0][0] + col[1][2] * right[0][1] + col[2][2] * right[0][2] + col[3][2] * right[0][3];
    result[0][3] = col[0][3] * right[0][0] + col[1][3] * right[0][1] + col[2][3] * right[0][2] + col[3][3] * right[0][3];

    result[1][0] = col[0][0] * right[1][0] + col[1][0] * right[1][1] + col[2][0] * right[1][2] + col[3][0] * right[1][3];
    result[1][1] = col[0][1] * right[1][0] + col[1][1] * right[1][1] + col[2][1] * right[1][2] + col[3][1] * right[1][3];
    result[1][2] = col[0][2] * right[1][0] + col[1][2] * right[1][1] + col[2][2] * right[1][2] + col[3][2] * right[1][3];
    result[1][3] = col[0][3] * right[1][0] + col[1][3] * right[1][1] + col[2][3] * right[1][2] + col[3][3] * right[1][3];

    result[2][0] = col[0][0] * right[2][0] + col[1][0] * right[2][1] + col[2][0] * right[2][2] + col[3][0] * right[2][3];
    result[2][1] = col[0][1] * right[2][0] + col[1][1] * right[2][1] + col[2][1] * right[2][2] + col[3][1] * right[2][3];
    result[2][2] = col[0][2] * right[2][0] + col[1][2] * right[2][1] + col[2][2] * right[2][2] + col[3][2] * right[2][3];
    result[2][3] = col[0][3] * right[2][0] + col[1][3] * right[2][1] + col[2][3] * right[2][2] + col[3][3] * right[2][3];

    result[3][0] = col[0][0] * right[3][0] + col[1][0] * right[3][1] + col[2][0] * right[3][2] + col[3][0] * right[3][3];
    result[3][1] = col[0][1] * right[3][0] + col[1][1] * right[3][1] + col[2][1] * right[3][2] + col[3][1] * right[3][3];
    result[3][2] = col[0][2] * right[3][0] + col[1][2] * right[3][1] + col[2][2] * right[3][2] + col[3][2] * right[3][3];
    result[3][3] = col[0][3] * right[3][0] + col[1][3] * right[3][1] + col[2][3] * right[3][2] + col[3][3] * right[3][3];

    return result;
  }

  Mat4& operator*=(const Mat4& other) {
    *this = *this * other;
    return *this;
  }

  Vec4 operator*(const Vec4& vec) const {

    Vec4 col0 = col[0] * vec[0];
    Vec4 col1 = col[1] * vec[1];
    Vec4 col2 = col[2] * vec[2];
    Vec4 col3 = col[3] * vec[3];

    Vec4 result = col0 + col1 + col2 + col3;

    return col[0] * vec[0] + col[1] * vec[1] + col[2] * vec[2] +
           col[3] * vec[3];
  }

  Mat4 operator*(f32 scalar) const {
    Mat4 result;
    for (auto i = 0; i < 4; ++i) {
      result[i] = col[i] * scalar;
    }
    return result;
  }

  Mat4 operator/(f32 scalar) const {
    Mat4 result;
    for (auto i = 0; i < 4; ++i) {
      result[i] = col[i] / scalar;
    }
    return result;
  }

  Mat4& operator/=(f32 scalar) {
    for (auto i = 0; i < 4; ++i) {
      col[i] /= scalar;
    }
    return *this;
  }
};

inline Mat4 transpose(const Mat4& mat) {
  Mat4 result;
  for (auto i = 0; i < 4; ++i) {
    for (auto j = 0; j < 4; ++j) {
      result[i][j] = mat.col[j][i];
    }
  }
}

inline Mat4 inverse(const Mat4& m) {
  f32 coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
  f32 coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
  f32 coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

  f32 coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
  f32 coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
  f32 coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

  f32 coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
  f32 coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
  f32 coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

  f32 coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
  f32 coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
  f32 coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

  f32 coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
  f32 coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
  f32 coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

  f32 coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
  f32 coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
  f32 coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

  Vec4 fac0(coef00, coef00, coef02, coef03);
  Vec4 fac1(coef04, coef04, coef06, coef07);
  Vec4 fac2(coef08, coef08, coef10, coef11);
  Vec4 fac3(coef12, coef12, coef14, coef15);
  Vec4 fac4(coef16, coef16, coef18, coef19);
  Vec4 fac5(coef20, coef20, coef22, coef23);

  Vec4 vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
  Vec4 vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
  Vec4 vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
  Vec4 vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

  Vec4 inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
  Vec4 inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
  Vec4 inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
  Vec4 inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

  Vec4 signA(+1, -1, +1, -1);
  Vec4 signB(-1, +1, -1, +1);

  Mat4 inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

  Vec4 row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

  Vec4 dot0(m[0] * row0);
  f32 dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

  f32 oneOverDeterminant = 1.f / dot1;

  return inverse * oneOverDeterminant;
}

}  // namespace ca

#endif  // CANVAS_MATH_MAT4_H_

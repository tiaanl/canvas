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
  static Mat4 identity;

  Vec4 c[4];

  Mat4() {}

  Mat4(const Vec4& c1, const Vec4& c2, const Vec4& c3, const Vec4& c4) {
    c[0] = c1;
    c[1] = c2;
    c[2] = c3;
    c[3] = c4;
  }

  Mat4(float c11, float c12, float c13, float c14, float c21, float c22,
       float c23, float c24, float c31, float c32, float c33, float c34,
       float c41, float c42, float c43, float c44) {
    c[0] = Vec4{c11, c12, c13, c14};
    c[1] = Vec4{c21, c22, c23, c24};
    c[2] = Vec4{c31, c32, c33, c34};
    c[3] = Vec4{c41, c42, c43, c44};
  }

  Vec4& operator[](std::size_t index) {
    DCHECK(index <= 3);
    return c[index];
  }

  const Vec4& operator[](std::size_t index) const {
    DCHECK(index <= 3);
    return c[index];
  }

  float* asArray() { return static_cast<float*>(&c[0].x); }
  const float* asArray() const { return static_cast<const float*>(&c[0].x); }

  // Multiply

  Mat4 operator*(const Mat4& other) const {
    Mat4 result;

    for (int col = 0; col < 4; col++)
      for (int row = 0; row < 4; row++)
        result.c[col][row] =
          c[col][0] * other.c[0][row] +
          c[col][1] * other.c[1][row] +
          c[col][2] * other.c[2][row] +
          c[col][3] * other.c[3][row];

    return result;
  }

  Mat4& operator*=(const Mat4& right) {
    *this = *this * right;
    return *this;
  }
};

}  // namespace ca

#endif  // CANVAS_MATH_MAT4_H_

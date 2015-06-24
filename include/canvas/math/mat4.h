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

  Mat4(const Vec4& row1, const Vec4& row2, const Vec4& row3, const Vec4& row4) {
    col[0] = row1;
    col[1] = row2;
    col[2] = row3;
    col[3] = row4;
  }

  Mat4(f32 v11, f32 v12, f32 v13, f32 v14, f32 v21, f32 v22, f32 v23, f32 v24,
       f32 v31, f32 v32, f32 v33, f32 v34, f32 v41, f32 v42, f32 v43, f32 v44) {
    col[0] = Vec4{v11, v12, v13, v14};
    col[1] = Vec4{v21, v22, v23, v24};
    col[2] = Vec4{v31, v32, v33, v34};
    col[3] = Vec4{v41, v42, v43, v44};
  }

  Vec4& operator[](std::size_t index) {
    DCHECK(index <= 3);
    return col[index];
  }

  const Vec4& operator[](std::size_t index) const {
    DCHECK(index <= 3);
    return col[index];
  }

  float* asArray() { return static_cast<float*>(&col[0].x); }
  const float* asArray() const { return static_cast<const float*>(&col[0].x); }

  bool operator==(const Mat4& other) const {
    for (size_t i = 0; i < 4; ++i) {
      if (col[i] != other.col[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Mat4& other) const {
    for (size_t i = 0; i < 4; ++i) {
      if (col[i] != other.col[i]) {
        return true;
      }
    }
    return false;
  }

  Mat4 operator+(const Mat4& other) const {
    Mat4 result;
    for (size_t i = 0; i < 4; ++i) {
      result[i] = col[i] + other.col[i];
    }
    return result;
  }

  Mat4& operator+=(const Mat4& other) { return (*this = (*this) + other); }

  Mat4 operator-(const Mat4& other) const {
    Mat4 result;
    for (size_t i = 0; i < 4; ++i)
      result[i] = col[i] - other.col[i];
    return result;
  }

  Mat4& operator-=(const Mat4& other) { return (*this = (*this) - other); }

  Mat4 operator*(const Mat4& right) const {
    Mat4 result;
    const Mat4& left = *this;

    result[0][0] = left[0][0] * right[0][0] + left[1][0] * right[0][1] +
                   left[2][0] * right[0][2] + left[3][0] * right[0][3];
    result[0][1] = left[0][1] * right[0][0] + left[1][1] * right[0][1] +
                   left[2][1] * right[0][2] + left[3][1] * right[0][3];
    result[0][2] = left[0][2] * right[0][0] + left[1][2] * right[0][1] +
                   left[2][2] * right[0][2] + left[3][2] * right[0][3];
    result[0][3] = left[0][3] * right[0][0] + left[1][3] * right[0][1] +
                   left[2][3] * right[0][2] + left[3][3] * right[0][3];

    result[1][0] = left[0][0] * right[1][0] + left[1][0] * right[1][1] +
                   left[2][0] * right[1][2] + left[3][0] * right[1][3];
    result[1][1] = left[0][1] * right[1][0] + left[1][1] * right[1][1] +
                   left[2][1] * right[1][2] + left[3][1] * right[1][3];
    result[1][2] = left[0][2] * right[1][0] + left[1][2] * right[1][1] +
                   left[2][2] * right[1][2] + left[3][2] * right[1][3];
    result[1][3] = left[0][3] * right[1][0] + left[1][3] * right[1][1] +
                   left[2][3] * right[1][2] + left[3][3] * right[1][3];

    result[2][0] = left[0][0] * right[2][0] + left[1][0] * right[2][1] +
                   left[2][0] * right[2][2] + left[3][0] * right[2][3];
    result[2][1] = left[0][1] * right[2][0] + left[1][1] * right[2][1] +
                   left[2][1] * right[2][2] + left[3][1] * right[2][3];
    result[2][2] = left[0][2] * right[2][0] + left[1][2] * right[2][1] +
                   left[2][2] * right[2][2] + left[3][2] * right[2][3];
    result[2][3] = left[0][3] * right[2][0] + left[1][3] * right[2][1] +
                   left[2][3] * right[2][2] + left[3][3] * right[2][3];

    result[3][0] = left[0][0] * right[3][0] + left[1][0] * right[3][1] +
                   left[2][0] * right[3][2] + left[3][0] * right[3][3];
    result[3][1] = left[0][1] * right[3][0] + left[1][1] * right[3][1] +
                   left[2][1] * right[3][2] + left[3][1] * right[3][3];
    result[3][2] = left[0][2] * right[3][0] + left[1][2] * right[3][1] +
                   left[2][2] * right[3][2] + left[3][2] * right[3][3];
    result[3][3] = left[0][3] * right[3][0] + left[1][3] * right[3][1] +
                   left[2][3] * right[3][2] + left[3][3] * right[3][3];

    return result;
  }

  Mat4& operator*=(const Mat4& other) { return (*this = (*this) * other); }

  Vec4 operator*(const Vec4& other) const {
    return (col[0] * other[0] + col[1] * other[1]) +
           (col[2] * other[2] + col[3] * other[3]);
  }

  Mat4 operator*(f32 scalar) const {
    Mat4 result;
    for (size_t i = 0; i < 4; ++i) {
      result[i] = col[i] * scalar;
    }
    return result;
  }

  Mat4 operator/(f32 scalar) const {
    Mat4 result;
    for (size_t i = 0; i < 4; ++i) {
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
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      result[i][j] = mat.col[j][i];
    }
  }
}

inline Mat4 inverse(const Mat4& m) {
  f32 SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
  f32 SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
  f32 SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
  f32 SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
  f32 SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
  f32 SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
  f32 SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
  f32 SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
  f32 SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
  f32 SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
  f32 SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
  f32 SubFactor11 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
  f32 SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
  f32 SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
  f32 SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
  f32 SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
  f32 SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
  f32 SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
  f32 SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

  Mat4 inverse;
  inverse[0][0] =
      +(m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02);
  inverse[0][1] =
      -(m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04);
  inverse[0][2] =
      +(m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05);
  inverse[0][3] =
      -(m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05);

  inverse[1][0] =
      -(m[0][1] * SubFactor00 - m[0][2] * SubFactor01 + m[0][3] * SubFactor02);
  inverse[1][1] =
      +(m[0][0] * SubFactor00 - m[0][2] * SubFactor03 + m[0][3] * SubFactor04);
  inverse[1][2] =
      -(m[0][0] * SubFactor01 - m[0][1] * SubFactor03 + m[0][3] * SubFactor05);
  inverse[1][3] =
      +(m[0][0] * SubFactor02 - m[0][1] * SubFactor04 + m[0][2] * SubFactor05);

  inverse[2][0] =
      +(m[0][1] * SubFactor06 - m[0][2] * SubFactor07 + m[0][3] * SubFactor08);
  inverse[2][1] =
      -(m[0][0] * SubFactor06 - m[0][2] * SubFactor09 + m[0][3] * SubFactor10);
  inverse[2][2] =
      +(m[0][0] * SubFactor11 - m[0][1] * SubFactor09 + m[0][3] * SubFactor12);
  inverse[2][3] =
      -(m[0][0] * SubFactor08 - m[0][1] * SubFactor10 + m[0][2] * SubFactor12);

  inverse[3][0] =
      -(m[0][1] * SubFactor13 - m[0][2] * SubFactor14 + m[0][3] * SubFactor15);
  inverse[3][1] =
      +(m[0][0] * SubFactor13 - m[0][2] * SubFactor16 + m[0][3] * SubFactor17);
  inverse[3][2] =
      -(m[0][0] * SubFactor14 - m[0][1] * SubFactor16 + m[0][3] * SubFactor18);
  inverse[3][3] =
      +(m[0][0] * SubFactor15 - m[0][1] * SubFactor17 + m[0][2] * SubFactor18);

  f32 determinant = +m[0][0] * inverse[0][0] + m[0][1] * inverse[0][1] +
                    m[0][2] * inverse[0][2] + m[0][3] * inverse[0][3];

  inverse /= determinant;

  return inverse;
}

}  // namespace ca

#endif  // CANVAS_MATH_MAT4_H_

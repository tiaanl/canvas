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

#include "canvas/math/vec4.h"

namespace ca {

template <typename T>
struct Mat4 {
  Vec4<T> c[4];

  Mat4() {}

  Mat4(const Vec4<T>& c1, const Vec4<T>& c2, const Vec4<T>& c3,
       const Vec4<T>& c4) {
    c[0] = c1;
    c[1] = c2;
    c[2] = c3;
    c[3] = c4;
  }

  Mat4(T c11, T c12, T c13, T c14, T c21, T c22, T c23, T c24, T c31, T c32,
       T c33, T c34, T c41, T c42, T c43, T c44) {
    c[0] = Vec4<T>{c11, c12, c13, c14};
    c[1] = Vec4<T>{c21, c22, c23, c24};
    c[2] = Vec4<T>{c31, c32, c33, c34};
    c[3] = Vec4<T>{c41, c42, c43, c44};
  }

  T* asArray() { return static_cast<T*>(&c[0].x); }
  const T* asArray() const { return static_cast<const T*>(&c[0].x); }
};

using Mat4f = Mat4<float>;

}  // namespace ca

#endif  // CANVAS_MATH_MAT4_H_

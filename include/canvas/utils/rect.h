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

#ifndef CANVAS_UTILS_RECT_H_
#define CANVAS_UTILS_RECT_H_

#include "canvas/utils/pos.h"
#include "canvas/utils/size.h"

namespace ca {

template <typename T>
class Rect {
  Pos<T> pos;
  Size<T> size;

  Rect(T x, T y, T width, T height) : pos(x, y), size(width, height) {}

  Rect(const Pos<T>& pos, const Size<T>& size) : pos(pos), size(size) {}
};

}  // namespace ca

#endif  // CANVAS_UTILS_RECT_H_

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

#ifndef CANVAS_UTILS_IMAGE_H_
#define CANVAS_UTILS_IMAGE_H_

#include <vector>

#include "nucleus/macros.h"
#include "nucleus/streams/input_stream.h"
#include "nucleus/types.h"

#include "canvas/utils/color.h"
#include "canvas/utils/size.h"

namespace ca {

class Image {
public:
  using DataType = std::vector<u8>;

  Image() = default;
  ~Image() = default;

  // Get the size of the image.
  const Size<i32> getSize() const { return m_size; }

  // Get the pixel data for the image.
  const DataType& getData() const { return m_data; }

  // Create a blank image with the specified color.
  void create(const Size<i32>& size, const Color& col = Color{});

  // Load the image data from a stream.
  bool loadFromStream(nu::InputStream* stream);

private:
  // The dimensions of the image.
  Size<i32> m_size;

  // The buffer that holds the pixel data.
  DataType m_data;

  DISALLOW_COPY_AND_ASSIGN(Image);
};

}  // namespace ca

#endif  // CANVAS_UTILS_IMAGE_H_

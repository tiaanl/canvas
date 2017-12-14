
#ifndef CANVAS_UTILS_IMAGE_H_
#define CANVAS_UTILS_IMAGE_H_

#include "Color.h"
#include "Pos.h"
#include "Size.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"
#include "nucleus/Streams/InputStream.h"
#include "nucleus/Types.h"

namespace ca {

class Image {
public:
  using DataType = nu::DynamicArray<U8>;

  Image() = default;
  ~Image() = default;

  // Get the size of the image.
  const Size<I32> getSize() const { return m_size; }

  // Get the pixel data for the image.
  const DataType& getData() const { return m_data; }

  // Create a blank image with the specified color.
  void create(const Size<I32>& size, const Color& col = Color{});

  // Load the image data from a stream.
  bool loadFromStream(nu::InputStream* stream);

  // Set the color of a single pixel in the image.
  void setPixel(const Pos<I32>& pos, const Color& color);

private:
  // The dimensions of the image.
  Size<I32> m_size;

  // The buffer that holds the pixel data.
  DataType m_data;

  DISALLOW_COPY_AND_ASSIGN(Image);
};

}  // namespace ca

#endif  // CANVAS_UTILS_IMAGE_H_

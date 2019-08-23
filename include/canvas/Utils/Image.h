
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

enum class ImageFormat : U32 {
  Unknown,
  Alpha,
  RGB,
  RGBA,
};

class Image {
public:
  // Create a blank alpha image.
  static Image createAlpha(const Size& size, U8 intensity = 0);

  Image();
  Image(Image&& other);
  ~Image();

  Image& operator=(Image&& other);

  ImageFormat getFormat() const {
    return m_format;
  }

  // Get the size of the image.
  const Size& getSize() const {
    return m_size;
  }

  // Get the pixel data for the image.
  U8* getData() const {
    return const_cast<U8*>(m_data.getData());
  }
  // Create a blank image with the specified color.
  void create(const Size& size, const Color& col = ca::Color::black);

  // Load the image data from a stream.
  bool loadFromStream(nu::InputStream* stream);

  // Set the color of a single pixel in the image.
  void setPixel(const Pos& pos, const Color& color);

private:
  DELETE_COPY(Image);

  // Format of the data is stored in.
  ImageFormat m_format = ImageFormat::Unknown;

  // The dimensions of the image.
  Size m_size;

  // The buffer that holds the pixel data.
  nu::DynamicArray<U8> m_data;
};

}  // namespace ca

#endif  // CANVAS_UTILS_IMAGE_H_


#include "canvas/utils/image.h"

#include <cstring>

#include "nucleus/logging.h"
#include "nucleus/utils/stl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace ca {

namespace {

static int stbCallbackRead(void* user, char* data, int size) {
  nu::InputStream* stream = static_cast<nu::InputStream*>(user);
  return static_cast<int>(stream->read(data, size));
}

static void stbCallbackSkip(void* user, int size) {
  nu::InputStream* stream = static_cast<nu::InputStream*>(user);
  stream->setPosition(stream->getPosition() + size);
}

static int stbCallbackEof(void* user) {
  nu::InputStream* stream = static_cast<nu::InputStream*>(user);
  return stream->isExhausted();
}

}  // namespace

void Image::create(const Size<I32>& size, const Color& col) {
  if (size.width && size.height) {
    // Store the size of the image.
    m_size = size;

    // Resize the buffer to hold the image.
    m_data.resize(size.width * size.height * 4);

    // Fill the image with the specified color.
    U8* data = nu::vectorAsArray(&m_data);
    U8* end = data + m_data.size();
    while (data < end) {
      *data++ = col.r;
      *data++ = col.g;
      *data++ = col.b;
      *data++ = col.a;
    }
  } else {
    // Store the size and clear out the data.
    m_size = {0, 0};
    m_data.clear();
  }
}

bool Image::loadFromStream(nu::InputStream* stream) {
  DCHECK(stream);

  // Set up the STB callbacks.
  stbi_io_callbacks callbacks;
  callbacks.read = &stbCallbackRead;
  callbacks.skip = &stbCallbackSkip;
  callbacks.eof = &stbCallbackEof;

  // Load the image and get a pointer to the pixels in memory.
  int width, height, channels;
  stbi_uc* ptr = stbi_load_from_callbacks(&callbacks, stream, &width, &height, &channels, STBI_rgb_alpha);
  DCHECK(channels == 3 || channels == 4) << "Unsupported image format.";

  if (ptr && width && height) {
    // Set the properties on the image.
    m_size.width = width;
    m_size.height = height;

    // Copy the pixels to the pixel buffer.
    m_data.resize(width * height * 4);
    std::memcpy(nu::vectorAsArray(&m_data), ptr, m_data.size());

    stbi_image_free(ptr);
  } else {
    LOG(Error) << "Could not load image from stream. (" << stbi_failure_reason() << ")";
    return false;
  }

  return true;
}

void Image::setPixel(const Pos<I32>& pos, const Color& color) {
  U8* ptr = &m_data[pos.y * (m_size.width * 4) + (pos.x * 4)];
  *ptr++ = color.r;
  *ptr++ = color.g;
  *ptr++ = color.b;
  *ptr++ = color.a;
}

}  // namespace ca

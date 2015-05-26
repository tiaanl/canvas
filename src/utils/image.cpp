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

#include "canvas/utils/image.h"

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

bool Image::loadFromStream(nu::InputStream* stream) {
  DCHECK(stream);

  // Set up the STB callbacks.
  stbi_io_callbacks callbacks;
  callbacks.read = &stbCallbackRead;
  callbacks.skip = &stbCallbackSkip;
  callbacks.eof = &stbCallbackEof;

  // Load the image and get a pointer to the pixels in memory.
  int width, height, channels;
  stbi_uc* ptr = stbi_load_from_callbacks(&callbacks, stream, &width, &height,
                                          &channels, STBI_rgb_alpha);
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
    LOG(Error) << "Could not load image from stream. (" << stbi_failure_reason()
               << ")";
    return false;
  }

  return true;
}

}  // namespace ca

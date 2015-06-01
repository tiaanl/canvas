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

#include "canvas/rendering/texture.h"

#include "nucleus/logging.h"

#include "canvas/utils/gl_check.h"

namespace ca {

namespace {

static i32 getMaxTextureSize() {
  GLint size;
  GL_CHECK(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size));
  return size;
}

}  // namespace

// static
void Texture::bind(const Texture* texture) {
  if (!texture) {
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
  } else {
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture->m_name));
  }
}

Texture::~Texture() {
  if (m_name != 0) {
    glDeleteTextures(1, &m_name);
  }
}

bool Texture::create(const Size<i32>& size) {
  i32 maxTextureSize = getMaxTextureSize();
  if (size.width == 0 || (size.width & (size.width - 1)) != 0 ||
      size.width > maxTextureSize || size.height == 0 ||
      (size.height & (size.height - 1)) != 0 || size.height > maxTextureSize) {
    LOG(Error) << "Can't create texture with invalid size. (" << size.width
               << ", " << size.height << ")";
    return false;
  }

  // Store the size.
  m_size = size;

  // Create the texture name if it doesn't exist already.
  if (m_name == 0) {
    GL_CHECK(glGenTextures(1, &m_name));
  }

  // Initialize the texture.
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_name));
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.width, m_size.height,
                        0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

  const bool smooth = false;
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                           smooth ? GL_LINEAR : GL_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                           smooth ? GL_LINEAR : GL_NEAREST));

  return true;
}

bool Texture::createFromImage(const Image& image) {
  createNewName();
  m_size = image.getSize();

  // Bind the texture.
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_name));

  // Upload the image data.
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.width, m_size.height,
                        0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData().data()));

  // Set the texture clamping.
  const bool smooth = false;
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                           smooth ? GL_LINEAR : GL_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                           smooth ? GL_LINEAR : GL_NEAREST));

  // Unbind the texture we were working on.
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

  return true;
}

void Texture::update(const u8* pixels, const Rect<i32>& rect) {
  DCHECK(rect.pos.x + rect.size.width < m_size.width);
  DCHECK(rect.pos.y + rect.size.height < m_size.height);

  if (!pixels || !m_name) {
    LOG(Warning) << "No texture update performed.";
    return;
  }

  // TODO: Make sure there is a GL context available.

  bind(this);
  GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, rect.pos.x, rect.pos.y,
                           rect.size.width, rect.size.height, GL_RGBA,
                           GL_UNSIGNED_BYTE, pixels));
}

void Texture::createNewName() {
  if (m_name != 0) {
    GL_CHECK(glDeleteTextures(1, &m_name));
    m_name = 0;
  }

  GL_CHECK(glGenTextures(1, &m_name));
}

}  // namespace ca

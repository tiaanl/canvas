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

Texture::~Texture() {
  if (m_name != 0) {
    glDeleteTextures(1, &m_name);
  }
}

void Texture::bind() const {
  DCHECK(m_name != 0) << "Can't bind an invalid texture.";
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_name));
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

void Texture::createNewName() {
  if (m_name != 0) {
    GL_CHECK(glDeleteTextures(1, &m_name));
    m_name = 0;
  }

  GL_CHECK(glGenTextures(1, &m_name));
}

}  // namespace ca

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

#include "canvas/rendering/vertex_buffer_object.h"

#include "nucleus/logging.h"

namespace ca {

VertexBufferObject::~VertexBufferObject() {
  // Destroy the object when we're done.
  GL_CHECK(glDeleteBuffers(1, &m_name));
}

bool VertexBufferObject::setData(const void* data, size_t size) {
  // Make sure the buffer is created.
  createInternal();

  // Bind the object.
  ScopedBind binder(*this);

  // Upload the data and check for errors.
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG(Error) << "Could not upload data to vertex buffer object.";

    switch (error) {
      case GL_INVALID_OPERATION:
        LOG(Error) << "GL_INVALID_OPERATION is generated if the reserved "
                      "buffer object name 0 is bound to target.";
        break;

      default:
        LOG(Error) << "Unknown error";
        break;
    }

    return false;
  }

  return true;
}

bool VertexBufferObject::createInternal() {
  // If the object is already created, then we don't do anything.
  if (m_name) {
    return true;
  }

  // Generate the buffer.
  GL_CHECK(glGenBuffers(1, &m_name));

  return true;
}

void VertexBufferObject::bind() {
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_name));
}

void VertexBufferObject::unbind() {
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

}  // namespace ca

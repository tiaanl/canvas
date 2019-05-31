
#include "canvas/Rendering/VertexBufferObject.h"

#include "nucleus/Logging.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

VertexBufferObject::~VertexBufferObject() {
  // Destroy the object when we're done.
  GL_CHECK(glDeleteBuffers(1, &m_name));
}

bool VertexBufferObject::setData(const void* data, MemSize size) {
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

void VertexBufferObject::bind() const {
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_name));
}

void VertexBufferObject::unbind() const {
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

}  // namespace ca

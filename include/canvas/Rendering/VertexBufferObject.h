
#ifndef CANVAS_RENDERING_VERTEX_BUFFER_OBJECT_H_
#define CANVAS_RENDERING_VERTEX_BUFFER_OBJECT_H_

#include "nucleus/Macros.h"

#include "canvas/OpenGL.h"
#include "canvas/Utils/GLCheck.h"

namespace ca {

class VertexBufferObject {
public:
  // Scoper to bind this object.
  struct ScopedBind {
    const VertexBufferObject& vbo;
    ScopedBind(const VertexBufferObject& vbo) : vbo(vbo) { vbo.bind(); }
    ~ScopedBind() { vbo.unbind(); }
  };

  VertexBufferObject() = default;
  ~VertexBufferObject();

  GLuint getNativeHandle() const { return m_name; }

  // Upload the given data to the GPU.
  bool setData(const void* data, USize size);

private:
  // Create the name of the object.
  bool createInternal();

  // Bind the object.
  void bind() const;

  // Unbind the object.
  void unbind() const;

  // The name of the vertex buffer object.
  GLuint m_name = 0;
};

}  // namespace ca

#endif  // CANVAS_RENDERING_VERTEX_BUFFER_OBJECT_H_

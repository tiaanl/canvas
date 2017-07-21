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

#ifndef CANVAS_RENDERING_VERTEX_BUFFER_OBJECT_H_
#define CANVAS_RENDERING_VERTEX_BUFFER_OBJECT_H_

#include "nucleus/macros.h"

#include "canvas/opengl.h"
#include "canvas/utils/gl_check.h"

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

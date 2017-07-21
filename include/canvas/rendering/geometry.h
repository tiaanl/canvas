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

#ifndef CANVAS_RENDERING_GEOMETRY_H_
#define CANVAS_RENDERING_GEOMETRY_H_

#include <vector>

#include "canvas/rendering/canvas.h"
#include "canvas/rendering/vertex.h"
#include "canvas/rendering/vertex_buffer_object.h"
#include "canvas/utils/color.h"
#include "canvas/utils/rect.h"
#include "nucleus/macros.h"

namespace ca {

class Geometry {
public:
    enum PrimitiveType {
        Triangles,
        TriangleStrip,
        TriangleFan,
    };

    // Create a rectangle geometry with the given dimensions.
    static Geometry createRectangle(const Rect<F32>& rect, const Color& color);

    explicit Geometry(PrimitiveType primitiveType = Triangles);
    ~Geometry();

    // Add a single vertex to the geometry.
    void addVertex(const Vertex& vertex);

    // Add an array of vertices to the geometry.
    void addVertices(Vertex* vertices, USize count);

    // Clear the list of vertices.
    void clear();

    // Compile and upload the data to the GPU.
    void compileAndUpload();

    // Render the geometry with the given transform applied.
    void render(Canvas* canvas) const;

private:
    // The type of primitives we want to render.
    PrimitiveType m_primitiveType;

    // All the vertices we contain.
    std::vector<Vertex> m_vertices;

    // The vertex array we're using.
    GLuint m_vertexArrayObject{0};

    // The vertex buffer we use to upload the vertex data to the GPU.
    VertexBufferObject m_vbo;

    // Whether the vertex data was compiled or not.
    bool m_compiled{false};
};

}  // namespace ca

#endif  // CANVAS_RENDERING_GEOMETRY_H_

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

#include "canvas/rendering/geometry.h"

#include "nucleus/macros.h"

namespace ca {

// static
Geometry Geometry::createRectangle(const Rect<F32>& rect, const Color& color) {
    Geometry result{TriangleFan};

    Vertex vertices[] = {
        Vertex{Vec3{rect.pos.x, rect.pos.y, 0.f}, Vec2{0.f, 0.f}, color},
        Vertex{Vec3{rect.pos.x + rect.size.width, rect.pos.y, 0.f}, Vec2{1.f, 0.f}, color},
        Vertex{Vec3{rect.pos.x + rect.size.width, rect.pos.y + rect.size.height, 0.f}, Vec2{1.f, 1.f}, color},
        Vertex{Vec3{rect.pos.x, rect.pos.y + rect.size.height, 0.f}, Vec2{0.f, 1.f}, color},
    };

    result.addVertices(vertices, ARRAY_SIZE(vertices));

    return result;
}

Geometry::Geometry(PrimitiveType primitiveType) : m_primitiveType(primitiveType) {}

Geometry::~Geometry() {
    if (m_vertexArrayObject) {
        GL_CHECK(glDeleteVertexArrays(1, &m_vertexArrayObject));
    }
}

void Geometry::addVertex(const Vertex& vertex) {
    m_vertices.push_back(vertex);

    m_compiled = false;
}

void Geometry::addVertices(Vertex* vertices, USize count) {
    m_vertices.reserve(m_vertices.size() + count);
    for (USize i = 0; i < count; ++i) {
        m_vertices.push_back(vertices[i]);
    }

    m_compiled = false;
}

void Geometry::clear() {
    m_vertices.clear();

    m_compiled = false;
}

void Geometry::compileAndUpload() {
    if (!m_vertexArrayObject) {
        GL_CHECK(glGenVertexArrays(1, &m_vertexArrayObject));
    }

    // Bind the vertex array object.
    GL_CHECK(glBindVertexArray(m_vertexArrayObject));

    m_vbo.setData(m_vertices.data(), m_vertices.size() * sizeof(Vertex));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo.getNativeHandle()));

    // The position channel.
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0));
    GL_CHECK(glEnableVertexAttribArray(0));

    // The texCoord channel.
    GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3)));
    GL_CHECK(glEnableVertexAttribArray(1));

    // The color channel.
    GL_CHECK(glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 5)));
    GL_CHECK(glEnableVertexAttribArray(2));

    m_compiled = true;
}

void Geometry::render(Canvas* canvas) const {
    if (!m_vertices.empty() && !m_compiled) {
        NOTREACHED() << "You have to compile the geometry before you use it.";
        return;
    }

    GLenum prim = 0;
    switch (m_primitiveType) {
        case Triangles:
            prim = GL_TRIANGLES;
            break;

        case TriangleStrip:
            prim = GL_TRIANGLE_STRIP;
            break;

        case TriangleFan:
            prim = GL_TRIANGLE_FAN;
            break;

        default:
            NOTREACHED();
            break;
    }

    // Draw the vertices with the specified primitive type.
    // GL_CHECK(glBindVertexArray(m_vertexArrayObject));
    // GL_CHECK(glDrawArrays(prim, 0, static_cast<GLint>(m_vertices.size())));
    canvas->render(0, m_vertexArrayObject, prim, 0, static_cast<GLint>(m_vertices.size()));
}

}  // namespace ca

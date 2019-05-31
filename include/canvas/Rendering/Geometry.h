
#ifndef CANVAS_RENDERING_GEOMETRY_H_
#define CANVAS_RENDERING_GEOMETRY_H_

#include "Canvas.h"
#include "Vertex.h"
#include "VertexBufferObject.h"
#include "canvas/Utils/Color.h"
#include "canvas/Utils/Rect.h"
#include "nucleus/Macros.h"

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
  void addVertices(Vertex* vertices, MemSize count);

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
  nu::DynamicArray<Vertex> m_vertices;

  // The vertex array we're using.
  GLuint m_vertexArrayObject{0};

  // The vertex buffer we use to upload the vertex data to the GPU.
  VertexBufferObject m_vbo;

  // Whether the vertex data was compiled or not.
  bool m_compiled{false};
};

}  // namespace ca

#endif  // CANVAS_RENDERING_GEOMETRY_H_

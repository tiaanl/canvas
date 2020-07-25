#ifndef CANVAS_RENDERER_IMMEDIATE_RENDERER_H_
#define CANVAS_RENDERER_IMMEDIATE_RENDERER_H_

#include "canvas/Math/Mat4.h"
#include "canvas/Math/Vec3.h"
#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Color.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"

namespace ca {

class Renderer;

class ImmediateRenderer {
public:
  NU_DELETE_COPY_AND_MOVE(ImmediateRenderer);

  explicit ImmediateRenderer(Renderer* renderer);

  auto setTransform(const Mat4& transform) -> void;
  auto vertex(const Vec3& position, const Color& color) -> void;

  auto submit(DrawType drawType) -> void;
  auto reset() -> void;

private:
  struct Vertex {
    Vec3 position;
    Color color;
  };

  using VertexList = nu::DynamicArray<Vertex>;

  Renderer* m_renderer;

  ca::Mat4 m_transform = ca::Mat4::identity;

  VertexList m_vertices;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_IMMEDIATE_RENDERER_H_

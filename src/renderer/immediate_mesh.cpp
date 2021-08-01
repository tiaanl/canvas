#include "canvas/renderer/immediate_mesh.h"

namespace ca {

ImmediateMesh::ImmediateMesh(ImmediateRenderer* immediate_renderer, DrawType draw_type,
                             const fl::Mat4& transform)
  : immediate_renderer_{immediate_renderer}, draw_type_{draw_type}, transform_{transform} {}

ImmediateMesh& ImmediateMesh::transform(const fl::Mat4& transform) {
  transform_ = transform;

  return *this;
}

ImmediateMesh& ImmediateMesh::vertex(const fl::Vec3& position, const Color& color) {
  vertices_.emplaceBack(position, color);

  return *this;
}

}  // namespace ca

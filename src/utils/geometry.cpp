#include "canvas/utils/geometry.h"

namespace ca {

Geometry create_rectangle(Renderer* renderer, const fl::Vec2& top_left,
                          const fl::Vec2& bottom_right) {
  static PositionTextureCoords vertices[] = {
      {
          {top_left.x, top_left.y, 0.0f},
          {0.0f, 0.0f},
      },
      {
          {bottom_right.x, top_left.y, 0.0f},
          {1.0f, 0.0f},
      },
      {
          {bottom_right.x, bottom_right.y, 0.0f},
          {1.0f, 1.0f},
      },
      {
          {top_left.x, bottom_right.y, 0.0f},
          {0.0f, 1.0f},
      },
  };

  static U16 indices[] = {0, 1, 2, 2, 3, 0};

  auto def = VertexDefinition{};
  def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
  def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);

  auto vertex_buffer_id = renderer->createVertexBuffer(def, vertices, sizeof(vertices));
  if (!isValid(vertex_buffer_id)) {
    LOG(Error) << "Could not create index buffer.";
    return {};
  }

  auto index_buffer_id =
      renderer->createIndexBuffer(ca::ComponentType::Unsigned16, indices, sizeof(indices));

  if (!isValid(index_buffer_id)) {
    LOG(Error) << "Could not create index buffer.";
    return {};
  }

  return {vertex_buffer_id, index_buffer_id, 6};
}

}  // namespace ca

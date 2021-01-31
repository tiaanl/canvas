
#include "canvas/Utils/Geometry.h"

#include "nucleus/Logging.h"

namespace ca {

Geometry createRectangle(Renderer* renderer, const fl::Vec2& topLeft, const fl::Vec2& bottomRight) {
  static PositionTextureCoords vertices[] = {
      {
          {topLeft.x, topLeft.y, 0.0f},
          {0.0f, 0.0f},
      },
      {
          {bottomRight.x, topLeft.y, 0.0f},
          {1.0f, 0.0f},
      },
      {
          {bottomRight.x, bottomRight.y, 0.0f},
          {1.0f, 1.0f},
      },
      {
          {topLeft.x, bottomRight.y, 0.0f},
          {0.0f, 1.0f},
      },
  };

  static U16 indices[] = {0, 1, 2, 2, 3, 0};

  auto def = VertexDefinition{};
  def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
  def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);

  auto vertexBufferId = renderer->createVertexBuffer(def, vertices, sizeof(vertices));
  if (!isValid(vertexBufferId)) {
    LOG(Error) << "Could not create index buffer.";
    return {};
  }

  auto indexBufferId =
      renderer->createIndexBuffer(ca::ComponentType::Unsigned16, indices, sizeof(indices));

  if (!isValid(indexBufferId)) {
    LOG(Error) << "Could not create index buffer.";
    return {};
  }

  return {vertexBufferId, indexBufferId, 6};
}

}  // namespace ca

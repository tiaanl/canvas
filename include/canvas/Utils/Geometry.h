
#ifndef CANVAS_UTILS_GEOMETRY_H_
#define CANVAS_UTILS_GEOMETRY_H_

#include "canvas/Math/Vec2.h"
#include "canvas/Math/Vec3.h"
#include "canvas/Renderer/Renderer.h"

namespace ca {

struct PositionTextureCoords {
  Vec3 position;
  Vec2 textureCoords;
};

struct Geometry {
  VertexBufferId vertexBufferId;
  IndexBufferId indexBufferId;
  U32 indexCount;
};

inline bool isValid(const Geometry& geometry) {
  return isValid(geometry.vertexBufferId) && isValid(geometry.indexBufferId);
}

Geometry createRectangle(Renderer* renderer, const Vec2& topLeft, const Vec2& bottomRight);

}  // namespace ca

#endif  // CANVAS_UTILS_GEOMETRY_H_

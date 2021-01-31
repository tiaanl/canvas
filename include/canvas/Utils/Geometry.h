
#ifndef CANVAS_UTILS_GEOMETRY_H_
#define CANVAS_UTILS_GEOMETRY_H_

#include "canvas/Renderer/Renderer.h"
#include "floats/Vec2.h"
#include "floats/Vec3.h"

namespace ca {

struct PositionTextureCoords {
  fl::Vec3 position;
  fl::Vec2 textureCoords;
};

struct Geometry {
  VertexBufferId vertexBufferId;
  IndexBufferId indexBufferId;
  U32 indexCount;
};

inline bool isValid(const Geometry& geometry) {
  return isValid(geometry.vertexBufferId) && isValid(geometry.indexBufferId);
}

Geometry createRectangle(Renderer* renderer, const fl::Vec2& topLeft, const fl::Vec2& bottomRight);

}  // namespace ca

#endif  // CANVAS_UTILS_GEOMETRY_H_

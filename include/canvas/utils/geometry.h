#pragma once

#include "canvas/renderer/renderer.h"
#include "floats/vec2.h"
#include "floats/vec3.h"

namespace ca {

struct PositionTextureCoords {
  fl::Vec3 position;
  fl::Vec2 texture_coords;
};

struct Geometry {
  VertexBufferId vertex_buffer_id;
  IndexBufferId index_buffer_id;
  U32 index_count = 0;
};

inline bool is_valid(const Geometry& geometry) {
  return geometry.vertex_buffer_id.is_valid() && geometry.index_buffer_id.is_valid();
}

Geometry create_rectangle(Renderer* renderer, const fl::Vec2& top_left,
                          const fl::Vec2& bottom_right);

}  // namespace ca

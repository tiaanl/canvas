
#ifndef CANVAS_RENDERING_VERTEX_H_
#define CANVAS_RENDERING_VERTEX_H_

#include "canvas/math/vec3.h"
#include "canvas/utils/color.h"

namespace ca {

struct Vertex {
  Vec3 pos;
  Vec2 texCoords;
  Color color;
};

}  // namespace ca

#endif  // CANVAS_RENDERING_VERTEX_H_

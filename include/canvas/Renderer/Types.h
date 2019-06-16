#ifndef CANVAS_RENDERER_TYPES_H_
#define CANVAS_RENDERER_TYPES_H_

#include "nucleus/Types.h"

#include <limits>

namespace ca {

constexpr MemSize kInvalidResourceId = std::numeric_limits<MemSize>::max();

#define DECLARE_RESOURCE_ID(Name)                                                                  \
  struct Name##Id {                                                                                \
    MemSize id = kInvalidResourceId;                                                               \
  };                                                                                               \
                                                                                                   \
  inline bool isValid(const Name##Id& resource) {                                                  \
    return resource.id != kInvalidResourceId;                                                      \
  }

DECLARE_RESOURCE_ID(Program);
DECLARE_RESOURCE_ID(VertexBuffer);
DECLARE_RESOURCE_ID(IndexBuffer);
DECLARE_RESOURCE_ID(Texture);

enum class ComponentType : U32 {
  Float32 = 0,
  Signed8,
  Unsigned8,
  Signed16,
  Unsigned16,
  Signed32,
  Unsigned32,
};

enum class ComponentCount : U32 {
  One = 1,
  Two = 2,
  Three = 3,
  Four = 4,
};

enum class DrawType : U32 {
  Triangles,
  TriangleStrip,
  TriangleFan,
};

}  // namespace ca

#endif  // CANVAS_RENDERER_TYPES_H_

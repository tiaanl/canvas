#ifndef CANVAS_RENDERER_TYPES_H_
#define CANVAS_RENDERER_TYPES_H_

#include <limits>

#include "nucleus/Streams/OutputStream.h"
#include "nucleus/Types.h"

namespace ca {

constexpr MemSize kInvalidResourceId = std::numeric_limits<MemSize>::max();

#define DECLARE_RESOURCE_ID(Name)                                                                  \
  struct Name##Id {                                                                                \
    MemSize id;                                                                                    \
    bool isValid() const {                                                                         \
      return id != kInvalidResourceId;                                                             \
    }                                                                                              \
  };                                                                                               \
                                                                                                   \
  inline bool isValid(const Name##Id& resource) {                                                  \
    return resource.isValid();                                                                     \
  }

DECLARE_RESOURCE_ID(Program)
DECLARE_RESOURCE_ID(VertexBuffer)
DECLARE_RESOURCE_ID(IndexBuffer)
DECLARE_RESOURCE_ID(Texture)
DECLARE_RESOURCE_ID(Uniform)

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

  Lines,
  LineStrip,
};

enum class TextureFormat : U32 {
  Unknown,
  Alpha,
  RGB,
  RGBA,
};

}  // namespace ca

#endif  // CANVAS_RENDERER_TYPES_H_

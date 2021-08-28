#pragma once

#include <limits>

#include "nucleus/streams/output_stream.h"
#include "nucleus/types.h"

constexpr MemSize INVALID_RESOURCE_ID = std::numeric_limits<MemSize>::max();

namespace ca {

#define DECLARE_RESOURCE_ID(Name)                                                                  \
  struct Name##Id {                                                                                \
    MemSize id = ::INVALID_RESOURCE_ID;                                                            \
    bool is_valid() const {                                                                        \
      return id != ::INVALID_RESOURCE_ID;                                                          \
    }                                                                                              \
  };                                                                                               \
  inline bool operator==(Name##Id left, Name##Id right) {                                          \
    return left.id == right.id;                                                                    \
  }                                                                                                \
  inline bool operator!=(Name##Id left, Name##Id right) {                                          \
    return left.id != right.id;                                                                    \
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
  Points,

  Lines,
  LineStrip,

  Triangles,
  TriangleStrip,
  TriangleFan,
};

enum class TextureFormat : U32 {
  Unknown,
  Alpha,
  RGB,
  RGBA,
};

}  // namespace ca

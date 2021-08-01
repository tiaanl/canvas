#pragma once

#include "canvas/renderer/types.h"
#include "canvas/utils/color.h"

namespace ca {

enum class CommandType : U32 {
  ClearBuffers,
  Draw,
};

struct ClearBuffersData {
  Color color;
};

struct DrawData {
  ProgramId programId;
  VertexBufferId vertexBufferId;
  IndexBufferId indexBufferId;
  TextureId textureId;
  DrawType drawType;
  U32 numIndices;

#if 0
  struct UniformEntry {
      UniformId uniformId;
      nu::DynamicArray<F32> values;
  };

  nu::DynamicArray<UniformEntry> uniforms;
#endif  // 0
};

struct Command {
  CommandType type;

  union {
    ClearBuffersData clearBuffersData;
    DrawData drawData;
  };

  explicit Command(CommandType type) : type{type} {}
};

}  // namespace ca

#ifndef CANVAS_RENDERER_COMMAND_H_
#define CANVAS_RENDERER_COMMAND_H_

#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Color.h"

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

  struct UniformEntry {
      UniformId uniformId;
      nu::DynamicArray<F32> values;
  };

  nu::DynamicArray<UniformEntry> uniforms;
};

struct Command {
  CommandType type;

  union {
    ClearBuffersData clearBuffersData;
    DrawData drawData;
  };

  Command(CommandType type) : type{type} {}
};

}  // namespace ca

#endif  // CANVAS_RENDERER_COMMAND_H_

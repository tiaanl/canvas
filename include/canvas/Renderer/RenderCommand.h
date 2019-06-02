
#ifndef CANVAS_RENDERER_RENDER_COMMAND_H_
#define CANVAS_RENDERER_RENDER_COMMAND_H_

#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Color.h"

namespace ca {

enum class RenderCommandType : U32 {
  ClearColorBuffer,
  ClearDepthBuffer,
  RenderGeometry,
};

struct ClearColorBufferData {
  Color color;
};

struct ClearDepthBufferData {
  F32 depth;
};

struct RenderGeometryData {
  GeometryId geometryId;
  TextureId textureId;
  ProgramId programId;
};

struct RenderCommand {
  RenderCommandType type;

  union {
    ClearColorBufferData clearColorBufferData;
    ClearDepthBufferData clearDepthBufferData;
    RenderGeometryData renderGeometryData;
  };
};

}  // namespace ca

#endif  // CANVAS_RENDERER_RENDER_COMMAND_H_

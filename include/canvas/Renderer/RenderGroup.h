
#ifndef CANVAS_RENDERER_RENDER_GROUP_H_
#define CANVAS_RENDERER_RENDER_GROUP_H_

#include "canvas/Renderer/RenderCommand.h"
#include "canvas/Utils/Color.h"
#include "nucleus/Containers/DynamicArray.h"

namespace ca {

enum class RenderGroupProjection : U8 {
  Perspective = 0x01,
  Orthographic = 0x02,
};

class RenderGroup {
public:
  RenderGroup(RenderGroupProjection projection) : m_projection{projection} {}
  ~RenderGroup() = default;

  // Render the group.
  void render(RenderContext* renderContext);

  void clearColorBuffer(const Color& color);
  void clearDepthBuffer(F32 depth);
  void renderGeometry(GeometryId geometryId, TextureId textureId, ProgramId programId);

private:
  void processData(RenderContext* renderContext, ClearColorBufferData* data);
  void processData(RenderContext* renderContext, RenderGeometryData* data);

  RenderGroupProjection m_projection;
  nu::DynamicArray<RenderCommand> m_commands;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_RENDER_GROUP_H_

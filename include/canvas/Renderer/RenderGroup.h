
#ifndef CANVAS_RENDERER_RENDER_GROUP_H_
#define CANVAS_RENDERER_RENDER_GROUP_H_

#include "canvas/Renderer/RenderCommand.h"
#include "canvas/Utils/Color.h"
#include "nucleus/Containers/DynamicArray.h"

namespace ca {

class Renderer;

enum class RenderGroupProjection : U8 {
  Perspective = 0x01,
  Orthographic = 0x02,
};

class RenderGroup {
public:
  explicit RenderGroup(RenderGroupProjection projection) : m_projection{projection} {}
  ~RenderGroup() = default;

  // Render the group.
  void render(Renderer* renderer);

  void clearColorBuffer(const Color& color);
  void clearDepthBuffer(F32 depth);
  void renderGeometry(GeometryId geometryId, TextureId textureId, ProgramId programId);

private:
  // Set up all the matrices we're going to use for positioning the world.
  void setUpMatrices();

  static void processData(Renderer* renderer, ClearColorBufferData* data);
  static void processData(Renderer* renderer, RenderGeometryData* data);

  RenderGroupProjection m_projection;
  nu::DynamicArray<RenderCommand> m_commands;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_RENDER_GROUP_H_


#ifndef CANVAS_RENDERER_RENDERER_H_
#define CANVAS_RENDERER_RENDERER_H_

#include "canvas/Renderer/RenderGroup.h"
#include "canvas/Renderer/VertexDefinition.h"
#include "canvas/Utils/Size.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"

namespace ca {

class VertexDefinition;
class Image;
class ShaderSource;
class Window;

class Renderer {
public:
  Renderer() = default;

  ~Renderer() = default;

  TextureId createTexture(const Image& image);

  GeometryId createGeometry(const VertexDefinition& bufferDefinition, void* data, MemSize dataSize);

  ProgramId createProgram(const ShaderSource& vertexShader, const ShaderSource& fragmentShader);

  void beginFrame();
  void endFrame();

  RenderGroup* addRenderGroup(RenderGroupProjection projection);

private:
  COPY_DELETE(Renderer);
  MOVE_DELETE(Renderer);

  friend class RenderGroup;

  struct TextureData {
    U32 id;
    Size<I32> size;
  };

  struct GeometryData {
    U32 id;
    U32 numComponents;
  };

  struct ProgramData {
    U32 id;
  };

  nu::DynamicArray<RenderGroup> m_renderGroups;
  nu::DynamicArray<TextureData> m_textures;
  nu::DynamicArray<GeometryData> m_geometries;
  nu::DynamicArray<ProgramData> m_programs;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_RENDERER_H_

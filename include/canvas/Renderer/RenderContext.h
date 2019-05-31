
#ifndef CANVAS_RENDER_CONTEXT_H_
#define CANVAS_RENDER_CONTEXT_H_

#include "canvas/Renderer/GeometryDefinition.h"
#include "canvas/Utils/Size.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Types.h"

namespace ca {

class Image;
class ShaderSource;

using TextureId = MemSize;
using GeometryId = MemSize;
using ProgramId = MemSize;

// The `RenderContext` is a wrapper around OpenGL at this point. All storage operations to OpenGL is
// wrapped.
class RenderContext {
public:
  RenderContext() = default;

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

  const GeometryData& getGeometryData(GeometryId id) const {
    return m_geometries[id];
  }

  TextureId createTexture(const Image& image);

  template <typename T>
  GeometryId createGeometry(const GeometryDefinition& geometryDefinition, T* components,
                            MemSize numComponents) {
    return createGeometryInternal(geometryDefinition, components, sizeof(T) * numComponents,
                                  numComponents);
  }

  ProgramId createProgram(const ShaderSource& vertexShader, const ShaderSource& fragmentShader);

private:
  GeometryId createGeometryInternal(const GeometryDefinition& geometryDefinition, void* data,
                                    MemSize dataSize, MemSize numComponents);

  nu::DynamicArray<TextureData> m_textures;
  nu::DynamicArray<GeometryData> m_geometries;
  nu::DynamicArray<ProgramData> m_programs;
};

}  // namespace ca

#endif  // CANVAS_RENDER_CONTEXT_H_

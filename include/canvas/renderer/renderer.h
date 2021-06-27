#pragma once

#include "canvas/Renderer/command.h"
#include "canvas/Renderer/render_state.h"
#include "canvas/Renderer/texture_slots.h"
#include "canvas/Renderer/types.h"
#include "canvas/Renderer/uniform_buffer.h"
#include "canvas/Renderer/vertex_definition.h"
#include "canvas/Utils/shader_source.h"
#include "floats/size.h"
#include "nucleus/Containers/dynamic_array.h"

namespace ca {

class Renderer {
public:
  NU_DELETE_COPY_AND_MOVE(Renderer);

  Renderer();
  ~Renderer();

  ProgramId createProgram(const ShaderSource& vertexShader, const ShaderSource& fragmentShader);
  ProgramId createProgram(const ShaderSource& vertexShader, const ShaderSource& geometryShader,
                          const ShaderSource& fragmentShader);
  void deleteProgram(ProgramId programId);

  VertexBufferId createVertexBuffer(const VertexDefinition& bufferDefinition, const void* data,
                                    MemSize dataSize);
  void vertexBufferData(VertexBufferId id, void* data, MemSize dataSize);
  void deleteVertexBuffer(VertexBufferId id);

  IndexBufferId createIndexBuffer(ComponentType componentType, const void* data, MemSize dataSize);
  void indexBufferData(IndexBufferId id, void* data, MemSize dataSize);
  void deleteIndexBuffer(IndexBufferId id);

  TextureId createTexture(TextureFormat format, const fl::Size& size, const void* data,
                          MemSize dataSize, bool smooth = false);

  UniformId createUniform(const nu::StringView& name);

  const fl::Size& getSize() const {
    return m_size;
  }

  // Resize the rendering area. Typically called when the window is resized.
  void resize(const fl::Size& size);

  NU_NO_DISCARD RenderState& state() {
    return render_state_;
  }

  void beginFrame();
  void endFrame();

  void clear(const Color& color);

  void draw(DrawType drawType, U32 vertexOffset, U32 vertexCount, ProgramId programId,
            VertexBufferId vertexBufferId, const TextureSlots& textures,
            const UniformBuffer& uniforms);

  void draw(DrawType drawType, U32 indexCount, ProgramId programId, VertexBufferId vertexBufferId,
            IndexBufferId indexBufferId, const TextureSlots& textures,
            const UniformBuffer& uniforms);

private:
  struct ProgramData {
    U32 id;
  };

  struct VertexBufferData {
    U32 id;
  };

  struct IndexBufferData {
    U32 id;
    ComponentType componentType;
  };

  struct TextureData {
    U32 id;
    fl::Size size;
  };

  struct UniformData {
    nu::StaticString<128> name;
  };

  void pre_draw(ProgramId program_id, const TextureSlots& textures, const UniformBuffer& uniforms);
  void post_draw();

  fl::Size m_size;

  nu::DynamicArray<ProgramData> m_programs;
  nu::DynamicArray<VertexBufferData> m_vertexBuffers;
  nu::DynamicArray<IndexBufferData> m_indexBuffers;
  nu::DynamicArray<TextureData> m_textures;
  nu::DynamicArray<UniformData> m_uniforms;

  RenderState render_state_;
};

}  // namespace ca

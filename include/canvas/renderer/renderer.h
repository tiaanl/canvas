#pragma once

#include "canvas/renderer/command.h"
#include "canvas/renderer/pipeline_builder.h"
#include "canvas/renderer/render_state.h"
#include "canvas/renderer/texture_slots.h"
#include "canvas/renderer/types.h"
#include "canvas/renderer/uniform_buffer.h"
#include "canvas/renderer/vertex_definition.h"
#include "canvas/utils/shader_source.h"
#include "floats/size.h"
#include "nucleus/containers/dynamic_array.h"

namespace ca {

class Renderer {
public:
  NU_DELETE_COPY_AND_MOVE(Renderer);

  Renderer();
  ~Renderer();

  ProgramId create_program(const ShaderSource& vertexShader, const ShaderSource& fragmentShader);
  ProgramId create_program(const ShaderSource& vertexShader, const ShaderSource& geometryShader,
                           const ShaderSource& fragmentShader);
  void delete_program(ProgramId programId);

  VertexBufferId create_vertex_buffer(const VertexDefinition& bufferDefinition, const void* data,
                                      MemSize dataSize);
  void vertex_buffer_data(VertexBufferId id, void* data, MemSize dataSize);
  void delete_vertex_buffer(VertexBufferId id);

  IndexBufferId create_index_buffer(ComponentType componentType, const void* data,
                                    MemSize dataSize);
  void index_buffer_data(IndexBufferId id, void* data, MemSize dataSize);
  void delete_index_buffer(IndexBufferId id);

  TextureId create_texture(TextureFormat format, const fl::Size& size, const void* data,
                           MemSize dataSize, bool smooth = false);

  UniformId create_uniform(const nu::StringView& name);

  NU_NO_DISCARD PipelineBuilder create_pipeline_builder() const;

  NU_NO_DISCARD const fl::Size& size() const {
    return size_;
  }

  // Resize the rendering area. Usually called when the window is resized.
  void resize(const fl::Size& size);

  NU_NO_DISCARD RenderState& state() {
    return render_state_;
  }

  void begin_frame();
  void end_frame();

  void clear(const Color& color);

  void draw(DrawType draw_type, U32 vertex_offset, U32 vertex_count, ProgramId program_id,
            VertexBufferId vertex_buffer_id, const TextureSlots& textures = {},
            const UniformBuffer& uniforms = {});

  void draw(DrawType draw_type, U32 index_count, ProgramId program_id,
            VertexBufferId vertex_buffer_id, IndexBufferId index_buffer_id,
            const TextureSlots& textures = {}, const UniformBuffer& uniforms = {});

private:
  struct ProgramData {
    U32 id = 0;
  };

  struct VertexBufferData {
    U32 id = 0;
  };

  struct IndexBufferData {
    U32 id = 0;
    ComponentType component_type;
  };

  struct TextureData {
    U32 id = 0;
    fl::Size size;
  };

  struct UniformData {
    nu::StaticString<128> name;
  };

  void pre_draw(ProgramId program_id, const TextureSlots& textures, const UniformBuffer& uniforms);
  void post_draw();

  fl::Size size_;

  nu::DynamicArray<ProgramData> programs_;
  nu::DynamicArray<VertexBufferData> vertex_buffers_;
  nu::DynamicArray<IndexBufferData> index_buffers_;
  nu::DynamicArray<TextureData> textures_;
  nu::DynamicArray<UniformData> uniforms_;

  RenderState render_state_;
};

}  // namespace ca

#pragma once

#include "canvas/renderer/texture_slots.h"
#include "canvas/renderer/uniform_buffer.h"
#include "canvas/renderer/vertex_definition.h"

namespace ca {

class PipelineBuilder;
class Renderer;

class Pipeline {
public:
  VertexBufferId create_vertex_buffer(const void* data, MemSize dataSize) const;

  void draw(DrawType draw_type, U32 vertex_offset, U32 vertex_count,
            VertexBufferId vertex_buffer_id, const TextureSlots& textures,
            const UniformBuffer& uniforms);

  void draw(DrawType draw_type, U32 index_count, VertexBufferId vertex_buffer_id,
            IndexBufferId index_buffer_id, const TextureSlots& textures,
            const UniformBuffer& uniforms);

private:
  friend class PipelineBuilder;

  Pipeline(Renderer* renderer, VertexDefinition vertex_definition, ProgramId program_id);

  Renderer* renderer_;
  VertexDefinition vertex_definition_;
  ProgramId program_id_;
};

}  // namespace ca

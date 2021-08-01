#include "canvas/renderer/pipeline.h"

#include "canvas/renderer/renderer.h"

namespace ca {

VertexBufferId Pipeline::create_vertex_buffer(const void* data, MemSize dataSize) const {
  return renderer_->createVertexBuffer(vertex_definition_, data, dataSize);
}

void Pipeline::draw(DrawType draw_type, U32 vertex_offset, U32 vertex_count,
                    VertexBufferId vertex_buffer_id, const TextureSlots& textures,
                    const UniformBuffer& uniforms) {
  renderer_->draw(draw_type, vertex_offset, vertex_count, program_id_, vertex_buffer_id, textures,
                  uniforms);
}

void Pipeline::draw(DrawType draw_type, U32 index_count, VertexBufferId vertex_buffer_id,
                    IndexBufferId index_buffer_id, const TextureSlots& textures,
                    const UniformBuffer& uniforms) {
  renderer_->draw(draw_type, index_count, program_id_, vertex_buffer_id, index_buffer_id, textures,
                  uniforms);
}

Pipeline::Pipeline(Renderer* renderer, VertexDefinition vertex_definition, ProgramId program_id)
  : renderer_{renderer},
    vertex_definition_{std::move(vertex_definition)},
    program_id_{program_id} {}

}  // namespace ca

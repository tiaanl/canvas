
#include "canvas/Renderer/Encoder.h"

#include "canvas/Math/Mat4.h"
#include "canvas/Math/Vec2.h"
#include "canvas/Math/Vec3.h"
#include "canvas/Math/Vec4.h"
#include "canvas/Renderer/Command.h"
#include "canvas/Renderer/Renderer.h"

namespace ca {

void CommandBuilder::submit() {
  m_renderer->pushCommand(m_command);
}

void DrawCommandBuilder::submit() {
  DCHECK(isValid(m_command.drawData.programId)) << "Program must be specified";
  DCHECK(isValid(m_command.drawData.vertexBufferId)) << "Vertex buffer must be specified";
  DCHECK(isValid(m_command.drawData.indexBufferId)) << "Index buffer must be specified";
  DCHECK(m_command.drawData.numIndices > 0) << "numIndices must be specified";

  CommandBuilder::submit();
}

#if 0

NewEncoder::NewEncoder(Renderer* renderer)
  : m_stream{renderer->m_commandBuffer}, m_uniformCount{0}, m_uniformCommandBufferStream{
                                                                m_uniformCommandBuffer} {
  reset();
}

NewEncoder& NewEncoder::program(ProgramId programId) {
  m_programId = programId;

  return *this;
}

NewEncoder& NewEncoder::vertexBuffer(VertexBufferId vertexBufferId) {
  m_vertexBufferId = vertexBufferId;

  return *this;
}

NewEncoder& NewEncoder::indexBuffer(IndexBufferId indexBufferId) {
  m_indexBufferId = indexBufferId;

  return *this;
}

NewEncoder& NewEncoder::texture(TextureId textureId) {
  m_textureId = textureId;

  return *this;
}

NewEncoder& NewEncoder::uniform(UniformId uniformId, F32 value) {
  m_uniformCommandBufferStream.writeU32(1);
  m_uniformCommandBufferStream.writeF32(value);
  return *this;
}

NewEncoder& NewEncoder::uniform(UniformId uniformId, const Vec2& value) {
  m_uniformCommandBufferStream.writeU32(2);
  m_uniformCommandBufferStream.writeF32(value.x);
  m_uniformCommandBufferStream.writeF32(value.y);
  return *this;
}

NewEncoder& NewEncoder::uniform(UniformId uniformId, const Vec3& value) {
  m_uniformCommandBufferStream.writeU32(3);
  m_uniformCommandBufferStream.writeF32(value.x);
  m_uniformCommandBufferStream.writeF32(value.y);
  m_uniformCommandBufferStream.writeF32(value.z);
  return *this;
}

NewEncoder& NewEncoder::uniform(UniformId uniformId, const Vec4& value) {
  m_uniformCommandBufferStream.writeU32(4);
  m_uniformCommandBufferStream.writeF32(value.x);
  m_uniformCommandBufferStream.writeF32(value.y);
  m_uniformCommandBufferStream.writeF32(value.z);
  m_uniformCommandBufferStream.writeF32(value.w);
  return *this;
}

NewEncoder& NewEncoder::uniform(UniformId uniformId, const Mat4& value) {
  m_uniformCommandBufferStream.writeU32(16);
  for (auto i : value.col) {
    m_uniformCommandBufferStream.writeF32(i.x);
    m_uniformCommandBufferStream.writeF32(i.y);
    m_uniformCommandBufferStream.writeF32(i.z);
    m_uniformCommandBufferStream.writeF32(i.w);
  }
  return *this;
}

void NewEncoder::submit() {
  m_stream.writeU64(static_cast<U64>(m_programId.id));
  m_stream.writeU64(static_cast<U64>(m_vertexBufferId.id));
  m_stream.writeU64(static_cast<U64>(m_indexBufferId.id));
  m_stream.writeU64(static_cast<U64>(m_textureId.id));
  m_stream.writeU32(static_cast<U32>(m_uniformCount));
  m_stream.writeBuffer(m_uniformCommandBuffer);

  reset();
}

void NewEncoder::reset() {
  m_programId = ProgramId{};
  m_vertexBufferId = VertexBufferId{};
  m_indexBufferId = IndexBufferId{};
  m_textureId = TextureId{};
  m_uniformCommandBuffer.clear();
}
#endif  // 0

}  // namespace ca

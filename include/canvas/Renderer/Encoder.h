#ifndef CANVAS_RENDERER_ENCODER_H_
#define CANVAS_RENDERER_ENCODER_H_

#include "canvas/Renderer/Command.h"
#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Color.h"
#include "nucleus/Macros.h"
#include "nucleus/Streams/WrappedDynamicArrayOutputStream.h"

namespace ca {

class Mat4;
class Renderer;
class Vec2;
class Vec3;
class Vec4;

class CommandBuilder {
public:
  void submit();

protected:
  CommandBuilder(Renderer* renderer, CommandType commandType)
    : m_renderer{renderer}, m_command{commandType} {}

  Renderer* m_renderer;
  Command m_command;

public:
  friend class Encoder;
};

class ClearBuffersCommandBuilder : public CommandBuilder {
public:
  ClearBuffersCommandBuilder(Renderer* renderer)
    : CommandBuilder{renderer, CommandType::ClearBuffers} {}

  ClearBuffersCommandBuilder& color(const Color& color) {
    m_command.clearBuffersData.color = color;
    return *this;
  }
};

class DrawCommandBuilder : public CommandBuilder {
public:
  DrawCommandBuilder(Renderer* renderer) : CommandBuilder{renderer, CommandType::Draw} {}

  DrawCommandBuilder& programId(ProgramId programId) {
    m_command.drawData.programId = programId;
    return *this;
  }

  DrawCommandBuilder& vertexBufferId(VertexBufferId vertexBufferId) {
    m_command.drawData.vertexBufferId = vertexBufferId;
    return *this;
  }

  DrawCommandBuilder& indexBufferId(IndexBufferId indexBufferId) {
    m_command.drawData.indexBufferId = indexBufferId;
    return *this;
  }

  DrawCommandBuilder& textureId(TextureId textureId) {
    m_command.drawData.textureId = textureId;
    return *this;
  }

  DrawCommandBuilder& drawType(DrawType drawType) {
    m_command.drawData.drawType = drawType;
    return *this;
  }

  DrawCommandBuilder& numIndices(U32 numIndices) {
    m_command.drawData.numIndices = numIndices;
    return *this;
  }

  void submit();
};

class Encoder {
public:
  explicit Encoder(Renderer* renderer) : m_renderer{renderer} {}

  ClearBuffersCommandBuilder clearBuffers() {
    return ClearBuffersCommandBuilder{m_renderer};
  }

  DrawCommandBuilder draw() {
    return DrawCommandBuilder{m_renderer};
  }

private:
  DELETE_COPY_AND_MOVE(Encoder);

  Renderer* m_renderer;
};

#if 0
class NewEncoder {
public:
  explicit NewEncoder(Renderer* renderer);

  NewEncoder& program(ProgramId programId);
  NewEncoder& vertexBuffer(VertexBufferId vertexBufferId);
  NewEncoder& indexBuffer(IndexBufferId indexBufferId);
  NewEncoder& texture(TextureId textureId);
  NewEncoder& uniform(UniformId uniformId, F32 value);
  NewEncoder& uniform(UniformId uniformId, const Vec2& value);
  NewEncoder& uniform(UniformId uniformId, const Vec3& value);
  NewEncoder& uniform(UniformId uniformId, const Vec4& value);
  NewEncoder& uniform(UniformId uniformId, const Mat4& value);

  void submit();

private:
  DELETE_COPY_AND_MOVE(NewEncoder);

  nu::WrappedDynamicArrayOutputStream m_stream;

  ProgramId m_programId;
  VertexBufferId m_vertexBufferId;
  IndexBufferId m_indexBufferId;
  TextureId m_textureId;

  U32 m_uniformCount;
  nu::DynamicArray<U8> m_uniformCommandBuffer;
  nu::WrappedDynamicArrayOutputStream m_uniformCommandBufferStream;
  void reset();
};
#endif  // 0

}  // namespace ca

#endif  // CANVAS_RENDERER_ENCODER_H_

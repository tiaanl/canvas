#ifndef CANVAS_RENDERER_ENCODER_H_
#define CANVAS_RENDERER_ENCODER_H_

#include "canvas/Renderer/Command.h"
#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Color.h"
#include "nucleus/Macros.h"

namespace ca {

class Renderer;

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

}  // namespace ca

#endif  // CANVAS_RENDERER_ENCODER_H_

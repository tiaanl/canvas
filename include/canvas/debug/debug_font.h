#pragma once

#include "canvas/renderer/types.h"
#include "canvas/renderer/uniform_buffer.h"
#include "floats/mat4.h"
#include "floats/pos.h"
#include "nucleus/macros.h"
#include "nucleus/text/string_view.h"

namespace ca {

class Renderer;

class DebugFont {
public:
  NU_DELETE_COPY_AND_MOVE(DebugFont);

  explicit DebugFont(Renderer* renderer);

  bool initialize();

  void drawText(const fl::Mat4& transform, const fl::Pos& position, nu::StringView text);

private:
  Renderer* m_renderer;

  VertexBufferId m_vertexBufferId;
  TextureId m_textureId;
  ProgramId m_programId;
  UniformId m_transformUniformId;
};

}  // namespace ca

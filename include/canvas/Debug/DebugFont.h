#ifndef CANVAS_DEBUG_DEBUG_FONT_H_
#define CANVAS_DEBUG_DEBUG_FONT_H_

#include "canvas/Renderer/Types.h"
#include "canvas/Renderer/UniformBuffer.h"
#include "floats/Mat4.h"
#include "floats/Pos.h"
#include "nucleus/Macros.h"
#include "nucleus/Text/StringView.h"

namespace ca {

class Renderer;

class DebugFont {
public:
  NU_DELETE_COPY_AND_MOVE(DebugFont);

  explicit DebugFont(Renderer* renderer);

  auto initialize() -> bool;

  auto drawText(const fl::Mat4& transform, const fl::Pos& position, const nu::StringView& text)
      -> void;

private:
  Renderer* m_renderer;

  VertexBufferId m_vertexBufferId;
  TextureId m_textureId;
  ProgramId m_programId;
  UniformId m_transformUniformId;
};

}  // namespace ca

#endif  // CANVAS_DEBUG_DEBUG_FONT_H_

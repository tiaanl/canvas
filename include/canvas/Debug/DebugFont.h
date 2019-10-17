#ifndef CANVAS_DEBUG_DEBUG_FONT_H_
#define CANVAS_DEBUG_DEBUG_FONT_H_

#include "canvas/Math/Mat4.h"
#include "canvas/Renderer/Types.h"
#include "canvas/Renderer/UniformBuffer.h"
#include "canvas/Utils/Pos.h"
#include "nucleus/Macros.h"
#include "nucleus/Text/StringView.h"

namespace ca {

class Renderer;

class DebugFont {
public:
  explicit DebugFont(Renderer* renderer);

  auto initialize() -> bool;

  auto drawText(const Mat4& transform, const Pos& position, const nu::StringView& text) -> void;

private:
  DELETE_COPY_AND_MOVE(DebugFont);

  Renderer* m_renderer;

  VertexBufferId m_vertexBufferId{kInvalidResourceId};
  TextureId m_textureId{kInvalidResourceId};
  ProgramId m_programId{kInvalidResourceId};
  UniformId m_transformUniformId{kInvalidResourceId};
};

}  // namespace ca

#endif  // CANVAS_DEBUG_DEBUG_FONT_H_

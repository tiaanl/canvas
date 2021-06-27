#pragma once

#include <floats/size.h>
#include <nucleus/profiling.h>

#include "canvas/Debug/debug_font.h"
#include "nucleus/macros.h"

namespace ca {

class Renderer;

class DebugInterface {
public:
  NU_DELETE_COPY_AND_MOVE(DebugInterface);

  DebugInterface(Renderer* renderer, fl::Size size);

  auto initialize() -> bool;

  auto resize(fl::Size size) -> void;

  auto render(F64 fps) -> void;

private:
  auto drawProfileBlock(nu::detail::ProfileMetrics::Block* block, const fl::Pos& position,
                        const fl::Mat4& transform, I32 indent = 0) -> I32;

  // Renderer* m_renderer;
  fl::Size m_size;
  DebugFont m_debugFont;
};

}  // namespace ca

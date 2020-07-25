#ifndef CANVAS_DEBUG_DEBUG_INTERFACE_H_
#define CANVAS_DEBUG_DEBUG_INTERFACE_H_

#include <nucleus/Profiling.h>

#include "canvas/Debug/DebugFont.h"
#include "nucleus/Macros.h"

namespace ca {

class Renderer;

class DebugInterface {
public:
  NU_DELETE_COPY_AND_MOVE(DebugInterface);

  DebugInterface(Renderer* renderer, Size size);

  auto initialize() -> bool;

  auto resize(Size size) -> void;

  auto render(F32 fps) -> void;

private:
  auto drawProfileBlock(nu::detail::ProfileMetrics::Block* block, const Pos& position,
                        const ca::Mat4& transform, I32 indent = 0) -> I32;

  // Renderer* m_renderer;
  Size m_size;
  DebugFont m_debugFont;
};

}  // namespace ca

#endif  // CANVAS_DEBUG_DEBUG_INTERFACE_H_

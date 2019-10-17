#ifndef CANVAS_DEBUG_DEBUG_INTERFACE_H_
#define CANVAS_DEBUG_DEBUG_INTERFACE_H_

#include <nucleus/Profiling.h>

#include "canvas/Debug/DebugFont.h"
#include "nucleus/Macros.h"

namespace ca {

class Renderer;

class DebugInterface {
public:
  explicit DebugInterface(Renderer* renderer);

  auto initialize() -> bool;

  auto render() -> void;

private:
  DELETE_COPY_AND_MOVE(DebugInterface);

  auto drawProfileBlock(nu::Profiler::Block* block, const Pos& position, const ca::Mat4& transform)
      -> I32;

  Renderer* m_renderer;
  DebugFont m_debugFont;
};

}  // namespace ca

#endif  // CANVAS_DEBUG_DEBUG_INTERFACE_H_

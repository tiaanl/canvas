#include "canvas/Debug/DebugInterface.h"

#include "canvas/Math/Transform.h"
#include "canvas/Renderer/Renderer.h"
#include "nucleus/Profiling.h"

namespace ca {

DebugInterface::DebugInterface(Renderer* renderer) : m_renderer{renderer}, m_debugFont{renderer} {}

auto DebugInterface::initialize() -> bool {
  return m_debugFont.initialize();
}

auto DebugInterface::render() -> void {
  // Set up an orthographic view projection.
  auto projection = orthographicProjection(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);

  auto profiler = nu::getGlobalProfiler();

  drawProfileBlock(profiler->root(), Pos{10, 10}, projection);
  //
  //  I32 top = 30;
  //  I32 indent = 10;
  //  for (auto current = profiler->root(); current; current = current->next) {
  //    m_debugFont.drawText(projection, Pos{indent, top}, current->name);
  //
  //    top += 14;
  //  }
}

auto DebugInterface::drawProfileBlock(nu::Profiler::Block* block, const Pos& position,
                                      const ca::Mat4& transform) -> I32 {
  auto currentPosition = position;
  for (auto* current = block; current; current = current->next) {
    m_debugFont.drawText(transform, position, current->name);

    currentPosition.y += 16;

    if (current->children) {
      currentPosition.y += drawProfileBlock(
          current->children, Pos{currentPosition.x + 10, currentPosition.y}, transform);
    }
  }

  return currentPosition.y - position.y;
}

}  // namespace ca

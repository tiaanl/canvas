#include "canvas/Debug/DebugInterface.h"

#include "canvas/Math/Transform.h"
#include "canvas/Renderer/Renderer.h"
#include "nucleus/Profiling.h"

#include <cstdio>

namespace ca {

DebugInterface::DebugInterface(Renderer* renderer) : m_renderer{renderer}, m_debugFont{renderer} {}

auto DebugInterface::initialize() -> bool {
  return m_debugFont.initialize();
}

auto DebugInterface::render() -> void {
  // Set up an orthographic view projection.
  auto projection = orthographicProjection(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);

  auto profiler = nu::detail::getCurrentProfileMetrics();

  drawProfileBlock(profiler->root(), Pos{350, 10}, projection);
}

auto DebugInterface::drawProfileBlock(nu::detail::ProfileMetrics::Block* block, const Pos& position,
                                      const ca::Mat4& transform, I32 indent) -> I32 {
  auto currentPosition = position;

  for (auto* current = block; current; current = current->next) {
    nu::StaticString<128> line;
    line.append(current->name);

    char buffer[64];
    sprintf_s(buffer, sizeof(buffer), "%.2f", current->stopTime - current->startTime);
    line.append("  ");
    line.append(buffer);

    m_debugFont.drawText(transform, currentPosition, line);

    currentPosition.y += 16;

    if (current->children) {
      currentPosition.y += drawProfileBlock(
          current->children, Pos{currentPosition.x + 10, currentPosition.y}, transform, indent + 1);
    }
  }

  return currentPosition.y - position.y;
}

}  // namespace ca

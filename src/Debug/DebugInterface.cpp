#include "canvas/Debug/DebugInterface.h"

#include <cstdio>

#include "canvas/Math/Transform.h"
#include "canvas/Renderer/Renderer.h"
#include "nucleus/Profiling.h"

namespace ca {

DebugInterface::DebugInterface(Renderer* renderer, Size size)
  : m_size{size}, m_debugFont{renderer} {}

auto DebugInterface::initialize() -> bool {
  return m_debugFont.initialize();
}

auto DebugInterface::resize(ca::Size size) -> void {
  m_size = size;
}

auto DebugInterface::render(F64 fps) -> void {
  // Set up an orthographic view projection.
  auto projection = orthographicProjection(0.0f, static_cast<F32>(m_size.width), 0.0f,
                                           static_cast<F32>(m_size.height), -1.0f, 1.0f);

  char buf[64];
  sprintf_s(buf, "%.1lf", fps);
  m_debugFont.drawText(projection, {10, 10}, buf);

  return;

  auto* profiler = nu::detail::getCurrentProfileMetrics();

  drawProfileBlock(profiler->root(), Pos{350, 10}, projection);
}

auto DebugInterface::drawProfileBlock(nu::detail::ProfileMetrics::Block* block, const Pos& position,
                                      const ca::Mat4& transform, I32 indent) -> I32 {
  auto currentPosition = position;

  for (auto* current = block; current; current = current->next) {
    nu::StaticString<128> line;
    line.append(current->name.view());

    char buffer[64];
#if OS(WIN)
    sprintf_s(buffer, sizeof(buffer), "%.2f", current->stopTime - current->startTime);
#else
    sprintf(buffer, "%.2f", current->stopTime - current->startTime);
#endif
    line.append("  ");
    line.append(buffer);

    m_debugFont.drawText(transform, currentPosition, line.view());

    currentPosition.y += 16;

    if (current->children) {
      currentPosition.y += drawProfileBlock(
          current->children, Pos{currentPosition.x + 10, currentPosition.y}, transform, indent + 1);
    }
  }

  return currentPosition.y - position.y;
}

}  // namespace ca

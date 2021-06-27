#include "canvas/Debug/debug_interface.h"

#include <cstdio>

#include "canvas/Renderer/renderer.h"
#include "floats/transform.h"
#include "nucleus/profiling.h"

namespace ca {

DebugInterface::DebugInterface(Renderer* renderer, fl::Size size)
  : m_size{size}, m_debugFont{renderer} {}

auto DebugInterface::initialize() -> bool {
  return m_debugFont.initialize();
}

auto DebugInterface::resize(fl::Size size) -> void {
  m_size = size;
}

auto DebugInterface::render(F64 fps) -> void {
  // Set up an orthographic view projection.
  auto projection = fl::orthographicProjection(0.0f, static_cast<F32>(m_size.width), 0.0f,
                                               static_cast<F32>(m_size.height), -1.0f, 1.0f);

  char buf[64];
#if COMPILER(MSVC)
  sprintf_s(buf, "%.1lf", fps);
#else
  std::sprintf(buf, "%.1lf", fps);
#endif
  m_debugFont.drawText(projection, {10, 10}, buf);

  return;

  auto* profiler = nu::detail::getCurrentProfileMetrics();

  drawProfileBlock(profiler->root(), fl::Pos{350, 10}, projection);
}

auto DebugInterface::drawProfileBlock(nu::detail::ProfileMetrics::Block* block,
                                      const fl::Pos& position, const fl::Mat4& transform,
                                      I32 indent) -> I32 {
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
      currentPosition.y +=
          drawProfileBlock(current->children, fl::Pos{currentPosition.x + 10, currentPosition.y},
                           transform, indent + 1);
    }
  }

  return currentPosition.y - position.y;
}

}  // namespace ca

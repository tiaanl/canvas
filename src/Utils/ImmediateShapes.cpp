#include "canvas/Utils/ImmediateShapes.h"

#include "canvas/Math/Common.h"

namespace ca {

auto drawSquare(ImmediateRenderer* renderer, const ca::Vec3& center, F32 edgeLength,
                const Color& color) -> void {
  drawRectangle(renderer, center, edgeLength, edgeLength, color);
}

auto drawRectangle(ImmediateRenderer* renderer, const ca::Vec3& center, F32 width, F32 height,
                   const Color& color) -> void {
  const F32 halfWidth = width * 0.5f;
  const F32 halfHeight = height * 0.5f;
  renderer->vertex(center + Vec3{-halfWidth, -halfHeight, 0.0f}, color);
  renderer->vertex(center + Vec3{-halfWidth, halfHeight, 0.0f}, color);
  renderer->vertex(center + Vec3{halfWidth, halfHeight, 0.0f}, color);
  renderer->vertex(center + Vec3{halfWidth, -halfHeight, 0.0f}, color);
  renderer->vertex(center + Vec3{-halfWidth, -halfHeight, 0.0f}, color);
  renderer->submit(DrawType::LineStrip);
}

auto drawCircle(ImmediateRenderer* renderer, const ca::Vec3& center, F32 radius, I32 segments,
                const Color& color) -> void {
  drawOval(renderer, center, radius, radius, segments, color);
}

auto drawOval(ImmediateRenderer* renderer, const ca::Vec3& center, F32 verticalRadius,
              F32 horizontalRadius, I32 segments, const Color& color) -> void {
  segments = maximum(segments, 3);

  for (auto i = 0; i < segments + 1; ++i) {
    F32 d = static_cast<F32>(i) * 360.0f / static_cast<F32>(segments);
    Vec3 p{cosine(degrees(d)) * horizontalRadius, sine(degrees(d)) * verticalRadius, 0.0f};

    renderer->vertex(center + p, color);
  }

  renderer->submit(DrawType::LineStrip);
}

}  // namespace ca

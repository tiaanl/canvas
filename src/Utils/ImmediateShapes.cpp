#include "canvas/Utils/ImmediateShapes.h"

#include "floats/Common.h"

namespace ca {

auto drawSquare(ImmediateRenderer* renderer, const fl::Vec3& center, F32 edgeLength,
                const Color& color) -> void {
  drawRectangle(renderer, center, edgeLength, edgeLength, color);
}

auto drawRectangle(ImmediateRenderer* renderer, const fl::Vec3& center, F32 width, F32 height,
                   const Color& color) -> void {
  const F32 halfWidth = width * 0.5f;
  const F32 halfHeight = height * 0.5f;
  renderer->vertex(center + fl::Vec3{-halfWidth, -halfHeight, 0.0f}, color);
  renderer->vertex(center + fl::Vec3{-halfWidth, halfHeight, 0.0f}, color);
  renderer->vertex(center + fl::Vec3{halfWidth, halfHeight, 0.0f}, color);
  renderer->vertex(center + fl::Vec3{halfWidth, -halfHeight, 0.0f}, color);
  renderer->vertex(center + fl::Vec3{-halfWidth, -halfHeight, 0.0f}, color);
  renderer->submit(DrawType::LineStrip);
}

auto drawCircle(ImmediateRenderer* renderer, const fl::Vec3& center, F32 radius, I32 segments,
                const Color& color) -> void {
  drawOval(renderer, center, radius, radius, segments, color);
}

auto drawOval(ImmediateRenderer* renderer, const fl::Vec3& center, F32 verticalRadius,
              F32 horizontalRadius, I32 segments, const Color& color) -> void {
  segments = fl::maximum(segments, 3);

  for (auto i = 0; i < segments + 1; ++i) {
    F32 d = static_cast<F32>(i) * 360.0f / static_cast<F32>(segments);
    fl::Vec3 p{cosine(fl::degrees(d)) * horizontalRadius, sine(fl::degrees(d)) * verticalRadius,
               0.0f};

    renderer->vertex(center + p, color);
  }

  renderer->submit(DrawType::LineStrip);
}

}  // namespace ca

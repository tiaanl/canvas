#ifndef CANVAS_UTILS_IMMEDIATE_SHAPES_H_
#define CANVAS_UTILS_IMMEDIATE_SHAPES_H_

#include "canvas/Renderer/ImmediateRenderer.h"
#include "floats/Vec3.h"

namespace ca {

auto drawSquare(ImmediateRenderer* renderer, const fl::Vec3& center, F32 edgeLength,
                const Color& color) -> void;

auto drawRectangle(ImmediateRenderer* renderer, const fl::Vec3& center, F32 width, F32 height,
                   const Color& color) -> void;

auto drawCircle(ImmediateRenderer* renderer, const fl::Vec3& center, F32 radius, I32 segments,
                const Color& color) -> void;

auto drawOval(ImmediateRenderer* renderer, const fl::Vec3& center, F32 verticalRadius,
              F32 horizontalRadius, I32 segments, const Color& color) -> void;

}  // namespace ca

#endif  // CANVAS_UTILS_IMMEDIATE_SHAPES_H_

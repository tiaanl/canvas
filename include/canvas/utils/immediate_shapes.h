#pragma once

#include "canvas/renderer/immediate_renderer.h"
#include "floats/vec3.h"

namespace ca {

void draw_square(ImmediateRenderer* renderer, const fl::Mat4& transform, const fl::Vec3& center,
                 F32 edge_length, const Color& color);

void draw_rectangle(ImmediateRenderer* renderer, const fl::Mat4& transform, const fl::Vec3& center,
                    F32 width, F32 height, const Color& color);

void draw_cube(ImmediateRenderer* renderer, const fl::Mat4& transform, const fl::Vec3& center,
               F32 edge_length, const Color& color);

void draw_circle(ImmediateRenderer* renderer, const fl::Mat4& transform, const fl::Vec3& center,
                 F32 radius, I32 segments, const Color& color);

void draw_oval(ImmediateRenderer* renderer, const fl::Mat4& transform, const fl::Vec3& center,
               F32 vertical_radius, F32 horizontal_radius, I32 segments, const Color& color);

}  // namespace ca

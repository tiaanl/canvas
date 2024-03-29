#include "canvas/utils/immediate_shapes.h"

namespace ca {

void draw_square(ImmediateRenderer* renderer, const fl::Mat4& transform, const fl::Vec3& center,
                 F32 edge_length, const Color& color) {
  draw_rectangle(renderer, transform, center, edge_length, edge_length, color);
}

void draw_rectangle(ImmediateRenderer* renderer, const fl::Mat4& transform, const fl::Vec3& center,
                    F32 width, F32 height, const Color& color) {
  const F32 half_width = width * 0.5f;
  const F32 half_height = height * 0.5f;

  renderer->create_mesh(DrawType::LineStrip, transform)
      .vertex(center + fl::Vec3{-half_width, -half_height, 0.0f}, color)
      .vertex(center + fl::Vec3{-half_width, half_height, 0.0f}, color)
      .vertex(center + fl::Vec3{half_width, half_height, 0.0f}, color)
      .vertex(center + fl::Vec3{half_width, -half_height, 0.0f}, color)
      .vertex(center + fl::Vec3{-half_width, -half_height, 0.0f}, color);
}

void draw_cube(ImmediateRenderer* renderer, const fl::Mat4& transform, const fl::Vec3& center,
               F32 edge_length, const Color& color) {
  const F32 half = edge_length / 2.0f;

  renderer->create_mesh(DrawType::Triangles, transform)
      .vertex(center + fl::Vec3{-half, -half, -half}, color)
      .vertex(center + fl::Vec3{half, -half, -half}, color)
      .vertex(center + fl::Vec3{half, half, -half}, color);
}

void draw_circle(ImmediateRenderer* renderer, const fl::Mat4& transform, const fl::Vec3& center,
                 F32 radius, I32 segments, const Color& color) {
  draw_oval(renderer, transform, center, radius, radius, segments, color);
}

void draw_oval(ImmediateRenderer* renderer, const fl::Mat4& transform, const fl::Vec3& center,
               F32 vertical_radius, F32 horizontal_radius, I32 segments, const Color& color) {
  segments = fl::maximum(segments, 3);

  auto& mesh = renderer->create_mesh(DrawType::LineStrip, transform);

  for (auto i = 0; i < segments + 1; ++i) {
    F32 d = static_cast<F32>(i) * 360.0f / static_cast<F32>(segments);
    fl::Vec3 p{cosine(fl::degrees(d)) * horizontal_radius, sine(fl::degrees(d)) * vertical_radius,
               0.0f};

    mesh.vertex(center + p, color);
  }
}

}  // namespace ca

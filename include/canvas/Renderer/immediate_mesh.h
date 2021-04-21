#pragma once

#include <canvas/Renderer/Types.h>
#include <canvas/Utils/Color.h>
#include <floats/Mat4.h>
#include <floats/Vec3.h>
#include <nucleus/Containers/DynamicArray.h>
#include <nucleus/Macros.h>

namespace ca {

class ImmediateRenderer;

class ImmediateMesh {
  NU_DELETE_COPY(ImmediateMesh);

public:
  ImmediateMesh(ImmediateMesh&& other) = default;
  ImmediateMesh& operator=(ImmediateMesh&& other) = default;

  ImmediateMesh& transform(const fl::Mat4& transform);
  ImmediateMesh& vertex(const fl::Vec3& position, const Color& color = Color::white);

private:
  friend class ImmediateRenderer;
  friend class nu::DynamicArray<ImmediateMesh>;

  struct Vertex {
    fl::Vec3 position;
    Color color;
  };

  explicit ImmediateMesh(ImmediateRenderer* immediate_renderer, DrawType draw_type,
                         const fl::Mat4& transform = fl::Mat4::identity);

  ImmediateRenderer* immediate_renderer_;
  DrawType draw_type_;
  fl::Mat4 transform_;
  nu::DynamicArray<Vertex> vertices_;
};

}  // namespace ca

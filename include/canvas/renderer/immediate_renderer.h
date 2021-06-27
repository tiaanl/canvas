#pragma once

#include "canvas/Renderer/immediate_mesh.h"
#include "canvas/Renderer/types.h"
#include "canvas/Utils/color.h"
#include "floats/mat4.h"
#include "floats/vec3.h"
#include "nucleus/Containers/dynamic_array.h"
#include "nucleus/macros.h"

namespace ca {

class Renderer;

class ImmediateRenderer {
  NU_DELETE_COPY(ImmediateRenderer);

public:
  explicit ImmediateRenderer(Renderer* renderer);

  NU_DEFAULT_MOVE(ImmediateRenderer);

  NU_NO_DISCARD ImmediateMesh& create_mesh(DrawType draw_type,
                                           const fl::Mat4& transform = fl::Mat4::identity);

  void submit_to_renderer();

private:
  Renderer* m_renderer;
  nu::DynamicArray<ImmediateMesh> meshes_;
};

}  // namespace ca

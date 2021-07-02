#pragma once

#include "canvas/renderer/immediate_mesh.h"
#include "canvas/renderer/types.h"
#include "canvas/utils/color.h"
#include "floats/mat4.h"
#include "floats/vec3.h"
#include "nucleus/containers/dynamic_array.h"
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
  Renderer* renderer_;
  nu::DynamicArray<ImmediateMesh> meshes_;
};

}  // namespace ca

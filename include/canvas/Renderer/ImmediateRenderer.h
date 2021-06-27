#ifndef CANVAS_RENDERER_IMMEDIATE_RENDERER_H_
#define CANVAS_RENDERER_IMMEDIATE_RENDERER_H_

#include "canvas/Renderer/Types.h"
#include "canvas/Renderer/immediate_mesh.h"
#include "canvas/Utils/Color.h"
#include "floats/Mat4.h"
#include "floats/Vec3.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"

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

#endif  // CANVAS_RENDERER_IMMEDIATE_RENDERER_H_

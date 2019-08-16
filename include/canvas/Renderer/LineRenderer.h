#ifndef CANVAS_RENDERER_LINE_RENDERER_H_
#define CANVAS_RENDERER_LINE_RENDERER_H_

#include "canvas/Math/Mat4.h"
#include "canvas/Math/Vec3.h"
#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Color.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"

namespace ca {

class Renderer;

class LineRenderer {
public:
  LineRenderer();

  bool initialize(ca::Renderer* renderer);
  void beginFrame();
  void renderLine(const ca::Vec3& p1, const ca::Vec3& p2, const ca::Color& color);
  void render(const ca::Mat4& transform);

private:
  DELETE_COPY_AND_MOVE(LineRenderer);

  struct Line {
    ca::Vec3 p1;
    ca::Color color1;
    ca::Vec3 p2;
    ca::Color color2;
  };

  Renderer* m_renderer = nullptr;

  ca::VertexBufferId m_vertexBufferId;
  ca::IndexBufferId m_indexBufferId;
  ca::ProgramId m_programId;
  ca::UniformId m_transformUniformId;

  nu::DynamicArray<Line> m_lines;
  nu::DynamicArray<U16> m_lineIndices;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_LINE_RENDERER_H_

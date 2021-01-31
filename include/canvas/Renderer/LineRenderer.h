#ifndef CANVAS_RENDERER_LINE_RENDERER_H_
#define CANVAS_RENDERER_LINE_RENDERER_H_

#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Color.h"
#include "floats/Mat4.h"
#include "floats/Plane.h"
#include "floats/Vec3.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"

namespace ca {

class Renderer;

class LineRenderer {
public:
  NU_DELETE_COPY_AND_MOVE(LineRenderer);

  LineRenderer();

  bool initialize(Renderer* renderer);
  void beginFrame();

  void renderLine(const fl::Vec3& p1, const fl::Vec3& p2, const Color& color);
  void renderGrid(const fl::Plane& plane, const fl::Vec3& worldUp, const Color& color,
                  I32 numBlocks, F32 blockSize);

  void render(const fl::Mat4& transform);

private:
  struct Line {
    fl::Vec3 p1;
    Color color1;
    fl::Vec3 p2;
    Color color2;
  };

  Renderer* m_renderer = nullptr;

  VertexBufferId m_vertexBufferId;
  IndexBufferId m_indexBufferId;
  ProgramId m_programId;
  UniformId m_transformUniformId;

  nu::DynamicArray<Line> m_lines;
  nu::DynamicArray<U16> m_lineIndices;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_LINE_RENDERER_H_

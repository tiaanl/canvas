
#ifndef CANVAS_RENDERER_RENDERER_H_
#define CANVAS_RENDERER_RENDERER_H_

#include "canvas/Renderer/RenderGroup.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"

namespace ca {

class Window;

class Renderer {
public:
  Renderer(Window* window, RenderContext* renderContext)
    : m_window{window}, m_renderContext{renderContext} {}
  ~Renderer() = default;

  void beginFrame();
  void endFrame();

  RenderGroup* addRenderGroup(RenderGroupProjection projection);

private:
  COPY_DELETE(Renderer);
  MOVE_DELETE(Renderer);

  // The window we are rendering to.
  Window* m_window;

  // The renderContext connected to the window.
  RenderContext* m_renderContext;

  nu::DynamicArray<RenderGroup> m_renderGroups;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_RENDERER_H_

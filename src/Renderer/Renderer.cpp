
#include "canvas/Renderer/Renderer.h"

namespace ca {

void Renderer::beginFrame() {}

void Renderer::endFrame() {
  for (auto& renderGroup : m_renderGroups) {
    renderGroup.render(m_renderContext);
  }

  m_renderGroups.clear();
}

RenderGroup* Renderer::addRenderGroup(RenderGroupProjection projection) {
  m_renderGroups.emplaceBack(projection);
  RenderGroup* result = &m_renderGroups.last();

  return result;
}

}  // namespace ca

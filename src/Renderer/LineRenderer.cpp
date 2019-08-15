#include "canvas/Renderer/LineRenderer.h"

#include "canvas/Renderer/Renderer.h"

namespace ca {

LineRenderer::LineRenderer() = default;

bool LineRenderer::initialize(ca::Renderer* renderer) {
  m_renderer = renderer;
  m_lines.clear();

  ca::VertexDefinition def;
  def.addAttribute(ca::ComponentType::Float32, ComponentCount::Three, "position");
  m_vertexBufferId = m_renderer->createVertexBuffer(def, nullptr, 0);

  return true;
}

void LineRenderer::beginFrame() {
  m_lines.clear();
}

void LineRenderer::renderLine(const ca::Vec3& p1, const ca::Vec3& p2, const ca::Color& color) {
  m_lines.pushBack([&p1, &p2, &color](Line* storage) {
    storage->p1 = p1;
    storage->p2 = p2;
    storage->color = color;
  });
}

void LineRenderer::render() {
}

}  // namespace ca

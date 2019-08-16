#include "canvas/Renderer/LineRenderer.h"

#include "canvas/Renderer/Renderer.h"

namespace ca {

namespace {

const I8* kVertexShaderSource = R"(
#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

uniform mat4 uTransform;
out vec4 vColor;

void main() {
  vColor = inColor;
  gl_Position = uTransform * vec4(inPosition, 1.0);
}
)";

const I8* kFragmentShaderSource = R"(
#version 330

in vec4 vColor;

out vec4 final;

void main() {
  final = vec4(vColor);
}
)";

}  // namespace

LineRenderer::LineRenderer() = default;

bool LineRenderer::initialize(ca::Renderer* renderer) {
  m_renderer = renderer;
  m_lines.clear();

  ca::VertexDefinition def;
  def.addAttribute(ca::ComponentType::Float32, ComponentCount::Three, "position");
  def.addAttribute(ca::ComponentType::Float32, ComponentCount::Four, "color");
  m_vertexBufferId = m_renderer->createVertexBuffer(def, nullptr, 0);
  if (!isValid(m_vertexBufferId)) {
    LOG(Error) << "Could not create vertex buffer for line renderer.";
    return false;
  }

  m_indexBufferId = m_renderer->createIndexBuffer(ca::ComponentType::Unsigned16, nullptr, 0);
  if (!isValid(m_indexBufferId)) {
    LOG(Error) << "Could not create index buffer for line renderer.";
    return false;
  }

  m_transformUniformId = m_renderer->createUniform("uTransform");
  if (!isValid(m_transformUniformId)) {
    LOG(Error) << "Could not create uTransform uniform for line renderer.";
    return false;
  }

  auto vertexShaderSource = ca::ShaderSource::from(kVertexShaderSource);
  auto fragmentShaderSource = ca::ShaderSource::from(kFragmentShaderSource);
  m_programId = m_renderer->createProgram(vertexShaderSource, fragmentShaderSource);
  if (!isValid(m_programId)) {
    LOG(Error) << "Could not create program for line renderer.";
    return false;
  }

  return true;
}

void LineRenderer::beginFrame() {
  m_lines.clear();
  m_lineIndices.clear();
}

void LineRenderer::renderLine(const ca::Vec3& p1, const ca::Vec3& p2, const ca::Color& color) {
  m_lines.pushBack([&p1, &p2, &color](Line* storage) {
    storage->p1 = p1;
    storage->color1 = color;
    storage->p2 = p2;
    storage->color2 = color;
  });

  m_lineIndices.pushBack(static_cast<U16>(m_lineIndices.getSize()));
  m_lineIndices.pushBack(static_cast<U16>(m_lineIndices.getSize()));
}

void LineRenderer::render(const ca::Mat4& transform) {
  // Upload the new data.
  m_renderer->vertexBufferData(m_vertexBufferId, m_lines.getData(),
                               m_lines.getSize() * sizeof(Line));

  m_renderer->indexBufferData(m_indexBufferId, m_lineIndices.getData(),
                              m_lineIndices.getSize() * 2 * sizeof(U16));

  ca::UniformBuffer uniformBuffer;
  uniformBuffer.set(m_transformUniformId, transform);

  m_renderer->draw(ca::DrawType::Lines, m_lines.getSize() * 2, m_programId, m_vertexBufferId,
                   m_indexBufferId, {}, uniformBuffer);
}

}  // namespace ca

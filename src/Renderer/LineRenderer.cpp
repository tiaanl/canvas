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
#if 0
  m_lines.constructBack([&p1, &p2, &color](Line* storage) {
    storage->p1 = p1;
    storage->color1 = color;
    storage->p2 = p2;
    storage->color2 = color;
  });
#else
  m_lines.emplaceBack(p1, color, p2, color);
#endif

  m_lineIndices.pushBack(static_cast<U16>(m_lineIndices.size()));
  m_lineIndices.pushBack(static_cast<U16>(m_lineIndices.size()));
}

void LineRenderer::renderGrid(const ca::Plane& plane, const ca::Vec3& worldUp,
                              const ca::Color& color, I32 numBlocks, F32 blockSize) {
  ca::Vec3 center = plane.normal * plane.distance;
  ca::Vec3 right = ca::crossProduct(plane.normal, worldUp);
  ca::Vec3 forward = ca::crossProduct(plane.normal, right);

  //  renderLine(plane.normal * plane.distance, plane.normal * plane.distance + plane.normal *
  //  100.0f,
  //             ca::Color::red);
  //  renderLine(plane.normal * plane.distance, plane.normal * plane.distance + right * 100.0f,
  //             ca::Color::green);
  //  renderLine(plane.normal * plane.distance, plane.normal * plane.distance + forward * 100.0f,
  //             ca::Color::blue);

  F32 max = static_cast<F32>(numBlocks) * blockSize;

  for (I32 x = -numBlocks; x <= numBlocks; ++x) {
    ca::Vec3 p1 = center + right * static_cast<F32>(x) * blockSize + forward * +max;
    ca::Vec3 p2 = center + right * static_cast<F32>(x) * blockSize + forward * -max;
    renderLine(p1, p2, color);
  }

  for (I32 y = -numBlocks; y <= numBlocks; ++y) {
    ca::Vec3 p1 = center + forward * static_cast<F32>(y) * blockSize + right * +max;
    ca::Vec3 p2 = center + forward * static_cast<F32>(y) * blockSize + right * -max;
    renderLine(p1, p2, color);
  }
}

void LineRenderer::render(const ca::Mat4& transform) {
  // Upload the new scene.
  m_renderer->vertexBufferData(m_vertexBufferId, m_lines.data(), m_lines.size() * sizeof(Line));

  m_renderer->indexBufferData(m_indexBufferId, m_lineIndices.data(),
                              m_lineIndices.size() * 2 * sizeof(U16));

  ca::UniformBuffer uniformBuffer;
  uniformBuffer.set(m_transformUniformId, transform);

  m_renderer->draw(ca::DrawType::Lines, static_cast<U32>(m_lines.size() * 2), m_programId,
                   m_vertexBufferId, m_indexBufferId, {}, uniformBuffer);
}

}  // namespace ca

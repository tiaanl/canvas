#include "canvas/Renderer/ImmediateRenderer.h"

#include "canvas/Renderer/Renderer.h"
#include "canvas/Renderer/VertexDefinition.h"
#include "nucleus/Streams/WrappedMemoryInputStream.h"

namespace ca {

namespace {

auto g_vertexShaderSource = R"source(
#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

out vec4 vsColor;

uniform mat4 uTransform;

void main() {
  gl_Position = uTransform * vec4(inPosition, 1.0);
  vsColor = inColor;
}
)source";

auto g_fragmentShaderSource = R"source(
#version 330

in vec4 vsColor;

out vec4 final;

void main() {
  final = vsColor;
}
)source";

}  // namespace

ImmediateRenderer::ImmediateRenderer(Renderer* renderer) : m_renderer{renderer} {}

auto ImmediateRenderer::setTransform(const Mat4& transform) -> void {
  m_transform = transform;
}

auto ImmediateRenderer::vertex(const Vec3& position, const Color& color) -> void {
  m_vertices.emplaceBack(position, color);
}

auto ImmediateRenderer::submit(DrawType drawType) -> void {
  auto vertexDefinition =
      VertexDefinition{}
          .addAttribute(ComponentType::Float32, ComponentCount::Three, "position")
          .addAttribute(ComponentType::Float32, ComponentCount::Four, "color");

  auto vertexBufferId =
      m_renderer->createVertexBuffer(vertexDefinition, m_vertices.data(),
                                     m_vertices.size() * sizeof(typename VertexList::ElementType));

  auto programId = m_renderer->createProgram(ShaderSource::from(g_vertexShaderSource),
                                             ShaderSource::from(g_fragmentShaderSource));

  auto transformUniformId = m_renderer->createUniform("uTransform");

  UniformBuffer uniforms;
  uniforms.set(transformUniformId, m_transform);

  m_renderer->draw(drawType, 0, static_cast<U32>(m_vertices.size()), programId, vertexBufferId,
                   TextureId{}, uniforms);

  // m_renderer->deleteProgram(programId);
  m_renderer->deleteVertexBuffer(vertexBufferId);

  reset();
}

auto ImmediateRenderer::reset() -> void {
  m_vertices.clear();
}

}  // namespace ca

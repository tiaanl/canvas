#include "canvas/Renderer/ImmediateRenderer.h"

#include "canvas/Renderer/Renderer.h"
#include "canvas/Renderer/VertexDefinition.h"

namespace ca {

namespace {

auto g_vertex_shader_source = R"source(
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

auto g_fragment_shader_source = R"source(
#version 330

in vec4 vsColor;

out vec4 final;

void main() {
  final = vsColor;
}
)source";

ProgramId g_program_id{kInvalidResourceId};

}  // namespace

ImmediateRenderer::ImmediateRenderer(Renderer* renderer) : m_renderer{renderer} {}

ImmediateMesh& ImmediateRenderer::create_mesh(DrawType draw_type, const fl::Mat4& transform) {
  auto result = meshes_.emplaceBack(this, draw_type, transform);
  return result.element();
}

void ImmediateRenderer::submit_to_renderer() {
  if (!g_program_id.isValid()) {
    LOG(Info) << "Creating program";
    g_program_id = m_renderer->createProgram(ShaderSource::from(g_vertex_shader_source),
                                             ShaderSource::from(g_fragment_shader_source));
  }

  VertexDefinition def;
  def.addAttribute(ComponentType::Float32, ComponentCount::Three);
  def.addAttribute(ComponentType::Float32, ComponentCount::Four);

  for (const auto& mesh : meshes_) {
    auto vertex_buffer_id = m_renderer->createVertexBuffer(
        def, mesh.vertices_.data(), mesh.vertices_.size() * sizeof(ImmediateMesh::Vertex));

    auto transform_uniform_id = m_renderer->createUniform("uTransform");

    UniformBuffer uniforms;
    uniforms.set(transform_uniform_id, mesh.transform_);

    m_renderer->draw(mesh.draw_type_, 0, static_cast<U32>(mesh.vertices_.size()), g_program_id,
                     vertex_buffer_id, {}, uniforms);

    m_renderer->deleteVertexBuffer(vertex_buffer_id);
  }

  meshes_.clear();
}

}  // namespace ca

#include "canvas/Renderer/pipeline_builder.h"

#include "canvas/Renderer/renderer.h"

namespace ca {

PipelineBuilder::PipelineBuilder() = default;

PipelineBuilder& PipelineBuilder::attribute(nu::StringView name, ComponentType type,
                                            ComponentCount component_count) {
  LOG(Info) << "Adding attribute: " << name;
  vertex_definition_.addAttribute(type, component_count);

  return *this;
}

PipelineBuilder& PipelineBuilder::vertex_shader(ShaderSource source) {
  vertex_shader_ = std::move(source);

  return *this;
}

PipelineBuilder& PipelineBuilder::geometry_shader(ShaderSource source) {
  geometry_shader_ = std::move(source);

  return *this;
}

PipelineBuilder& PipelineBuilder::fragment_shader(ShaderSource source) {
  fragment_shader_ = std::move(source);

  return *this;
}

nu::Optional<Pipeline> PipelineBuilder::build(Renderer* renderer) const {
  DCHECK(vertex_shader_.has_value());
  DCHECK(fragment_shader_.has_value());

  auto program_id = renderer->createProgram(
      vertex_shader_.value(),
      geometry_shader_.has_value() ? geometry_shader_.value() : ShaderSource{},
      fragment_shader_.value());
  if (!program_id) {
    LOG(Error) << "Could not create pipeline program.";
    return {};
  }

  return Pipeline{renderer, vertex_definition_, program_id};
}

}  // namespace ca

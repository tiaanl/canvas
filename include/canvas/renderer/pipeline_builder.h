#pragma once

#include <nucleus/optional.h>

#include "canvas/Renderer/pipeline.h"
#include "canvas/Renderer/vertex_definition.h"
#include "canvas/Utils/shader_source.h"

namespace ca {

class Renderer;

class PipelineBuilder {
public:
  PipelineBuilder();

  PipelineBuilder& attribute(nu::StringView name, ComponentType type,
                             ComponentCount component_count);

  PipelineBuilder& vertex_shader(ShaderSource source);
  PipelineBuilder& geometry_shader(ShaderSource source);
  PipelineBuilder& fragment_shader(ShaderSource source);

  nu::Optional<Pipeline> build(Renderer* renderer) const;

private:
  VertexDefinition vertex_definition_;
  nu::Optional<ShaderSource> vertex_shader_;
  nu::Optional<ShaderSource> geometry_shader_;
  nu::Optional<ShaderSource> fragment_shader_;
};

}  // namespace ca

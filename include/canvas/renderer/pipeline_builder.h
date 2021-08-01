#pragma once

#include <nucleus/optional.h>

#include "canvas/renderer/pipeline.h"
#include "canvas/renderer/vertex_definition.h"
#include "canvas/utils/shader_source.h"

namespace ca {

class Renderer;

class PipelineBuilder {
public:
  explicit PipelineBuilder(Renderer* renderer);

  PipelineBuilder& attribute(nu::StringView name, ComponentType type,
                             ComponentCount component_count);

  PipelineBuilder& vertex_shader(ShaderSource source);
  PipelineBuilder& geometry_shader(ShaderSource source);
  PipelineBuilder& fragment_shader(ShaderSource source);

  NU_NO_DISCARD nu::Optional<Pipeline> build() const;

private:
  Renderer* renderer_;

  VertexDefinition vertex_definition_;
  nu::Optional<ShaderSource> vertex_shader_;
  nu::Optional<ShaderSource> geometry_shader_;
  nu::Optional<ShaderSource> fragment_shader_;
};

}  // namespace ca

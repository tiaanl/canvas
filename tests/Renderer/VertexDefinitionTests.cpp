
#include "canvas/Renderer/VertexDefinition.h"
#include "nucleus/Logging.h"
#include "nucleus/Testing.h"

namespace ca {

TEST_CASE("create empty vertex definition") {
  VertexDefinition vd;
  CHECK(vd.getAttributes().isEmpty());
}

TEST_CASE("add single vertex attribute") {
  VertexDefinition vd;
  vd.addAttribute(ComponentType::Float32, ComponentCount::Three, "position");
  vd.addAttribute(ComponentType::Unsigned32, ComponentCount::Two, "something");

  auto& attributes = vd.getAttributes();

  CHECK(attributes[0].getType() == ComponentType::Float32);
  CHECK(attributes[0].getComponentCount() == ComponentCount::Three);
  CHECK(attributes[0].getName() == "position");

  CHECK(attributes[1].getType() == ComponentType::Unsigned32);
  CHECK(attributes[1].getComponentCount() == ComponentCount::Two);
  CHECK(attributes[1].getName() == "something");
}

TEST_CASE("build correct shader source") {
  VertexDefinition vd;
  vd.addAttribute(ComponentType::Float32, ComponentCount::Three, "position");
  vd.addAttribute(ComponentType::Unsigned32, ComponentCount::Two, "something");

  nu::DynamicString text = vd.buildShaderSource();
  LOG(Info) << text.getData();
  CHECK(text.compare("layout(location = 0) in vec3 in_position;\nlayout(location = 1) in vec2 "
                     "in_something;\n") == 0);
}

}  // namespace ca

#include <catch2/catch.hpp>

#include "canvas/renderer/vertex_definition.h"

namespace ca {

TEST_CASE("add single vertex attribute") {
  VertexDefinition vd;
  vd.addAttribute(ComponentType::Float32, ComponentCount::Three);
  vd.addAttribute(ComponentType::Unsigned32, ComponentCount::Two);

  auto attribute = vd.begin();

  CHECK(attribute->getType() == ComponentType::Float32);
  CHECK(attribute->getCount() == ComponentCount::Three);

  ++attribute;

  CHECK(attribute->getType() == ComponentType::Unsigned32);
  CHECK(attribute->getCount() == ComponentCount::Two);
}

}  // namespace ca

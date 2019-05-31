
#include "canvas/Renderer/GeometryDefinition.h"

namespace ca {

void GeometryDefinition::addAttribute(U32 numberOfComponents, ComponentType componentType,
                                      U32 stride, U32 offset) {
  Attribute result;

  result.numberOfComponents = numberOfComponents;
  result.componentType = componentType;
  result.stride = stride;
  result.offset = offset;

  m_attributes.pushBack(result);
}

}  // namespace ca

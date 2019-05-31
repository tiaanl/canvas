
#include "canvas/Renderer/BufferDefinition.h"

namespace ca {

void BufferDefinition::addAttribute(U32 numberOfComponents, ComponentType componentType) {
  Attribute result;

  result.numberOfComponents = numberOfComponents;
  result.componentType = componentType;

  m_attributes.pushBack(result);
}

}  // namespace ca

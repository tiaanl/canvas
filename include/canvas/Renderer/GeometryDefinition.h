
#ifndef CANVAS_RENDERER_GEOMETRY_DEFINITION_H_
#define CANVAS_RENDERER_GEOMETRY_DEFINITION_H_

#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Types.h"

namespace ca {

enum class ComponentType : U32 {
  Float32 = 0,
  Signed8,
  Unsigned8,
  Signed16,
  Unsigned16,
  Signed32,
  Unsigned32,
};

struct Attribute {
  U32 numberOfComponents;  // 1..4
  ComponentType componentType;
  U32 stride;
  U32 offset;
};

class GeometryDefinition {
public:
  GeometryDefinition() = default;

  const nu::DynamicArray<Attribute>& getAttributes() const {
    return m_attributes;
  }

  void addAttribute(U32 numberOfComponents, ComponentType componentType, U32 stride, U32 offset);

private:
  nu::DynamicArray<Attribute> m_attributes;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_GEOMETRY_DEFINITION_H_

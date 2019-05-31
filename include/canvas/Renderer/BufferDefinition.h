
#ifndef CANVAS_RENDERER_BUFFER_DEFINITION_H_
#define CANVAS_RENDERER_BUFFER_DEFINITION_H_

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
};

class BufferDefinition {
public:
  explicit BufferDefinition(U32 componentsPerVertex) : m_componentsPerVertex{componentsPerVertex} {}

  U32 getComponentsPerVertex() const {
    return m_componentsPerVertex;
  }

  const nu::DynamicArray<Attribute>& getAttributes() const {
    return m_attributes;
  }

  void addAttribute(U32 numberOfComponents, ComponentType componentType);

private:
  // The total number of components per vertex.  If we are using a position + textureCoords
  // combination, then the number of components would be 5.  3 for the position, 2 for the
  // textureCoords.
  U32 m_componentsPerVertex;

  nu::DynamicArray<Attribute> m_attributes;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_BUFFER_DEFINITION_H_

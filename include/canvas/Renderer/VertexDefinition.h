
#ifndef CANVAS_RENDERER_VERTEX_DEFINITION_H_
#define CANVAS_RENDERER_VERTEX_DEFINITION_H_

#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Logging.h"
#include "nucleus/Text/StaticString.h"
#include "nucleus/Text/DynamicString.h"
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

class VertexAttribute {
public:
  VertexAttribute(ComponentType type, U32 componentCount, const nu::StringView& name)
    : m_type{ type }, m_componentCount{ componentCount }, m_name{ name } {}

  ComponentType getType() const {
    return m_type;
  }

  U32 getComponentCount() const {
    return m_componentCount;
  }

  const nu::StringView& getName() const {
    return m_name;
  }

private:
  ComponentType m_type;
  U32 m_componentCount;
  nu::StaticString<64> m_name;
};

class VertexDefinition {
public:
  using AttributeList = nu::DynamicArray<VertexAttribute>;

  VertexDefinition() = default;

  const AttributeList& getAttributes() const {
    return m_attributes;
  }

  void addAttribute(ComponentType type, U32 componentCount, const nu::StringView& name) {
    DCHECK(componentCount <= 4) << "maximum 4 components allowed per attribute type";

    m_attributes.emplaceBack(type, componentCount, name);
  }

  nu::DynamicString buildShaderSource();

private:
  friend class Renderer;

  AttributeList m_attributes;
  U32 m_stride = 0;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_VERTEX_DEFINITION_H_

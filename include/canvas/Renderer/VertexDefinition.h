
#ifndef CANVAS_RENDERER_VERTEX_DEFINITION_H_
#define CANVAS_RENDERER_VERTEX_DEFINITION_H_

#include "canvas/Renderer/Types.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Logging.h"
#include "nucleus/Text/DynamicString.h"
#include "nucleus/Text/StaticString.h"
#include "nucleus/Types.h"

namespace ca {

class VertexAttribute {
public:
  VertexAttribute(ComponentType type, ComponentCount count);

  auto getType() const -> ComponentType {
    return m_type;
  }

  auto getCount() const -> ComponentCount {
    return m_count;
  }

  auto getSizeInBytes() const -> U32 {
    return m_sizeInBytes;
  }

private:
  ComponentType m_type;
  ComponentCount m_count;
  U32 m_sizeInBytes;
};

class VertexDefinition {
public:
  using AttributeList = nu::DynamicArray<VertexAttribute>;

  VertexDefinition() = default;

  auto getStride() const -> U32 {
    return m_stride;
  }

  auto begin() -> AttributeList::Iterator {
    return m_attributes.begin();
  }

  auto begin() const -> AttributeList::ConstIterator {
    return m_attributes.begin();
  }

  auto end() -> AttributeList::Iterator {
    return m_attributes.end();
  }

  auto end() const -> AttributeList::ConstIterator {
    return m_attributes.end();
  }

  auto addAttribute(ComponentType type, ComponentCount componentCount) -> void {
    auto result = m_attributes.emplaceBack(type, componentCount);
    m_stride += result.element().getSizeInBytes();
  }

private:
  AttributeList m_attributes;
  U32 m_stride = 0;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_VERTEX_DEFINITION_H_

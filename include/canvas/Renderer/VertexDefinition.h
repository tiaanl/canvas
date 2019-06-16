
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
  VertexAttribute(ComponentType type, ComponentCount count, const nu::StringView& name)
    : m_type{type}, m_count{count}, m_name{name} {
    m_sizeInBytes = getComponentTypeSizeInBytes(type) * U32(count);
  }

  ComponentType getType() const {
    return m_type;
  }

  ComponentCount getCount() const {
    return m_count;
  }

  U32 getSizeInBytes() const {
    return m_sizeInBytes;
  }

  const nu::StringView& getName() const {
    return m_name;
  }

private:
  static U32 getComponentTypeSizeInBytes(ComponentType type) {
    switch (type) {
      case ComponentType::Float32:
        return sizeof(F32);

      case ComponentType::Signed8:
        return sizeof(I8);

      case ComponentType::Unsigned8:
        return sizeof(U8);

      case ComponentType::Signed16:
        return sizeof(I16);

      case ComponentType::Unsigned16:
        return sizeof(U16);

      case ComponentType::Signed32:
        return sizeof(I32);

      case ComponentType::Unsigned32:
        return sizeof(U32);

      default:
        DCHECK(false) << "Invalid component type.";
        return 0;
    }
  }

  ComponentType m_type;
  ComponentCount m_count;
  U32 m_sizeInBytes;
  nu::StaticString<64> m_name;
};

class VertexDefinition {
public:
  using AttributeList = nu::DynamicArray<VertexAttribute>;

  VertexDefinition() = default;

  const AttributeList& getAttributes() const {
    return m_attributes;
  }

  U32 getStride() const {
    return m_stride;
  }

  VertexDefinition& addAttribute(ComponentType type, ComponentCount componentCount,
                                 const nu::StringView& name) {
    m_attributes.emplaceBack(type, componentCount, name);
    m_stride += m_attributes.last().getSizeInBytes();

    return *this;
  }

  nu::DynamicString buildShaderSource();

private:
  AttributeList m_attributes;
  U32 m_stride = 0;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_VERTEX_DEFINITION_H_

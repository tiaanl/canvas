
#include "canvas/renderer/vertex_definition.h"

namespace ca {

namespace {

auto getComponentTypeSizeInBytes(ComponentType type) -> U32 {
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

}  // namespace

VertexAttribute::VertexAttribute(ComponentType type, ComponentCount count)
  : m_type{type}, m_count{count} {
  m_sizeInBytes = getComponentTypeSizeInBytes(type) * U32(count);
}

}  // namespace ca


#include "canvas/Renderer/VertexDefinition.h"

#include "nucleus/Streams/StringOutputStream.h"

namespace ca {

nu::DynamicString VertexDefinition::buildShaderSource() {
  nu::StringOutputStream out;

  // layout(location = 0) in vec3 inPosition;
  // layout(location = 1) in vec2 inTextureCoord;

#if 0
  for (U32 i = 0; i < m_attributes.getSize(); ++i) {
    auto& attr = m_attributes[i];
    out << "layout(location = " << i << ") in vec" << attr.getComponentCount() << " in_"
      << attr.getName().getData() << ";\n";
  }
#endif  // 0

  return out.getString();
}

}  // namespace ca

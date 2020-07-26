
#ifndef CANVAS_UTILS_SHADER_SOURCE_H_
#define CANVAS_UTILS_SHADER_SOURCE_H_

#include "nucleus/Streams/InputStream.h"
#include "nucleus/Text/DynamicString.h"

namespace ca {

class ShaderSource {
public:
  static ShaderSource from(nu::StringView source);
  static ShaderSource from(nu::InputStream* stream);

  ShaderSource() = default;

  // Replace the current contents of the shader source with the contents of the given stream.
  bool loadFromStream(nu::InputStream* stream);

  nu::StringView getSource() const {
    return m_source.view();
  }

private:
  explicit ShaderSource(nu::DynamicString source);

  nu::DynamicString m_source;
};

}  // namespace ca

#endif  // CANVAS_UTILS_SHADER_SOURCE_H_

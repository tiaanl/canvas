#pragma once

#include "nucleus/streams/input_stream.h"
#include "nucleus/text/dynamic_string.h"

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

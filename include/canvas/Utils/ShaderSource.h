
#ifndef CANVAS_UTILS_SHADER_SOURCE_H_
#define CANVAS_UTILS_SHADER_SOURCE_H_

#include "nucleus/Streams/InputStream.h"
#include "nucleus/Text/String.h"
#include "nucleus/Text/StringView.h"

namespace ca {

class ShaderSource {
public:
  static ShaderSource from(const nu::StringView& source);
  static ShaderSource from(nu::InputStream* stream);

  nu::StringView getSource() const {
    return nu::StringView{m_source.getRawBytes(), m_source.getLength()};
  }

private:
  ShaderSource(nu::String&& source);

  nu::String m_source;
};

}  // namespace ca

#endif  // CANVAS_UTILS_SHADER_SOURCE_H_

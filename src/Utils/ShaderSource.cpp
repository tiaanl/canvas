
#include "canvas/Utils/ShaderSource.h"

namespace ca {

// static
ShaderSource ShaderSource::from(const nu::StringView& source) {
  nu::String data{source.getData(), source.getLength()};
  return {std::move(data)};
}

ShaderSource ShaderSource::from(nu::InputStream* stream) {
  nu::String temp;
  temp.resize(1024);

  nu::String data;

  for (;;) {
    auto bytesRead = stream->read(temp.getRawBytes(), temp.getLength());

    data.append(temp, bytesRead);

    if (bytesRead < temp.getLength()) {
      break;
    }
  }

  return {std::move(data)};
}

ShaderSource::ShaderSource(nu::String&& source) : m_source{std::move(source)} {}

}  // namespace ca

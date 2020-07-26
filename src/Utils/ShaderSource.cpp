
#include "canvas/Utils/ShaderSource.h"

namespace ca {

// static
ShaderSource ShaderSource::from(nu::StringView source) {
  return ShaderSource{source};
}

// static
ShaderSource ShaderSource::from(nu::InputStream* stream) {
  nu::DynamicString temp;
  temp.resize(1024);

  nu::DynamicString data;

  for (;;) {
    auto bytesRead = stream->read(temp.data(), temp.length());

    data.append(temp.view().subString(0, bytesRead));

    if (bytesRead < temp.length()) {
      break;
    }
  }

  return ShaderSource{std::move(data)};
}

bool ShaderSource::loadFromStream(nu::InputStream* stream) {
  auto bytesRemaining = stream->getBytesRemaining();
  m_source.resize(bytesRemaining);
  stream->read(m_source.data(), bytesRemaining);

  return true;
}

ShaderSource::ShaderSource(nu::DynamicString source) : m_source{std::move(source)} {}

}  // namespace ca

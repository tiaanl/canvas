
#include "canvas/Utils/ShaderSource.h"

namespace ca {

// static
ShaderSource ShaderSource::from(const nu::StringView& source) {
  nu::String data{source.data(), source.length()};
  return ShaderSource{std::move(data)};
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

  return ShaderSource{std::move(data)};
}

bool ShaderSource::loadFromStream(nu::InputStream* stream) {
  auto bytesRemaining = stream->getBytesRemaining();
  m_source.resize(bytesRemaining);
  stream->read(m_source.getRawBytes(), bytesRemaining);

  return true;
}

ShaderSource::ShaderSource(nu::String&& source) : m_source{source} {}

}  // namespace ca

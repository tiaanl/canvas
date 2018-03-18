
#include "canvas/Rendering/Shader.h"

#include "canvas/Utils/GLCheck.h"
#include "nucleus/Logging.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

Shader::Shader(Shader&& other) noexcept : m_type(other.m_type), m_name(other.m_name) {
  other.m_name = 0;
}

Shader::~Shader() {
  if (m_name) {
    GL_CHECK(glDeleteShader(m_name));
  }
}

Shader& Shader::operator=(Shader&& other) noexcept {
  m_type = other.m_type;
  m_name = other.m_name;

  other.m_name = 0;

  return *this;
}

bool Shader::loadFromStream(ShaderType shaderType, nu::InputStream* stream) {
  m_type = shaderType;

  nu::DynamicArray<I8> data;

  const auto streamLength = stream->getLength();
  if (!streamLength) {
    // We don't need to do anything if the file is empty.
    return true;
  }

  // Read the entire stream into the data buffer.
  data.resize(streamLength + 1);
  auto bytesRead = stream->read(data.getData(), streamLength);

  // Make sure we terminate the string buffer.
  data[bytesRead] = '\0';

  // Set the source data and return the success status.
  return setSource(data);
}

bool Shader::createInternal() {
  // If we've already been created, do nothing.
  if (m_name && glIsShader(m_name)) {
    return true;
  }

  m_name = glCreateShader(m_type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

  return glCheck();
}

bool Shader::setSource(const nu::DynamicArray<I8>& source) {
  // Make sure the shader is created.
  createInternal();

  // Set the source of the shader.
  const GLchar* src = source.getData();
  const GLint length = static_cast<const GLint>(source.getSize());
  GL_CHECK(glShaderSource(m_name, 1, &src, &length));
  GL_CHECK(glCompileShader(m_name));

  GLint success;
  GL_CHECK(glGetShaderiv(m_name, GL_COMPILE_STATUS, &success));
  if (success == GL_FALSE) {
    // Get the size of the log messages.
    GLint logSize = 0;
    GL_CHECK(glGetShaderiv(m_name, GL_INFO_LOG_LENGTH, &logSize));

    nu::DynamicArray<GLchar> log;
    log.resize(static_cast<USize>(logSize));
    GL_CHECK(glGetShaderInfoLog(m_name, logSize, &logSize, log.getData()));

    LOG(Error) << log.getData();

    return false;
  }

  return true;
}

}  // namespace ca

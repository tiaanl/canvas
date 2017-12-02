
#include "canvas/rendering/shader.h"

#include "nucleus/logging.h"
#include "nucleus/utils/stl.h"

#include "canvas/utils/gl_check.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

Shader::Shader(ShaderType type) : m_type(type) {}

Shader::~Shader() {
  if (m_name) {
    GL_CHECK(glDeleteShader(m_name));
  }
}

bool Shader::loadFromStream(nu::InputStream* stream) {
  std::vector<char> data;

  const auto streamLength = stream->getLength();
  if (!streamLength) {
    // We don't need to do anything if the file is empty.
    return true;
  }

  // Read the entire stream into the data buffer.
  auto bytesRead = stream->read(nu::vectorAsArray(&data, streamLength + 1), streamLength);

  // Make sure we terminate the string buffer.
  data[bytesRead] = '\0';

  // Set the source data and return the success status.
  return setSource(data);
}

bool Shader::createInternal() {
  // If we've already been created, do nothing.
  if (m_name) {
    return true;
  }

  m_name = glCreateShader(m_type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

  return true;
}

bool Shader::setSource(const std::vector<char>& data) {
  // Make sure the shader is created.
  createInternal();

  // Set the source of the shader.
  const GLchar* src = nu::vectorAsArray(&data);
  GL_CHECK(glShaderSource(m_name, 1, &src, 0));
  GL_CHECK(glCompileShader(m_name));

  GLint success;
  GL_CHECK(glGetShaderiv(m_name, GL_COMPILE_STATUS, &success));
  if (success == GL_FALSE) {
    // Get the size of the log messages.
    GLint logSize = 0;
    GL_CHECK(glGetShaderiv(m_name, GL_INFO_LOG_LENGTH, &logSize));

    std::vector<GLchar> log(logSize);
    GL_CHECK(glGetShaderInfoLog(m_name, logSize, &logSize, &log[0]));

    LOG(Error) << log.data();

    return false;
  }

  return true;
}

}  // namespace ca

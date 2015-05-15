// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "canvas/rendering/shader.h"

#include "nucleus/logging.h"

#include "canvas/utils/gl_check.h"

namespace ca {

Shader::Shader(ShaderType type) : m_type(type) {
}

bool Shader::loadFromFile(const nu::FilePath& filename) {
  std::vector<char> data;

#if 0
  if (!getFileContents(filename, &data)) {
    LOG(Error) << "Could not read shader file. (" << filename << ")";
    return false;
  }
#endif  // 0

  return setSource(data);
}

bool Shader::createInternal() {
  // If we've already been created, do nothing.
  if (m_name) {
    return true;
  }

  m_name =
      glCreateShader(m_type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

  return true;
}

bool Shader::setSource(const std::vector<char>& data) {
  // Make sure the shader is created.
  createInternal();

  // Set the source of the shader.
  const GLchar* src = &data[0];
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

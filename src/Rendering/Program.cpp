
#include "canvas/Rendering/Program.h"

#include "canvas/Rendering/Shader.h"
#include "canvas/Utils/GLCheck.h"
#include "nucleus/Containers/DynamicArray.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

// static
void Program::bind(Program* program) {
  if (program) {
    // Make sure the program is linked.
    if (!program->m_isLinked) {
      program->linkInternal();
    }

    GL_CHECK(glUseProgram(program->m_name));
  } else {
    GL_CHECK(glUseProgram(0));
  }
}

Program::Program() {}

Program::Program(const ResourceRef<Shader>& vertexShader, const ResourceRef<Shader>& fragmentShader)
  : m_vertexShader(vertexShader), m_fragmentShader(fragmentShader) {}

Program::~Program() {
  if (m_name) {
    GL_CHECK(glDeleteProgram(m_name));
  }
}

void Program::setVertexShader(const ResourceRef<Shader>& vertexShader) {
  m_vertexShader = vertexShader;
  m_isLinked = false;
}

void Program::setFragmentShader(const ResourceRef<Shader>& fragmentShader) {
  m_fragmentShader = fragmentShader;
  m_isLinked = false;
}

void Program::link() {
  linkInternal();
}

#define BIND_AND_GET_LOCATION()                                                                                        \
  bind(this);                                                                                                          \
  GLint location = glGetUniformLocation(m_name, name.c_str());                                                         \
  if (location == -1 || glGetError() != GL_NO_ERROR) {                                                                 \
    LOG(Warning) << "Could not find uniform location. (" << name << ")";                                               \
    return false;                                                                                                      \
  }

bool Program::setUniform(std::string name, float f) {
  BIND_AND_GET_LOCATION()
  glUniform1f(location, f);
  return glGetError() == GL_NO_ERROR;
}

bool Program::setUniform(std::string name, const Vec2& vec2) {
  BIND_AND_GET_LOCATION()
  glUniform2f(location, vec2.x, vec2.y);
  return glGetError() == GL_NO_ERROR;
}

bool Program::setUniform(std::string name, const Vec3& vec3) {
  BIND_AND_GET_LOCATION()
  glUniform3f(location, vec3.x, vec3.y, vec3.z);
  return glGetError() == GL_NO_ERROR;
}

bool Program::setUniform(std::string name, const Vec4& vec4) {
  BIND_AND_GET_LOCATION()
  glUniform4f(location, vec4.x, vec4.y, vec4.z, vec4.w);
  return glGetError() == GL_NO_ERROR;
}

bool Program::setUniform(std::string name, const Mat4& mat4) {
  BIND_AND_GET_LOCATION()
  glUniformMatrix4fv(location, 1, GL_FALSE, &mat4[0].x);
  return glGetError() == GL_NO_ERROR;
}

#undef BIND_AND_GET_LOCATION

void Program::linkInternal() {
  // Make sure the program is created.
  if (!m_name) {
    m_name = glCreateProgram();
  }

  // Attach the shaders.
  GL_CHECK(glAttachShader(m_name, m_vertexShader.get()->get().getNativeHandle()));
  GL_CHECK(glAttachShader(m_name, m_fragmentShader.get()->get().getNativeHandle()));

  // Link the program.
  GL_CHECK(glLinkProgram(m_name));

  // Check if there were any information.
  GLint infoLength = 0;
  GL_CHECK(glGetProgramiv(m_name, GL_INFO_LOG_LENGTH, &infoLength));

  if (infoLength > 0) {
    nu::DynamicArray<I8> buffer;
    buffer.resize(infoLength);
    GL_CHECK(glGetProgramInfoLog(m_name, infoLength, &infoLength, (GLchar*)buffer.getData()));
    if (infoLength) {
      LOG(Error) << buffer.getData();
    }
  }

  m_isLinked = true;
}

}  // namespace ca

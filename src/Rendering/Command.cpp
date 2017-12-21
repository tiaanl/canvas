
#include "canvas/Rendering/Command.h"
#include "canvas/Utils/GLCheck.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

Command::Command() {}

Command::Command(GLuint program, GLuint vertexArray, GLenum primitiveType, GLint first, GLint count)
  : m_program(program), m_vertexArray(vertexArray), m_primitiveType(primitiveType), m_first(first), m_count(count) {}

void Command::addUniform(const std::string& name, const Vec4& value) {
  m_uniformData.emplaceBack(UniformData::Uniform4f, name, (void*)(&value.x));
}

void Command::addUniform(const std::string& name, const Mat4& mat) {
  m_uniformData.emplaceBack(UniformData::UniformMatrix4x4, name, (void*)mat.asArray());
}

void Command::execute() {
  /*
  // Use the program.
  if (m_program) {
    GL_CHECK(glUseProgram(m_program));
  }

  // Set all the uniforms.
  for (const UniformData& data : m_uniformData) {
    GLint location = glGetUniformLocation(m_program, data.name.c_str());
    if (location == -1 || glGetError() != GL_NO_ERROR) {
      LOG(Warning) << "Could not find uniform location. (" << data.name << ")";
      continue;
    }

    switch (data.type) {
      case UniformData::Uniform4f:
        GL_CHECK(glUniform4fv(location, 1, (GLfloat*)data.data));
        break;

      case UniformData::UniformMatrix4x4:
        GL_CHECK(glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)data.data));
        break;

      default:
        NOTREACHED() << "Unknown uniform data type.";
        break;
    }
  }
  */

  // Bind the vertex array.
  GL_CHECK(glBindVertexArray(m_vertexArray));

  // Draw the geometry.
  GL_CHECK(glDrawArrays(m_primitiveType, m_first, m_count));
}

}  // namespace ca
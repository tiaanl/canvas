
#ifndef CANVAS_RENDERING_COMMAND_H_
#define CANVAS_RENDERING_COMMAND_H_

#include <vector>

#include "canvas/math/mat4.h"
#include "canvas/opengl.h"
#include "nucleus/types.h"

namespace ca {

class Command {
public:
  Command();
  Command(GLuint program, GLuint vertexArray, GLenum primitiveType, GLint first, GLint count);

  void addUniform(const std::string& name, const Vec4& value);
  void addUniform(const std::string& name, const Mat4& mat);

  void execute();

private:
  GLuint m_program{0};
  GLuint m_vertexArray{0};
  GLenum m_primitiveType{0};
  GLint m_first{0};
  GLint m_count{0};

  struct UniformData {
    enum {
      Uniform4f,
      UniformMatrix4x4,
    } type;
    std::string name;
    void* data;
  };

  std::vector<UniformData> m_uniformData;
};

}  // namespace ca

#endif  // CANVAS_RENDERING_COMMAND_H_

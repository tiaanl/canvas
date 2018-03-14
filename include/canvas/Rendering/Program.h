
#ifndef CANVAS_RENDERING_PROGRAM_H_
#define CANVAS_RENDERING_PROGRAM_H_

#include <string>

#include "nucleus/Macros.h"

#include "canvas/Math/Mat4.h"
#include "canvas/Math/Vec2.h"
#include "canvas/Math/Vec3.h"
#include "canvas/Math/Vec4.h"
#include "canvas/OpenGL.h"
#include "canvas/Resources/Resource.h"

namespace ca {

class Shader;

class Program {
public:
  COPY_DELETE(Program);

  // Bind the specified program.  Can pass nullptr to clear the program binding.
  static void bind(Program* program);

  Program();
  Program(Program&& other) noexcept;
  Program(const ResourceRef<Shader>& vertexShader, const ResourceRef<Shader>& fragmentShader);
  ~Program();

  Program& operator=(Program&& other) noexcept;

  // Return the OpenGL resource name for the shader program.
  GLuint getNativeHandle() const {
    return m_name;
  }

  // Get/set the vertex shader.
  const ResourceRef<Shader>& getVertexShader() const {
    return m_vertexShader;
  }

  void setVertexShader(const ResourceRef<Shader>& vertexShader);

  // Get/set the fragment shader.
  const ResourceRef<Shader>& getFragmentShader() const {
    return m_fragmentShader;
  }

  void setFragmentShader(const ResourceRef<Shader>& fragmentShader);

  // Returns true if the program is linked.
  bool isLinked() const {
    return m_isLinked;
  }

  // Link the program.
  bool link();

  // Set uniforms inside the program.
  bool setUniform(std::string name, float f);
  bool setUniform(std::string name, const Vec2& vec2);
  bool setUniform(std::string name, const Vec3& vec3);
  bool setUniform(std::string name, const Vec4& vec4);
  bool setUniform(std::string name, const Mat4& mat4);

private:
  // Link the program.
  bool linkInternal();

  // The native handle to the program.
  GLuint m_name = 0;

  // The shaders we'll use.
  ResourceRef<Shader> m_vertexShader;
  ResourceRef<Shader> m_fragmentShader;

  // Flag to keep track of whether the program is linked.
  bool m_isLinked = false;
};

}  // namespace ca

#endif  // CANVAS_RENDERING_PROGRAM_H_


#ifndef CANVAS_RENDERING_SHADER_H_
#define CANVAS_RENDERING_SHADER_H_

#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"
#include "nucleus/Streams/InputStream.h"

#include "canvas/OpenGL.h"

namespace ca {

class Shader {
public:
  COPY_DELETE(Shader);

  enum ShaderType {
    Unknown,
    Vertex,
    Fragment,
  };

  Shader() = default;
  Shader(Shader&& other) noexcept;
  ~Shader();

  Shader& operator=(Shader&& other) noexcept;

  // Get the native handle of the shader.
  GLuint getNativeHandle() const {
    return m_name;
  }

  // Load the shader source from an input stream.
  bool loadFromStream(ShaderType shaderType, nu::InputStream* stream);

private:
  // Create the shader.
  bool createInternal();

  // Set the source of the shader.
  bool setSource(const nu::DynamicArray<I8>& source);

  // The type of this shader.
  ShaderType m_type = Unknown;

  // The name of the shader.
  GLuint m_name = 0;
};

}  // namespace ca

#endif  // CANVAS_RENDERING_SHADER_H_

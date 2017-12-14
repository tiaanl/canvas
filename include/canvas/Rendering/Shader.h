
#ifndef CANVAS_RENDERING_SHADER_H_
#define CANVAS_RENDERING_SHADER_H_

#include "nucleus/Macros.h"
#include "nucleus/Streams/InputStream.h"

#include "canvas/OpenGL.h"

namespace ca {

class Shader {
public:
  enum ShaderType {
    Vertex,
    Fragment,
  };

  explicit Shader(ShaderType type);
  ~Shader();

  // Get the native handle of the shader.
  GLuint getNativeHandle() const { return m_name; }

  // Load the shader source from an input stream.
  bool loadFromStream(nu::InputStream* stream);

private:
  // Create the shader.
  bool createInternal();

  // Set the source of the shader.
  bool setSource(const I8* data);

  // The type of this shader.
  ShaderType m_type;

  // The name of the shader.
  GLuint m_name{0};

  DISALLOW_IMPLICIT_CONSTRUCTORS(Shader);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_SHADER_H_

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

#ifndef CANVAS_RENDERING_SHADER_H_
#define CANVAS_RENDERING_SHADER_H_

#include <vector>

#include "nucleus/streams/input_stream.h"
#include "nucleus/macros.h"

#include "canvas/opengl.h"

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
  bool setSource(const std::vector<char>& data);

  // The type of this shader.
  ShaderType m_type;

  // The name of the shader.
  GLuint m_name{0};

  DISALLOW_IMPLICIT_CONSTRUCTORS(Shader);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_SHADER_H_

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

#include "canvas/app.h"
#include "canvas/math/vec4.h"
#include "canvas/rendering/canvas.h"
#include "canvas/rendering/shader.h"
#include "canvas/rendering/program.h"
#include "canvas/rendering/texture.h"
#include "canvas/rendering/vertex_buffer_object.h"
#include "canvas/utils/image.h"
#include "nucleus/logging.h"
#include "nucleus/streams/file_input_stream.h"

class Rendering : public ca::WindowDelegate {
public:
  Rendering() {
    m_title = "Rendering";
  }

  ~Rendering() override {}

  // Override: ca::WindowDelegate

  void onWindowCreated() override {
    LOG(Info) << "onWindowCreated";

    nu::FilePath root{FILE_PATH_LITERAL("C:\\Workspace\\canvas\\examples\\rendering")};

    nu::FileInputStream vertStream{
        root.append(FILE_PATH_LITERAL("res"))
            .append(FILE_PATH_LITERAL("shaders"))
            .append(FILE_PATH_LITERAL("default.vert.glsl"))};
    m_vertShader.loadFromStream(&vertStream);
    m_program.setVertexShader(&m_vertShader);

    nu::FileInputStream fragStream{
        root.append(FILE_PATH_LITERAL("res"))
            .append(FILE_PATH_LITERAL("shaders"))
            .append(FILE_PATH_LITERAL("default.frag.glsl"))};

    m_fragShader.loadFromStream(&fragStream);
    m_program.setFragmentShader(&m_fragShader);

    // Make sure the program is linked.
    m_program.link();

    // And use the program.
    ca::Program::bind(&m_program);

    // clang-format off
    static float vertices[] = {
      -0.5f, -0.5f, 0.0f, 0.0f,
       0.5f, -0.5f, 1.0f, 0.0f,
       0.5f,  0.5f, 1.0f, 1.0f,
      -0.5f,  0.5f, 0.0f, 1.0f,
    };
    // clang-format on

    m_vbo.setData(vertices, sizeof(vertices));

    {
      // Load a texture in.
      nu::FileInputStream imageStream{
          root.append(FILE_PATH_LITERAL("res"))
              .append(FILE_PATH_LITERAL("images"))
              .append(FILE_PATH_LITERAL("canvas.jpg"))};

      ca::Image image;
      if (!image.loadFromStream(&imageStream)) {
        return;
      }

      if (!m_texture.createFromImage(image)) {
        return;
      }
    }
  }

  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color{31, 62, 93, 255});

    ca::Program::bind(&m_program);
    DCHECK(m_program.setUniform("uni_color", ca::Vec4f(1.0f, 1.0f, 0.0f, 1.0f)));

    m_texture.bind();
    ca::VertexBufferObject::ScopedBind binder(m_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4,
                          (void*)(sizeof(GLfloat) * 2));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN, 0, 4));

    glDisable(GL_BLEND);
  }

private:
  ca::Shader m_vertShader{ca::Shader::Vertex};
  ca::Shader m_fragShader{ca::Shader::Fragment};
  ca::Program m_program;
  ca::VertexBufferObject m_vbo;
  ca::Texture m_texture;

  DISALLOW_COPY_AND_ASSIGN(Rendering);
};

CANVAS_APP(Rendering)

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
#include "canvas/math/mat4.h"
#include "canvas/math/transform.h"
#include "canvas/math/vec4.h"
#include "canvas/rendering/canvas.h"
#include "canvas/rendering/font.h"
#include "canvas/rendering/program.h"
#include "canvas/rendering/shader.h"
#include "canvas/rendering/texture.h"
#include "canvas/rendering/vertex_buffer_object.h"
#include "canvas/utils/image.h"
#include "nucleus/logging.h"
#include "nucleus/streams/file_input_stream.h"

class Rendering : public ca::WindowDelegate {
public:
  Rendering() { m_title = "Rendering"; }

  ~Rendering() override {}

  // Override: ca::WindowDelegate

  void onWindowCreated() override {
    LOG(Info) << "onWindowCreated";

    nu::FileInputStream fontStream{
        nu::FilePath{FILE_PATH_LITERAL("C:\\Windows\\Fonts\\arial.ttf")}};

    m_font.loadFromStream(&fontStream);
    m_font.getOrInsertGlyph(50, 'a');
    m_font.getOrInsertGlyph(50, 'b');
    m_font.getOrInsertGlyph(50, 'c');
    m_font.getOrInsertGlyph(50, 'd');
    m_font.getOrInsertGlyph(50, 'H');
    m_font.getOrInsertGlyph(50, 'e');
    m_font.getOrInsertGlyph(50, 'l');
    m_font.getOrInsertGlyph(50, 'o');

    nu::FilePath root{
        FILE_PATH_LITERAL("C:\\Workspace\\canvas\\examples\\rendering")};

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
    const f32 kSize = 10.f;
    static float vertices[] = {
      -kSize, -kSize, 0.0f, 0.0f,
       kSize, -kSize, 1.0f, 0.0f,
       kSize,  kSize, 1.0f, 1.0f,
      -kSize,  kSize, 0.0f, 1.0f,
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

  void onWindowResized(const ca::Size<uint32_t>& size) override {
    m_projectionMatrix = ca::ortho(-static_cast<float>(size.width) / 4.f,
                                   static_cast<float>(size.width) / 4.f,
                                   static_cast<float>(size.height) / 4.f,
                                   -static_cast<float>(size.height) / 4.f);
  }

  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color{31, 62, 93, 255});

    static float counter = 0.f;
    static float direction = 0.0001f;
#if 0
    counter += direction;
    if (counter < 0.f || counter > 1.f) {
      direction *= -1.f;
    }
#endif  // 0

    ca::Program::bind(&m_program);

    // DCHECK(m_program.setUniform("uni_color", ca::Vec4(1.0f, 1.0f, 0.0f, 1.0f)));

    ca::Mat4 viewMatrix;
    viewMatrix = ca::scale(viewMatrix, ca::Vec3{10.f, 10.f, 1.f});
    viewMatrix = ca::rotate(viewMatrix, counter* 20.f, ca::Vec3{0.f, 0.f, 1.f});
    viewMatrix = ca::translate(viewMatrix, ca::Vec3{counter * 100.f, 0.f, 0.f});
    ca::Mat4 mvp = m_projectionMatrix * viewMatrix;
    DCHECK(m_program.setUniform("uni_mvp", mvp));

    // ca::Texture::bind(&m_texture);
    ca::Texture::bind(m_font.getTexture(50));
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

  ca::Mat4 m_projectionMatrix;

  ca::Font m_font;

  DISALLOW_COPY_AND_ASSIGN(Rendering);
};

CANVAS_APP(Rendering)

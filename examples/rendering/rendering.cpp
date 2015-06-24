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
#include "canvas/rendering/canvas.h"
#include "canvas/rendering/geometry.h"
#include "canvas/rendering/program.h"
#include "canvas/rendering/shader.h"
#include "canvas/rendering/sprite.h"
#include "canvas/rendering/texture.h"
#include "canvas/utils/image.h"
#include "nucleus/streams/file_input_stream.h"

class Rendering : public ca::WindowDelegate {
public:
  Rendering() { m_title = "Rendering"; }

  ~Rendering() override {}

  // Override: ca::WindowDelegate

  bool onWindowCreated() override {
    nu::FilePath root{
        FILE_PATH_LITERAL("C:\\Workspace\\canvas\\examples\\rendering")};

    // Load vertex shader.
    nu::FileInputStream vertStream{
        root.append(FILE_PATH_LITERAL("res"))
            .append(FILE_PATH_LITERAL("shaders"))
            .append(FILE_PATH_LITERAL("default.vert.glsl"))};
    ca::Shader vertShader{ca::Shader::Vertex};
    vertShader.loadFromStream(&vertStream);
    m_program.setVertexShader(&vertShader);

    // Load fragment shader.
    nu::FileInputStream fragStream{
        root.append(FILE_PATH_LITERAL("res"))
            .append(FILE_PATH_LITERAL("shaders"))
            .append(FILE_PATH_LITERAL("default.frag.glsl"))};
    ca::Shader fragShader{ca::Shader::Fragment};
    fragShader.loadFromStream(&fragStream);
    m_program.setFragmentShader(&fragShader);

    // Make sure the program is linked.
    m_program.link();

    // And use the program.
    ca::Program::bind(&m_program);

    // Load a texture in.
    nu::FileInputStream imageStream{
        root.append(FILE_PATH_LITERAL("res"))
            .append(FILE_PATH_LITERAL("images"))
            .append(FILE_PATH_LITERAL("canvas.jpg"))};

    ca::Image image;
    if (!image.loadFromStream(&imageStream)) {
      return false;
    }

    if (!m_texture.createFromImage(image)) {
      return false;
    }

    // Create some geometry that we can render.
    m_geometry = ca::Geometry::createRectangle(
        ca::Rect<f32>{-0.5f, -0.5f, 1.f, 1.f}, ca::Color{255, 0, 0, 127});
    m_geometry.compileAndUpload();

    // Set up the sprite.
    m_sprite.setTexture(&m_texture);

    return true;
  }

  void onWindowResized(const ca::Size<uint32_t>& size) override {
    m_projectionMatrix = ca::ortho(-static_cast<float>(size.width) / 2.f,
                                   static_cast<float>(size.width) / 2.f,
                                   static_cast<float>(size.height) / 2.f,
                                   -static_cast<float>(size.height) / 2.f);
  }

  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color{31, 62, 93, 255});

#if 0
    ca::Program::bind(&m_program);
#endif  // 0

    ca::Mat4 viewMatrix;
    // viewMatrix = ca::scale(viewMatrix, ca::Vec3{0.5f, 0.5f, 1.f});
    // viewMatrix = ca::rotate(viewMatrix, 20.f, ca::Vec3{0.f, 0.f, 1.f});
    // viewMatrix = ca::translate(viewMatrix, ca::Vec3{100.f, 0.f, 0.f});

    viewMatrix *= ca::rotate(10.f, ca::Vec3{0.f, 0.f, 1.0f});
    viewMatrix *= ca::scale(ca::Vec3{0.5f, 0.5f, 1.0f});
    viewMatrix *= ca::translate(ca::Vec3{100.f, 10.f, 0.f});

    ca::Mat4 mvp = m_projectionMatrix * viewMatrix;

#if 0
    DCHECK(m_program.setUniform("uni_mvp", mvp));

    ca::Texture::bind(&m_texture);
    m_geometry.render();
#endif  // 0

    m_sprite.render(canvas, mvp);
  }

private:
  ca::Mat4 m_projectionMatrix;

  ca::Program m_program;
  ca::Texture m_texture;
  ca::Geometry m_geometry;

  ca::Sprite m_sprite;

  DISALLOW_COPY_AND_ASSIGN(Rendering);
};

CANVAS_APP(Rendering)

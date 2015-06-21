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
#include "canvas/rendering/geometry.h"
#include "canvas/rendering/program.h"
#include "canvas/rendering/shader.h"
#include "canvas/rendering/text.h"
#include "canvas/rendering/texture.h"
#include "canvas/rendering/vertex_buffer_object.h"
#include "canvas/utils/image.h"
#include "nucleus/logging.h"
#include "nucleus/streams/file_input_stream.h"

class Rendering : public ca::WindowDelegate {
public:
  Rendering() { m_title = "Text"; }

  ~Rendering() override {}

  // Override: ca::WindowDelegate

  void onWindowCreated() override {
    nu::FileInputStream fontStream{
        nu::FilePath{FILE_PATH_LITERAL("C:\\Windows\\Fonts\\arial.ttf")}};

    m_font.loadFromStream(&fontStream);

    m_text.reset(new ca::Text{&m_font, 50, "Hello, World!"});
  }

  void onWindowResized(const ca::Size<u32>& size) override {
    m_projectionMatrix = ca::ortho(-static_cast<float>(size.width) / 2.f,
                                   static_cast<float>(size.width) / 2.f,
                                   static_cast<float>(size.height) / 2.f,
                                   -static_cast<float>(size.height) / 2.f);
  }

  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color{31, 62, 93, 255});

    ca::Mat4 viewMatrix;
    // viewMatrix = ca::scale(viewMatrix, ca::Vec3{100.f, 100.f, 1.f});
    // viewMatrix = ca::rotate(viewMatrix, 20.f, ca::Vec3{0.f, 0.f, 1.f});
    // viewMatrix = ca::translate(viewMatrix, ca::Vec3{100.f, 0.f, 0.f});
    ca::Mat4 mvp = m_projectionMatrix * viewMatrix;

    m_text->render(canvas, mvp);
  }

private:
  ca::Mat4 m_projectionMatrix;

  ca::Font m_font;
  std::unique_ptr<ca::Text> m_text;

  DISALLOW_COPY_AND_ASSIGN(Rendering);
};

CANVAS_APP(Rendering)

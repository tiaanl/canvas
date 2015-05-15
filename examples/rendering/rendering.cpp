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
#include "canvas/rendering/canvas.h"
#include "canvas/rendering/shader.h"
#include "nucleus/logging.h"
#include "nucleus/streams/file_input_stream.h"

class Rendering : public ca::WindowDelegate {
public:
  Rendering() {}
  ~Rendering() override {}

  // Override: ca::WindowDelegate

  void onWindowCreated() override {
    LOG(Info) << "onWindowCreated";

    nu::FileInputStream stream(nu::FilePath{
        L"C:\\Workspace\\canvas\\examples\\rendering\\res\\shaders\\default."
        L"vert.glsl"});
    m_vertShader.loadFromStream(&stream);
  }

  void onPaint(ca::Canvas* canvas) override { canvas->clear(ca::Color{}); }

private:
  ca::Shader m_vertShader{ca::Shader::Vertex};

  DISALLOW_COPY_AND_ASSIGN(Rendering);
};

int main(int argc, char* argv[]) {
  Rendering rendering;

  ca::App app;
  app.addWindow(ca::Window::create(&rendering, "canvas - Rendering Example"));
  app.run();

  return EXIT_SUCCESS;
}

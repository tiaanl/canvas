
#include "canvas/Primitives/Text.h"
#include "canvas/app.h"
#include "canvas/math/transform.h"
#include "canvas/rendering/canvas.h"
#include "canvas/rendering/program.h"
#include "canvas/rendering/shader.h"
#include "nucleus/streams/file_input_stream.h"

class Rendering : public ca::WindowDelegate {
public:
  Rendering() { m_title = "Text"; }

  ~Rendering() override {}

  // Override: ca::WindowDelegate

  bool onWindowCreated() override {
    nu::FileInputStream fontStream{nu::FilePath{FILE_PATH_LITERAL("C:\\Windows\\Fonts\\arial.ttf")}};

    m_font.loadFromStream(&fontStream);

    m_text1.reset(new ca::Text{&m_font, 50, "Hello, World!"});
    m_text2.reset(new ca::Text{&m_font, 30, "Tiaan Louw"});

    return true;
  }

  void onWindowResized(const ca::Size<U32>& size) override {
    m_projectionMatrix = ca::ortho(-static_cast<float>(size.width) / 2.f, static_cast<float>(size.width) / 2.f,
                                   static_cast<float>(size.height) / 2.f, -static_cast<float>(size.height) / 2.f);
  }

  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color{31, 62, 93, 255});

    ca::Mat4 viewMatrix;
    // viewMatrix = ca::scale(viewMatrix, ca::Vec3{100.f, 100.f, 1.f});
    viewMatrix *= ca::rotate(20.f, ca::Vec3{0.f, 0.f, 1.f});
    // viewMatrix = ca::translate(viewMatrix, ca::Vec3{100.f, 0.f, 0.f});
    ca::Mat4 mvp = m_projectionMatrix * viewMatrix;

    m_text1->render(canvas, mvp);
    m_text2->render(canvas, mvp);
  }

private:
  ca::Mat4 m_projectionMatrix;

  ca::Font m_font;
  std::unique_ptr<ca::Text> m_text1;
  std::unique_ptr<ca::Text> m_text2;

  DISALLOW_COPY_AND_ASSIGN(Rendering);
};

CANVAS_APP(Rendering)


#include "canvas/Primitives/Text.h"
#include "canvas/App.h"
#include "canvas/Math/Transform.h"
#include "canvas/Rendering/Font.h"
#include "canvas/Rendering/Program.h"
#include "canvas/Rendering/Shader.h"
#include "nucleus/Streams/FileInputStream.h"

class Rendering : public ca::WindowDelegate {
public:
  Rendering() { m_title = "Text"; }

  ~Rendering() override = default;

  // Override: ca::WindowDelegate

  bool onWindowCreated() override {
#if OS(WIN)
    nu::FileInputStream fontStream{nu::FilePath{"C:\\Windows\\Fonts\\arial.ttf"}};
#elif OS(MACOSX)
    nu::FileInputStream fontStream{nu::FilePath{"/Library/Fonts/Arial.ttf"}};
#endif

    m_font.loadFromStream(&fontStream);

    m_text1.reset(new ca::Text{&m_font, 50, "Hello, yyg!"});

    return true;
  }

  void onWindowResized(const ca::Size<U32>& size) override {
    // m_projectionMatrix = ca::ortho(-static_cast<float>(size.width) / 2.f, static_cast<float>(size.width) / 2.f,
    //                               -static_cast<float>(size.height) / 2.f, static_cast<float>(size.height) / 2.f);

    // Top left = 0, 0
    // Bottom right = width, height
    m_projectionMatrix = ca::ortho(0.f, static_cast<F32>(size.width), static_cast<F32>(size.height), 0.f);
  }

  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color{31, 62, 93, 255});

    ca::Mat4 viewMatrix;
    // viewMatrix = ca::scale(viewMatrix, ca::Vec3{100.f, 100.f, 1.f});
    // viewMatrix *= ca::rotate(20.f, ca::Vec3{0.f, 0.f, 1.f});
    // viewMatrix = ca::translate(viewMatrix, ca::Vec3{100.f, 0.f, 0.f});
    ca::Mat4 mvp = m_projectionMatrix * viewMatrix;

    m_text1->render(canvas, mvp);
  }

private:
  ca::Mat4 m_projectionMatrix;

  ca::Font m_font;
  std::unique_ptr<ca::Text> m_text1;

  DISALLOW_COPY_AND_ASSIGN(Rendering);
};

CANVAS_APP(Rendering)

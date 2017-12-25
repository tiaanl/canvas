
#include "canvas/App.h"
#include "canvas/Math/Mat4.h"
#include "canvas/Math/Transform.h"
#include "canvas/Primitives/Sprite.h"
#include "canvas/Rendering/Shader.h"
#include "nucleus/Utils/Files.h"

class Rendering : public ca::WindowDelegate {
public:
  Rendering() : m_texture() { m_title = "Rendering"; }

  ~Rendering() override = default;

  // Override: ca::WindowDelegate

  bool onWindowCreated() override {
#if 0
    nu::FilePath root{"C:\\Code\\canvas\\examples\\rendering"};

    // Load vertex shader.
    nu::FileInputStream vertStream{root.append(FILE_PATH_LITERAL("res"))
                                       .append(FILE_PATH_LITERAL("shaders"))
                                       .append(FILE_PATH_LITERAL("default.vert.glsl"))};
    ca::Shader vertShader{ca::Shader::Vertex};
    vertShader.loadFromStream(&vertStream);
    m_program.setVertexShader(&vertShader);

    // Load fragment shader.
    nu::FileInputStream fragStream{root.append(FILE_PATH_LITERAL("res"))
                                       .append(FILE_PATH_LITERAL("shaders"))
                                       .append(FILE_PATH_LITERAL("default.frag.glsl"))};
    ca::Shader fragShader{ca::Shader::Fragment};
    fragShader.loadFromStream(&fragStream);
    m_program.setFragmentShader(&fragShader);

    // Make sure the program is linked.
    m_program.link();

    // And use the program.
    ca::Program::bind(&m_program);

    if (!m_texture.createFromImage(image)) {
      return false;
    }

    // Create some geometry that we can render.
    m_geometry = ca::Geometry::createRectangle(ca::Rect<F32>{-0.5f, -0.5f, 1.f, 1.f}, ca::Color{255, 0, 0, 127});
    m_geometry.compileAndUpload();

    // Set up the sprite.
    m_sprite.setTexture(&m_texture);
#endif  // 0

    return true;
  }

  void onWindowResized(const ca::Size<U32>& size) override {
    m_projectionMatrix = ca::ortho(-static_cast<float>(size.width) / 2.f, static_cast<float>(size.width) / 2.f,
                                   static_cast<float>(size.height) / 2.f, -static_cast<float>(size.height) / 2.f);
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

    //    viewMatrix *= ca::rotate(10.f, ca::Vec3{0.f, 0.f, 1.0f});
    //    viewMatrix *= ca::scale(ca::Vec3{0.5f, 0.5f, 1.0f});
    //    viewMatrix *= ca::translate(ca::Vec3{100.f, 10.f, 0.f});

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

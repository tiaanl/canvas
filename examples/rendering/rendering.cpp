
#include "canvas/App.h"
#include "canvas/Math/Mat4.h"
#include "canvas/Math/Transform.h"
#include "canvas/Primitives/Sprite.h"
#include "canvas/Rendering/Shader.h"
#include "canvas/Resources/ResourceManager.h"
#include "nucleus/Files.h"

using ca::ResourceRef;
using ca::Shader;
using ca::Texture;

class Rendering : public ca::WindowDelegate {
public:
  explicit Rendering() : ca::WindowDelegate("Rendering"), m_texture() {}

  ~Rendering() override = default;

  // Override: ca::WindowDelegate

  bool onWindowCreated() override {
    m_resourceManager.setRootPath(nu::getCurrentWorkingDirectory().append("res"));

    // ResourceRef<Shader> vertexShader = m_resourceManager.getShader("shaders/default.vert.glsl", Shader::Vertex);
    // m_program.setVertexShader(vertexShader);

    // ResourceRef<Shader> fragmentShader = m_resourceManager.getShader("shaders/default.frag.glsl", Shader::Fragment);
    // m_program.setFragmentShader(fragmentShader);

    // Make sure the program is linked.
    // m_program.link();

    // And use the program.
    // ca::Program::bind(&m_program);

    m_texture = m_resourceManager.getTexture("images/canvas.png");
    if (!m_texture) {
      return false;
    }

    // Create some geometry that we can render.
    m_geometry = ca::Geometry::createRectangle(ca::Rect<F32>{-0.5f, -0.5f, 1.f, 1.f}, ca::Color{255, 0, 0, 127});
    m_geometry.compileAndUpload();

    // Set up the sprite.
    m_sprite.setTexture(&m_texture.get()->get());

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
  ca::ResourceManager m_resourceManager;

  ca::Mat4 m_projectionMatrix;

  ResourceRef<Texture> m_texture;

  ca::Program m_program;
  ca::Geometry m_geometry;

  ca::Sprite m_sprite;

  DISALLOW_COPY_AND_ASSIGN(Rendering);
};

CANVAS_APP(Rendering)

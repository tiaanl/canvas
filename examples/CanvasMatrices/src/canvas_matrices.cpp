#include <canvas/App.h>
#include <floats/Transform.h>

static const char* VERTEX_SHADER = R"(
#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

uniform mat4 u_mvp;

out vec4 vertex_color;

void main() {
  gl_Position = u_mvp * vec4(inPosition, 1.0);
  vertex_color = inColor;
}
)";

static const char* FRAGMENT_SHADER = R"(
#version 330

in vec4 vertex_color;

out vec4 final;

void main() {
  final = vertex_color;
}
)";

class Matrices : public ca::WindowDelegate {
public:
  Matrices() : ca::WindowDelegate{"Canvas | Matrices"} {}

  bool onWindowCreated(ca::Window* window) override {
    if (!WindowDelegate::onWindowCreated(window)) {
      return false;
    }

    auto* renderer = window->getRenderer();

    // clang-format off
    static F32 vertices[] = {
        // Left
        -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 1.0f,

        // Right
         0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f, 1.0f,

        // Back
         0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 1.0f,

        // Front
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f, 1.0f,

        // Top
         0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 1.0f, 1.0f,

        // Bottom
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f, 1.0f,
    };
    // clang-format on

    auto def = ca::VertexDefinition();
    def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
    def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Four);
    vertex_buffer_id_ = renderer->createVertexBuffer(def, vertices, sizeof(vertices));
    if (!vertex_buffer_id_) {
      return false;
    }

    program_id_ = renderer->createProgram(ca::ShaderSource::from(VERTEX_SHADER),
                                          ca::ShaderSource::from(FRAGMENT_SHADER));
    if (!program_id_) {
      return false;
    }

    mvp_uniform_id_ = renderer->createUniform("u_mvp");
    if (!mvp_uniform_id_) {
      return false;
    }

    return true;
  }

  void onWindowResized(const fl::Size& size) override {
    WindowDelegate::onWindowResized(size);

    if (size.height) {
      aspect_ratio_ = static_cast<F32>(size.width) / static_cast<F32>(size.height);
    }
  }

  void on_mouse_moved(const ca::MouseEvent& evt) override {
    WindowDelegate::on_mouse_moved(evt);

    if (is_dragging_) {
      F32 delta_x = static_cast<F32>(evt.pos.x - last_mouse_pos_.x);
      F32 delta_y = static_cast<F32>(evt.pos.y - last_mouse_pos_.y);

      last_mouse_pos_ = evt.pos;

      horizontal_ += delta_x;
      vertical_ += delta_y;
    }
  }

  void on_mouse_pressed(const ca::MouseEvent& evt) override {
    WindowDelegate::on_mouse_pressed(evt);

    if (evt.button == ca::MouseEvent::Button::Left) {
      is_dragging_ = true;
      last_mouse_pos_ = evt.pos;
    }
  }

  void on_mouse_released(const ca::MouseEvent& evt) override {
    WindowDelegate::on_mouse_released(evt);

    if (is_dragging_ && evt.button == ca::MouseEvent::Button::Left) {
      is_dragging_ = false;
    }
  }

  void on_key_pressed(const ca::KeyEvent& evt) override {
    WindowDelegate::on_key_pressed(evt);

    if (evt.key == ca::Key::R) {
      horizontal_ = 30.0f;
      vertical_ = 20.0f;
    }
  }

  void onRender(ca::Renderer* renderer) override {
    // auto mvp = fl::Mat4::identity;
    auto projection =
        fl::perspectiveProjection(fl::Angle::fromDegrees(60.0f), aspect_ratio_, 0.1f, 100.0f);

    auto rotation_1 = fl::Quaternion::fromEulerAngles(fl::Angle::fromDegrees(vertical_),
                                                      fl::Angle::zero, fl::Angle::zero)
                          .toRotationMatrix();
    auto rotation_2 = fl::Quaternion::fromEulerAngles(
                          fl::Angle::zero, fl::Angle::fromDegrees(horizontal_), fl::Angle::zero)
                          .toRotationMatrix();
    auto translation = fl::translationMatrix({0.0f, 0.0f, -5.0f});

    auto mvp = projection * (translation * rotation_1 * rotation_2);

    ca::UniformBuffer uniforms;
    uniforms.set(mvp_uniform_id_, mvp);

    renderer->state().depth_test(true);
    renderer->draw(ca::DrawType::Triangles, 0, 36, program_id_, vertex_buffer_id_, {}, uniforms);
  }

private:
  ca::VertexBufferId vertex_buffer_id_;
  ca::ProgramId program_id_;
  ca::UniformId mvp_uniform_id_;

  F32 aspect_ratio_ = 1.0f;

  bool is_dragging_ = false;

  fl::Pos last_mouse_pos_;
  F32 horizontal_ = 30.0f;
  F32 vertical_ = 20.0f;
};

CANVAS_APP(Matrices)

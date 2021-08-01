
#include <canvas/app.h>

const char* VERTEX_SHADER_SOURCE = R"(#version 330 core

layout(location = 0) in vec3 in_position;

void main() {
  gl_Position = vec4(in_position, 1.0);
}
)";

const char* FRAGMENT_SHADER_SOURCE = R"(#version 330 core

out vec4 frag_color;

uniform vec4 u_color;

void main() {
  frag_color = u_color;
}
)";

class Triangle : public ca::WindowDelegate {
  NU_DELETE_COPY_AND_MOVE(Triangle);

public:
  Triangle() : WindowDelegate("01 - Triangle") {}

  bool on_window_created(ca::Window* window) override {
    if (!WindowDelegate::on_window_created(window)) {
      return false;
    }

    auto* renderer = window->getRenderer();

    // Set up the pipeline.
    pipeline_ = renderer->create_pipeline_builder()
                    .attribute("position", ca::ComponentType::Float32, ca::ComponentCount::Three)
                    .vertex_shader(ca::ShaderSource::from(VERTEX_SHADER_SOURCE))
                    .fragment_shader(ca::ShaderSource::from(FRAGMENT_SHADER_SOURCE))
                    .build();
    if (!pipeline_.has_value()) {
      LOG(Error) << "Could not create render pipeline.";
      return false;
    }

    // Create the geometry of the triangle we want to render.
    F32 vertices[] = {
        -0.5f,  -0.5f, 0.0f,  // Lower left corner
        0.5f,   -0.5f, 0.0f,  // Lower right corner
        0.0f,   0.5f,  0.0f,  // Upper corner
        -0.25f, 0.0f,  0.0f,  // Inner left
        0.25f,  0.0f,  0.0f,  // Inner right
        0.0f,   -0.5f, 0.0f   // Inner down
    };

    vertex_buffer_id_ = pipeline_->create_vertex_buffer(vertices, sizeof(vertices));
    if (!vertex_buffer_id_) {
      LOG(Error) << "Could not create vertex buffer.";
      return false;
    }

    U16 indices[] = {
        0, 3, 5,  // Lower left triangle
        3, 2, 4,  // Lower right triangle
        5, 4, 1   // Upper triangle
    };

    index_buffer_id_ =
        renderer->create_index_buffer(ca::ComponentType::Unsigned16, indices, sizeof(indices));
    if (!index_buffer_id_) {
      LOG(Error) << "Could not create index buffer.";
      return false;
    }

    auto color_uniform_id = renderer->create_uniform("u_color");
    if (!color_uniform_id) {
      LOG(Error) << "Could not create color uniform.";
      return false;
    }

    uniforms_.set(color_uniform_id, ca::Color{0.949f, 0.667f, 0.298f});

    return true;
  }

  void on_render(ca::Renderer* renderer) override {
    renderer->clear(ca::Color{0.063f, 0.094f, 0.125f});
    pipeline_->draw(ca::DrawType::Triangles, 9, vertex_buffer_id_, index_buffer_id_, {}, uniforms_);
  }

private:
  nu::Optional<ca::Pipeline> pipeline_;
  ca::VertexBufferId vertex_buffer_id_;
  ca::IndexBufferId index_buffer_id_;
  ca::UniformBuffer uniforms_;
};

CANVAS_APP(Triangle)

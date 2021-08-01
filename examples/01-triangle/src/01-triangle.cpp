
#include <canvas/app.h>
#include <canvas/renderer/pipeline_builder.h>

const char *VERTEX_SHADER_SOURCE = R"(#version 330 core

layout(location = 0) in vec3 in_position;

void main() {
  gl_Position = vec4(in_position, 1.0);
}
)";

const char *FRAGMENT_SHADER_SOURCE = R"(#version 330 core

out vec4 frag_color;

void main() {
  frag_color = vec4(1.0, 0.0, 0.0, 1.0);
}
)";

class Triangle : public ca::WindowDelegate {
  NU_DELETE_COPY_AND_MOVE(Triangle);

public:
  Triangle() : WindowDelegate("01 - Triangle") {}

  bool on_window_created(ca::Window *window) override {
    if (!WindowDelegate::on_window_created(window)) {
      return false;
    }

    // Set up the pipeline.
    pipeline_ = ca::PipelineBuilder{}
                    .attribute("position", ca::ComponentType::Float32, ca::ComponentCount::Three)
                    .vertex_shader(ca::ShaderSource::from(VERTEX_SHADER_SOURCE))
                    .fragment_shader(ca::ShaderSource::from(FRAGMENT_SHADER_SOURCE))
                    .build(window->getRenderer());
    if (!pipeline_.has_value()) {
      LOG(Error) << "Could not create render pipeline.";
      return false;
    }

    // Create the geometry of the triangle we want to render.
    F32 vertices[] = {
        -0.5f, -0.5f, 0.0f,  // Lower left corner
        0.5f,  -0.5f, 0.0f,  // Lower right corner
        0.0f,  0.5f,  0.0f   // Upper corner
    };

    vertex_buffer_id_ = pipeline_->create_vertex_buffer(vertices, sizeof(vertices));
    if (!vertex_buffer_id_) {
      LOG(Error) << "Could not create vertex buffer.";
      return false;
    }

    return true;
  }

  void on_render(ca::Renderer *renderer) override {
    renderer->clear(ca::Color::black);
    pipeline_->draw(ca::DrawType::Triangles, 0, 3, vertex_buffer_id_);
  }

private:
  nu::Optional<ca::Pipeline> pipeline_;
  ca::VertexBufferId vertex_buffer_id_;
};

CANVAS_APP(Triangle)

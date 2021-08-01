#include <canvas/app.h>
#include <floats/transform.h>

const char* VERTEX_SHADER_SOURCE = R"(#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 0) in vec3 in_color;
layout(location = 0) in vec2 in_tex_coord;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out vec3 v_color;
out vec2 v_tex_coord;

void main() {
  gl_Position = u_projection * u_view * u_model * vec4(in_position, 1.0);
  v_color = in_color;
  v_tex_coord = in_tex_coord;
}
)";

const char* FRAGMENT_SHADER_SOURCE = R"(#version 330 core

in vec3 v_color;
in vec2 v_tex_coord;

out vec4 frag_color;

void main() {
  frag_color = vec4(v_color, 1.0);
}
)";

class Triangle : public ca::WindowDelegate {
  NU_DELETE_COPY_AND_MOVE(Triangle);

public:
  Triangle() : WindowDelegate("02 - Cube") {}

  bool on_window_created(ca::Window* window) override {
    if (!WindowDelegate::on_window_created(window)) {
      return false;
    }

    auto* renderer = window->getRenderer();

    // renderer->state().cull_face(true);
    renderer->state().depth_test(true);

    if (!create_geometry(renderer)) {
      return false;
    }

    projection_uniform_id_ = renderer->create_uniform("u_projection");
    if (!projection_uniform_id_) {
      LOG(Error) << "Could not create color uniform.";
      return false;
    }

    auto view_uniform_id = renderer->create_uniform("u_view");
    if (!view_uniform_id) {
      LOG(Error) << "Could not create color uniform.";
      return false;
    }

    // Set up the view matrix.
    auto view_matrix = fl::look_at(fl::Vec3::forward * -3.0f, fl::Vec3::zero, fl::Vec3::up);
    uniforms_.set(view_uniform_id, view_matrix);

    model_uniform_id_ = renderer->create_uniform("u_model");
    if (!model_uniform_id_) {
      LOG(Error) << "Could not create color uniform.";
      return false;
    }

    // Set up projection matrix.
    update_projection_matrix(renderer->size());

    return true;
  }

  void on_window_resized(const fl::Size& size) override {
    WindowDelegate::on_window_resized(size);

    update_projection_matrix(size);
  }

  void on_tick(F32 delta) override {
    WindowDelegate::on_tick(delta);

    rotation_angle_ += delta * 0.5f;
    if (rotation_angle_ >= 360.0f) {
      rotation_angle_ -= 360.0f;
    }
  }

  void on_render(ca::Renderer* renderer) override {
    renderer->clear(ca::Color{0.063f, 0.094f, 0.125f});

    // Update the model matrix for each frame.

    auto model_matrix = fl::rotation_matrix(fl::normalize(fl::Vec3::up + fl::Vec3::right),
                                            fl::Angle::fromDegrees(rotation_angle_));
    uniforms_.set(model_uniform_id_, model_matrix);

    // Render the geometry.

    pipeline_->draw(ca::DrawType::Triangles, 6 * 3, vertex_buffer_id_, index_buffer_id_, {},
                    uniforms_);
  }

private:
  bool create_geometry(ca::Renderer* renderer) {
    // Set up the pipeline.
    pipeline_ = renderer->create_pipeline_builder()
                    .attribute("position", ca::ComponentType::Float32, ca::ComponentCount::Three)
                    .attribute("color", ca::ComponentType::Float32, ca::ComponentCount::Three)
                    .attribute("tex_coord", ca::ComponentType::Float32, ca::ComponentCount::Two)
                    .vertex_shader(ca::ShaderSource::from(VERTEX_SHADER_SOURCE))
                    .fragment_shader(ca::ShaderSource::from(FRAGMENT_SHADER_SOURCE))
                    .build();
    if (!pipeline_.has_value()) {
      LOG(Error) << "Could not create render pipeline.";
      return false;
    }

    // Create the geometry of the triangle we want to render.
    F32 vertices[] = {
        -0.5f, 0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 0.0f, 0.0f,  //
        -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,  //
        0.5f,  0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,  //
        0.5f,  0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 5.0f, 0.0f,  //
        0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f, 2.5f, 5.0f,  //
    };

    vertex_buffer_id_ = pipeline_->create_vertex_buffer(vertices, sizeof(vertices));
    if (!vertex_buffer_id_) {
      LOG(Error) << "Could not create vertex buffer.";
      return false;
    }

    U16 indices[] = {
        0, 1, 2,  //
        0, 2, 3,  //
        0, 1, 4,  //
        1, 2, 4,  //
        4, 2, 3,  //
        4, 3, 0,  //
    };

    index_buffer_id_ =
        renderer->create_index_buffer(ca::ComponentType::Unsigned16, indices, sizeof(indices));
    if (!index_buffer_id_) {
      LOG(Error) << "Could not create index buffer.";
      return false;
    }

    return true;
  }

  void update_projection_matrix(const fl::Size& size) {
    const F32 aspect_ratio = fl::aspect_ratio(size);
    auto projection_matrix =
        fl::perspective_projection(fl::Angle::fromDegrees(45.0f), aspect_ratio, 0.01f, 100.0f);
    uniforms_.set(projection_uniform_id_, projection_matrix);
  }

  nu::Optional<ca::Pipeline> pipeline_;

  ca::VertexBufferId vertex_buffer_id_;
  ca::IndexBufferId index_buffer_id_;
  ca::UniformBuffer uniforms_;

  ca::UniformId projection_uniform_id_;
  ca::UniformId model_uniform_id_;

  F32 rotation_angle_ = 0.0f;
};

CANVAS_APP(Triangle)

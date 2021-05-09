#include <canvas/App.h>
#include <floats/Transform.h>

static const unsigned DIFFUSE_TEXTURE_WIDTH = 5;
static const unsigned DIFFUSE_TEXTURE_HEIGHT = 5;

static const unsigned NORMALS_TEXTURE_WIDTH = 8;
static const unsigned NORMALS_TEXTURE_HEIGHT = 8;

static const char* MATERIAL_VERTEX_SHADER = R"(
#version 330

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_tex_coord;
layout(location = 2) in vec3 in_normal;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out vec2 vertex_tex_coord;
out vec3 vertex_normal;
out vec3 fragment_position;

void main() {
  gl_Position = u_projection * u_view * u_model * vec4(in_position, 1.0);
  vertex_tex_coord = in_tex_coord;
  vertex_normal = in_normal;
  fragment_position = vec3(u_model * vec4(in_position, 1.0));
}
)";

static const char* MATERIAL_FRAGMENT_SHADER = R"(
#version 330

in vec2 vertex_tex_coord;
in vec3 vertex_normal;
in vec3 fragment_position;

out vec4 final;

uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_light_position;
uniform float u_ambient_light_intensity;

uniform sampler2D u_diffuse_texture;
uniform sampler2D u_normals_texture;

void main() {
  vec3 normal = normalize(vertex_normal * texture(u_normals_texture, vertex_tex_coord).xyz);
  vec3 direction_to_light = normalize(u_light_position - fragment_position);
  float light_intensity = max(dot(vertex_normal, direction_to_light), 0.0);
  light_intensity += u_ambient_light_intensity;

  vec4 textured_color = texture(u_diffuse_texture, vertex_tex_coord);
  final = vec4(light_intensity * textured_color.xyz, 1.0);
}
)";

static const char* LIGHT_VERTEX_SHADER = R"(
#version 330

layout(location = 0) in vec3 in_position;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main() {
  gl_Position = u_projection * u_view * u_model * vec4(in_position, 1.0);
}
)";

static const char* LIGHT_FRAGMENT_SHADER = R"(
#version 330

out vec4 final;

void main() {
  final = vec4(1.0, 1.0, 1.0, 1.0);
}
)";

// clang-format off
static const fl::Vec3 VERTICES[] = {
    { 0.5,  0.5,  0.5},
    { 0.5,  0.5, -0.5},
    { 0.5, -0.5,  0.5},
    { 0.5, -0.5, -0.5},
    {-0.5,  0.5,  0.5},
    {-0.5,  0.5, -0.5},
    {-0.5, -0.5,  0.5},
    {-0.5, -0.5, -0.5},
};

static const fl::Vec2 TEX_COORDS[] = {
    {0.0, 1.0},
    {1.0, 0.0},
    {1.0, 1.0},
    {1.0, 1.0},
    {0.0, 0.0},
    {1.0, 0.0},
    {0.0, 1.0},
    {1.0, 0.0},
    {1.0, 1.0},
    {0.0, 1.0},
    {0.0, 0.0},
    {1.0, 0.0},
    {0.0, 0.0},
    {0.0, 0.0},
    {1.0, 1.0},
    {0.0, 1.0},
};

static const fl::Vec3 NORMALS[] = {
    { 0.0,  0.0,  1.0},
    { 0.0, -1.0,  0.0},
    {-1.0,  0.0,  0.0},
    { 0.0,  0.0, -1.0},
    { 1.0,  0.0,  0.0},
    { 0.0,  1.0,  0.0},
};

static const U8 FACES[] = {
    5, 1, 1,   3,  2, 1,   1,  3, 1,
    3, 4, 2,   8,  5, 2,   4,  6, 2,
    7, 7, 3,   6,  8, 3,   8,  5, 3,
    2, 9, 4,   8,  5, 4,   6, 10, 4,
    1, 3, 5,   4, 11, 5,   2, 12, 5,
    5, 1, 6,   2, 12, 6,   6, 13, 6,
    5, 1, 1,   7, 14, 1,   3,  2, 1,
    3, 4, 2,   7,  7, 2,   8,  5, 2,
    7, 7, 3,   5, 15, 3,   6,  8, 3,
    2, 9, 4,   4,  6, 4,   8,  5, 4,
    1, 3, 5,   3, 16, 5,   4, 11, 5,
    5, 1, 6,   1,  3, 6,   2, 12, 6,
};
// clang-format on

struct Vertex {
  fl::Vec3 position;
  fl::Vec2 tex_coord;
  fl::Vec3 normal;
};

nu::DynamicArray<fl::Vec3> build_light_box() {
  nu::DynamicArray<fl::Vec3> result;

  for (unsigned i = 0; i < NU_ARRAY_SIZE(FACES); i += 3) {
    unsigned vertex_index = FACES[i] - 1;
    result.pushBack(VERTICES[vertex_index] * 0.1f);
  }

  return result;
}

nu::DynamicArray<Vertex> build_mesh() {
  nu::DynamicArray<Vertex> result;

  for (unsigned i = 0; i < NU_ARRAY_SIZE(FACES); i += 3) {
    auto vertex_index = FACES[i + 0] - 1;
    auto tex_coord_index = FACES[i + 1] - 1;
    auto normal_index = FACES[i + 2] - 1;

    Vertex v{
        VERTICES[vertex_index],
        TEX_COORDS[tex_coord_index],
        NORMALS[normal_index],
    };

    result.pushBack(v);
  }

  return result;
}

struct Color {
  U8 red;
  U8 green;
  U8 blue;
  U8 alpha;
};

nu::DynamicArray<Color> build_diffuse_texture() {
  nu::DynamicArray<Color> result;

  for (unsigned y = 0; y < DIFFUSE_TEXTURE_HEIGHT; ++y) {
    for (unsigned x = 0; x < DIFFUSE_TEXTURE_WIDTH; ++x) {
      if ((y * DIFFUSE_TEXTURE_WIDTH + x) % 2 == 0) {
        result.pushBack({255, 0, 0, 255});
      } else {
        result.pushBack({0, 255, 0, 255});
      }
    }
  }

  return result;
}

nu::DynamicArray<Color> build_normals_texture() {
  nu::DynamicArray<Color> result;

  static constexpr auto bevel_width = 3;

  for (unsigned y = 0; y < NORMALS_TEXTURE_HEIGHT; ++y) {
    for (unsigned x = 0; x < NORMALS_TEXTURE_WIDTH; ++x) {
      fl::Vec3 normal = {0.0f, 0.0f, 1.0f};

      if (x < bevel_width) {
        normal.x = -1.0f;
      } else if (x >= NORMALS_TEXTURE_WIDTH - bevel_width) {
        normal.x = 1.0f;
      }

      if (y < bevel_width) {
        normal.y = -1.0f;
      } else if (y >= NORMALS_TEXTURE_WIDTH - bevel_width) {
        normal.y = 1.0f;
      }

      normal = fl::normalize(normal);

      result.pushBack({static_cast<U8>(static_cast<F32>(normal.x) * 255.0f),
                       static_cast<U8>(static_cast<F32>(normal.y) * 255.0f),
                       static_cast<U8>(static_cast<F32>(normal.z) * 255.0f), 255});
    }
  }

  return result;
}

class Matrices : public ca::WindowDelegate {
public:
  Matrices() : ca::WindowDelegate{"Canvas | Matrices"} {}

  bool onWindowCreated(ca::Window* window) override {
    if (!WindowDelegate::onWindowCreated(window)) {
      return false;
    }

    auto* renderer = window->getRenderer();
    auto def = ca::VertexDefinition();
    def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
    def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);
    def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);

    auto vertices = build_mesh();
    vertex_buffer_id_ =
        renderer->createVertexBuffer(def, vertices.data(), vertices.size() * sizeof(Vertex));
    if (!vertex_buffer_id_) {
      return false;
    }

    auto box_vertices = build_light_box();
    auto light_box_def = ca::VertexDefinition{};
    light_box_def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
    light_box_vertex_buffer_id_ = renderer->createVertexBuffer(
        light_box_def, box_vertices.data(), box_vertices.size() * sizeof(fl::Vec3));

    material_program_id_ =
        renderer->createProgram(ca::ShaderSource::from(MATERIAL_VERTEX_SHADER),
                                ca::ShaderSource::from(MATERIAL_FRAGMENT_SHADER));
    if (!material_program_id_) {
      return false;
    }

    light_program_id_ = renderer->createProgram(ca::ShaderSource::from(LIGHT_VERTEX_SHADER),
                                                ca::ShaderSource::from(LIGHT_FRAGMENT_SHADER));
    if (!light_program_id_) {
      return false;
    }

    auto diffuse_texture = build_diffuse_texture();
    diffuse_texture_id_ = renderer->createTexture(
        ca::TextureFormat::RGBA, {DIFFUSE_TEXTURE_WIDTH, DIFFUSE_TEXTURE_HEIGHT},
        diffuse_texture.data(), diffuse_texture.size() * sizeof(Color), false);
    if (!diffuse_texture_id_) {
      return false;
    }

    auto normals_texture = build_normals_texture();
    normals_texture_id_ = renderer->createTexture(
        ca::TextureFormat::RGBA, {NORMALS_TEXTURE_WIDTH, NORMALS_TEXTURE_HEIGHT},
        normals_texture.data(), normals_texture.size() * sizeof(Color), false);
    if (!normals_texture_id_) {
      return false;
    }

    projection_matrix_uniform_id_ = renderer->createUniform("u_projection");
    if (!projection_matrix_uniform_id_) {
      return false;
    }

    view_matrix_uniform_id_ = renderer->createUniform("u_view");
    if (!view_matrix_uniform_id_) {
      return false;
    }

    model_matrix_uniform_id_ = renderer->createUniform("u_model");
    if (!model_matrix_uniform_id_) {
      return false;
    }

    light_position_uniform_id_ = renderer->createUniform("u_light_position");
    if (!light_position_uniform_id_) {
      return false;
    }

    ambient_light_intensity_uniform_id_ = renderer->createUniform("u_ambient_light_intensity");
    if (!ambient_light_intensity_uniform_id_) {
      return false;
    }

    diffuse_texture_uniform_id_ = renderer->createUniform("u_diffuse_texture");
    if (!diffuse_texture_uniform_id_) {
      return false;
    }

    normals_texture_uniform_id_ = renderer->createUniform("u_normals_texture");
    if (!normals_texture_uniform_id_) {
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
      while (horizontal_ > 360.0f) {
        horizontal_ -= 360.0f;
      }
      vertical_ += delta_y;
      vertical_ = fl::clamp(vertical_, -89.0f, 89.0f);
    }
  }

  bool on_mouse_pressed(const ca::MouseEvent& evt) override {
    WindowDelegate::on_mouse_pressed(evt);

    if (evt.button == ca::MouseEvent::Button::Left) {
      is_dragging_ = true;
      last_mouse_pos_ = evt.pos;

      return true;
    }

    return false;
  }

  void on_mouse_released(const ca::MouseEvent& evt) override {
    WindowDelegate::on_mouse_released(evt);

    if (is_dragging_ && evt.button == ca::MouseEvent::Button::Left) {
      is_dragging_ = false;
    }
  }

  void on_key_pressed(const ca::KeyEvent& evt) override {
    WindowDelegate::on_key_pressed(evt);

    if (evt.key == ca::Key::Left) {
      light_position_.x -= 0.1f;
    } else if (evt.key == ca::Key::Right) {
      light_position_.x += 0.1f;
    } else if (evt.key == ca::Key::Up) {
      light_position_.y += 0.1f;
    } else if (evt.key == ca::Key::Down) {
      light_position_.y -= 0.1f;
    } else if (evt.key == ca::Key::R) {
      horizontal_ = 30.0f;
      vertical_ = 20.0f;
    }
  }

  void onRender(ca::Renderer* renderer) override {
    auto projection_matrix =
        fl::perspectiveProjection(fl::Angle::fromDegrees(60.0f), aspect_ratio_, 0.1f, 100.0f);

    auto rotation_1 = fl::Quaternion::fromEulerAngles(fl::Angle::fromDegrees(vertical_),
                                                      fl::Angle::zero, fl::Angle::zero)
                          .toRotationMatrix();
    auto rotation_2 = fl::Quaternion::fromEulerAngles(
                          fl::Angle::zero, fl::Angle::fromDegrees(horizontal_), fl::Angle::zero)
                          .toRotationMatrix();
    auto translation = fl::translationMatrix({0.0f, 0.0f, -5.0f});

    auto view_matrix = translation * rotation_1 * rotation_2;

    auto model_matrix = fl::Mat4::identity;

    renderer->state().depth_test(true);

    ca::UniformBuffer uniforms;
    uniforms.set(projection_matrix_uniform_id_, projection_matrix);
    uniforms.set(view_matrix_uniform_id_, view_matrix);
    uniforms.set(model_matrix_uniform_id_, model_matrix);
    uniforms.set(light_position_uniform_id_, light_position_);
    uniforms.set(ambient_light_intensity_uniform_id_, ambient_light_intensity_);
    uniforms.set(diffuse_texture_uniform_id_, static_cast<I32>(0));
    uniforms.set(normals_texture_uniform_id_, static_cast<I32>(1));

    renderer->draw(ca::DrawType::Triangles, 0, sizeof(FACES) / 3, material_program_id_,
                   vertex_buffer_id_, {diffuse_texture_id_, normals_texture_id_}, uniforms);

    model_matrix = fl::translationMatrix(light_position_);

    ca::UniformBuffer light_box_uniforms;
    light_box_uniforms.set(projection_matrix_uniform_id_, projection_matrix);
    light_box_uniforms.set(view_matrix_uniform_id_, view_matrix);
    light_box_uniforms.set(model_matrix_uniform_id_, model_matrix);
    renderer->draw(ca::DrawType::Triangles, 0, sizeof(FACES) / 3, light_program_id_,
                   light_box_vertex_buffer_id_, {}, light_box_uniforms);
  }

private:
  ca::UniformId projection_matrix_uniform_id_;
  ca::UniformId view_matrix_uniform_id_;
  ca::UniformId model_matrix_uniform_id_;
  ca::UniformId light_position_uniform_id_;
  ca::UniformId ambient_light_intensity_uniform_id_;
  ca::UniformId diffuse_texture_uniform_id_;
  ca::UniformId normals_texture_uniform_id_;

  ca::ProgramId material_program_id_;
  ca::VertexBufferId vertex_buffer_id_;
  ca::TextureId diffuse_texture_id_;
  ca::TextureId normals_texture_id_;

  F32 ambient_light_intensity_ = 0.2f;
  fl::Vec3 light_position_ = fl::Vec3{1.0f, 1.0f, 1.0f};
  ca::ProgramId light_program_id_;
  ca::VertexBufferId light_box_vertex_buffer_id_;

  F32 aspect_ratio_ = 1.0f;

  bool is_dragging_ = false;

  fl::Pos last_mouse_pos_;
  F32 horizontal_ = 30.0f;
  F32 vertical_ = 20.0f;
};

CANVAS_APP(Matrices)

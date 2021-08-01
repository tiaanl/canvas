
#include <canvas/app.h>
#include <canvas/static_data/all.h>
#include <nucleus/file_path.h>
#include <nucleus/streams/file_input_stream.h>

class Minimal : public ca::WindowDelegate {
  NU_DELETE_COPY_AND_MOVE(Minimal);

public:
  Minimal()
    : ca::WindowDelegate("Canvas Minimal Example"), root_path_(nu::getExecutablePath().dirName()) {}

  ~Minimal() override = default;

  bool on_window_created(ca::Window* window) override {
    LOG(Info) << "Root path: " << root_path_.getPath();

    ca::Renderer* renderer = window->getRenderer();

    if (!load_program(renderer)) {
      LOG(Error) << "Could not create program";
      return false;
    }

    if (!load_vertex_buffer(renderer)) {
      LOG(Error) << "Could not create vertex buffer and index buffer.";
      return false;
    }

    if (!load_texture(renderer)) {
      LOG(Error) << "Could not create texture.";
      return false;
    }

    scale_uniform_ = renderer->createUniform("uScale");
    uniforms_.set(scale_uniform_, 0.5f);

    return true;
  }

  void on_render(ca::Renderer* renderer) override {
    PROFILE("Minimal Frame")

    {
      PROFILE("clear")
      renderer->clear(ca::Color{0.0f, 0.1f, 0.2f});
    }

    {
      PROFILE("draw")
      renderer->draw(ca::DrawType::Triangles, 6, program_id_, vertex_buffer_id_, index_buffer_id_,
                     texture_id_, uniforms_);
    }
  }

private:
  bool load_program(ca::Renderer* renderer) {
    nu::FileInputStream vs{root_path_ / "default.vs"};
    if (!vs.openedOk()) {
      return false;
    }

    nu::FileInputStream fs{root_path_ / "default.fs"};
    if (!fs.openedOk()) {
      return false;
    }

    program_id_ = renderer->createProgram(ca::ShaderSource::from(&vs), ca::ShaderSource::from(&fs));

    return isValid(program_id_);
  }

  bool load_vertex_buffer(ca::Renderer* renderer) {
    ca::VertexDefinition def;
    def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
    def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);

    static struct {
      F32 x;
      F32 y;
      F32 z;
      F32 u;
      F32 v;
    } vertices[] = {
        {-1.0f, 1.0f, 1.0f, 0.0f, 0.0f},   //
        {1.0f, 1.0f, 1.0f, 1.0f, 0.0f},    //
        {-1.0f, -1.0f, 1.0f, 0.0f, 1.0f},  //
        {1.0f, -1.0f, 1.0f, 1.0f, 1.0f},   //

        {-1.0f, 1.0f, -1.0f, 0.0f, 0.0f},   //
        {1.0f, 1.0f, -1.0f, 1.0f, 0.0f},    //
        {-1.0f, -1.0f, -1.0f, 0.0f, 1.0f},  //
        {1.0f, -1.0f, -1.0f, 1.0f, 1.0f},   //

        {-1.0f, 1.0f, 1.0f, 0.0f, 0.0f},   //
        {1.0f, 1.0f, 1.0f, 1.0f, 0.0f},    //
        {-1.0f, 1.0f, -1.0f, 0.0f, 1.0f},  //
        {1.0f, 1.0f, -1.0f, 1.0f, 1.0f},   //

        {-1.0f, -1.0f, 1.0f, 0.0f, 0.0f},   //
        {1.0f, -1.0f, 1.0f, 1.0f, 0},       //
        {-1.0f, -1.0f, -1.0f, 0.0f, 1.0f},  //
        {1.0f, -1.0f, -1.0f, 1.0f, 1.0f},   //

        {1.0f, -1.0f, 1.0f, 0.0f, 0.0f},   //
        {1.0f, 1.0f, 1.0f, 1.0f, 0},       //
        {1.0f, -1.0f, -1.0f, 0.0f, 1.0f},  //
        {1.0f, 1.0f, -1.0f, 1.0f, 1.0f},   //

        {-1.0f, -1.0f, 1.0f, 0.0f, 0.0f},   //
        {-1.0f, 1.0f, 1.0f, 1.0f, 0.0f},    //
        {-1.0f, -1.0f, -1.0f, 0.0f, 1.0f},  //
        {-1.0f, 1.0f, -1.0f, 1.0f, 1.0f},   //
    };

    vertex_buffer_id_ = renderer->createVertexBuffer(def, vertices, sizeof(vertices));
    if (!isValid(vertex_buffer_id_)) {
      return false;
    }

    static U16 indices[] = {
        0,  2,  1,  //
        1,  2,  3,  //
        4,  5,  6,  //
        5,  7,  6,  //

        8,  10, 9,   //
        9,  10, 11,  //
        12, 13, 14,  //
        13, 15, 14,  //

        16, 18, 17,  //
        17, 18, 19,  //
        20, 21, 22,  //
        21, 23, 22,  //
    };

    index_buffer_id_ =
        renderer->createIndexBuffer(ca::ComponentType::Unsigned16, indices, sizeof(indices));

    if (!isValid(index_buffer_id_)) {
      return false;
    }

    return true;
  }

  bool load_texture(ca::Renderer* renderer) {
    auto image_path = root_path_ / "default.png";
    nu::FileInputStream image_stream{image_path};
    if (!image_stream.openedOk()) {
      return false;
    }

    texture_id_ = renderer->createTexture(ca::TextureFormat::Alpha, fl::Size{256, 128},
                                          ca::monoFont, ca::monoFontSize);

    return isValid(texture_id_);
  }

  nu::FilePath root_path_;

  ca::ProgramId program_id_;
  ca::VertexBufferId vertex_buffer_id_;
  ca::IndexBufferId index_buffer_id_;
  ca::TextureId texture_id_;
  ca::UniformId scale_uniform_;
  ca::UniformBuffer uniforms_;
};

CANVAS_APP(Minimal)

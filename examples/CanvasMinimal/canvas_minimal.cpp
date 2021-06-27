
#include "canvas/App.h"
#include "canvas/StaticData/All.h"
#include "canvas/Utils/ShaderSource.h"
#include "nucleus/Streams/file_input_stream.h"
#include "nucleus/file_path.h"

class Minimal : public ca::WindowDelegate {
public:
  NU_DELETE_COPY_AND_MOVE(Minimal);

  Minimal()
    : ca::WindowDelegate("Canvas Minimal Example"), m_rootPath(nu::getExecutablePath().dirName()) {}

  ~Minimal() override = default;

  // Override: ca::WindowDelegate
  bool onWindowCreated(ca::Window* window) override {
    LOG(Info) << "Root path: " << m_rootPath.getPath();

    ca::Renderer* renderer = window->getRenderer();

    if (!loadProgram(renderer)) {
      LOG(Error) << "Could not create program";
      return false;
    }

    if (!loadVertexBuffer(renderer)) {
      LOG(Error) << "Could not create vertex buffer and index buffer.";
      return false;
    }

    if (!loadTexture(renderer)) {
      LOG(Error) << "Could not create texture.";
      return false;
    }

    m_scaleUniform = renderer->createUniform("uScale");
    m_uniforms.set(m_scaleUniform, 0.5f);

    return true;
  }

  void onRender(ca::Renderer* renderer) override {
    PROFILE("Minimal Frame")

    {
      PROFILE("clear")
      renderer->clear(ca::Color{0.0f, 0.1f, 0.2f});
    }

    {
      PROFILE("draw")
      renderer->draw(ca::DrawType::Triangles, 6, m_programId, m_vertexBufferId, m_indexBufferId,
                     m_textureId, m_uniforms);
    }
  }

private:
  bool loadProgram(ca::Renderer* renderer) {
    nu::FileInputStream vs{m_rootPath / "default.vs"};
    if (!vs.openedOk()) {
      return false;
    }

    nu::FileInputStream fs{m_rootPath / "default.fs"};
    if (!fs.openedOk()) {
      return false;
    }

    m_programId = renderer->createProgram(ca::ShaderSource::from(&vs), ca::ShaderSource::from(&fs));

    return isValid(m_programId);
  }

  bool loadVertexBuffer(ca::Renderer* renderer) {
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

    m_vertexBufferId = renderer->createVertexBuffer(def, vertices, sizeof(vertices));
    if (!isValid(m_vertexBufferId)) {
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

    m_indexBufferId =
        renderer->createIndexBuffer(ca::ComponentType::Unsigned16, indices, sizeof(indices));

    if (!isValid(m_indexBufferId)) {
      return false;
    }

    return true;
  }

  bool loadTexture(ca::Renderer* renderer) {
    auto imagePath = m_rootPath / "default.png";
    nu::FileInputStream imageStream{imagePath};
    if (!imageStream.openedOk()) {
      return false;
    }

    m_textureId = renderer->createTexture(ca::TextureFormat::Alpha, fl::Size{256, 128},
                                          ca::monoFont, ca::monoFontSize);

    return isValid(m_textureId);
  }

  nu::FilePath m_rootPath;

  ca::ProgramId m_programId;
  ca::VertexBufferId m_vertexBufferId;
  ca::IndexBufferId m_indexBufferId;
  ca::TextureId m_textureId;
  ca::UniformId m_scaleUniform;
  ca::UniformBuffer m_uniforms;
};

CANVAS_APP(Minimal)


#include "canvas/App.h"

#include "canvas/Renderer/BufferDefinition.h"
#include "canvas/Utils/Image.h"
#include "canvas/Utils/ShaderSource.h"
#include "nucleus/FilePath.h"
#include "nucleus/Optional.h"
#include "nucleus/Streams/FileInputStream.h"

class MinimalWindow : public ca::WindowDelegate {
public:
  MinimalWindow() : ca::WindowDelegate("Minimal"), m_rootPath(nu::getCurrentWorkingDirectory()) {}
  ~MinimalWindow() override = default;

  // Override: ca::WindowDelegate
  bool onWindowCreated(ca::Renderer* renderer) override {
    LOG(Info) << "Root path: " << m_rootPath;
    return loadProgram(renderer) && loadGeometry(renderer) && loadTexture(renderer);
  }

  void onRender(ca::Renderer* renderer) override {
    auto renderGroup = renderer->addRenderGroup(ca::RenderGroupProjection::Perspective);
    renderGroup->clearColorBuffer(ca::color(0.125f, 0.25f, 0.33f, 1.0f));
    renderGroup->renderGeometry(m_geometryId, m_textureId, m_programId);
  }

private:
  DISALLOW_COPY_AND_ASSIGN(MinimalWindow);

  bool loadProgram(ca::Renderer* renderer) {
    nu::FileInputStream* vs = new nu::FileInputStream{m_rootPath / "default.vs"};
    if (!vs->openedOk()) {
      return false;
    }

    auto vertexShader = ca::ShaderSource::from(vs);

    nu::FileInputStream* fs = new nu::FileInputStream{m_rootPath / "default.fs"};
    if (!fs->openedOk()) {
      return false;
    }

    auto fragmentShader = ca::ShaderSource::from(fs);

    m_programId = renderer->createProgram(vertexShader, fragmentShader);

    return true;
  }

  bool loadGeometry(ca::Renderer* renderer) {
    ca::BufferDefinition def{5};
    def.addAttribute(3, ca::ComponentType::Float32);
    def.addAttribute(2, ca::ComponentType::Float32);

    static F32 vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  //
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  //
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  //
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  //
    };

    m_geometryId = renderer->createGeometry(def, vertices, sizeof(vertices));

    return true;
  }

  bool loadTexture(ca::Renderer* renderer) {
    auto imagePath = m_rootPath / "default.png";
    nu::FileInputStream imageStream{imagePath};
    if (!imageStream.openedOk()) {
      LOG(Error) << "Could not load image: " << imagePath;
      return false;
    }

    ca::Image image;
    if (!image.loadFromStream(&imageStream)) {
      return false;
    }

    m_textureId = renderer->createTexture(image);

    return true;
  }

  nu::FilePath m_rootPath;

  ca::ProgramId m_programId = 0;
  ca::GeometryId m_geometryId = 0;
  ca::TextureId m_textureId = 0;
};

CANVAS_APP(MinimalWindow)

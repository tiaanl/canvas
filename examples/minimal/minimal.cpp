
#include "canvas/App.h"

#include "canvas/Renderer/RenderContext.h"
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
  bool onWindowCreated(ca::RenderContext* renderContext) override {
    LOG(Info) << "Root path: " << m_rootPath;
    return loadProgram(renderContext) && loadGeometry(renderContext) && loadTexture(renderContext);
  }

  void onRender(ca::Renderer* renderer) override {
    auto renderGroup = renderer->addRenderGroup(ca::RenderGroupProjection::Perspective);
    renderGroup->clearColorBuffer(ca::color(0.125f, 0.25f, 0.33f, 1.0f));
    renderGroup->renderGeometry(m_geometryId, m_textureId, m_programId);
  }

private:
  DISALLOW_COPY_AND_ASSIGN(MinimalWindow);

  bool loadProgram(ca::RenderContext* renderContext) {
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

    m_programId = renderContext->createProgram(vertexShader, fragmentShader);

    return true;
  }

  bool loadGeometry(ca::RenderContext* renderContext) {
    ca::GeometryDefinition def;
    def.addAttribute(3, ca::ComponentType::Float32, 0, 0);

    static F32 vertices[] = {
        0.0f,  0.5f,  0.0f,  //
        0.5f,  -0.5f, 0.0f,  //
        -0.5f, -0.5f, 0.0f,  //
    };

    m_geometryId = renderContext->createGeometry(def, vertices, ARRAY_SIZE(vertices));

    return true;
  }

  bool loadTexture(ca::RenderContext* renderContext) {
    nu::FileInputStream imageStream{m_rootPath / "default.png"};
    if (!imageStream.openedOk()) {
      return false;
    }

    ca::Image image;
    if (!image.loadFromStream(&imageStream)) {
      return false;
    }

    m_textureId = renderContext->createTexture(image);

    return true;
  }

  nu::FilePath m_rootPath;

  ca::ProgramId m_programId = 0;
  ca::GeometryId m_geometryId = 0;
  ca::TextureId m_textureId = 0;
};

CANVAS_APP(MinimalWindow)

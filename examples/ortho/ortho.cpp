
#include "canvas/app.h"
#include "canvas/math/transform.h"
#include "canvas/rendering/canvas.h"
#include "canvas/rendering/geometry.h"
#include "canvas/rendering/program.h"
#include "canvas/rendering/shader.h"
#include "nucleus/streams/wrapped_memory_input_stream.h"

#include <cstring>

const char kVertexShader[] =
    "#version 410\n"
    "\n"
    "layout(location=0) in vec3 vert_position;\n"
    "\n"
    "uniform mat4 uni_projectionMatrix;\n"
    "uniform mat4 uni_viewMatrix;\n"
    "uniform mat4 uni_modelMatrix;\n"
    "\n"
    "void main() {\n"
    "  gl_Position = uni_projectionMatrix * uni_viewMatrix * uni_modelMatrix * vec4(vert_position, 1.0);\n"
    "}\n";

const char kFragmentShader[] =
    "#version 410\n"
    "\n"
    "in vec3 vert_position;\n"
    "\n"
    "out vec4 frag_color;\n"
    "\n"
    "void main() {\n"
    "  frag_color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

class OrthoWindow : public ca::WindowDelegate {
public:
  OrthoWindow() {}
  ~OrthoWindow() override {}

  bool onWindowCreated() override {
    nu::WrappedMemoryInputStream vertexStream(kVertexShader, std::strlen(kVertexShader));
    ca::Shader vertexShader(ca::Shader::Vertex);
    vertexShader.loadFromStream(&vertexStream);

    nu::WrappedMemoryInputStream fragmentStream(kFragmentShader, std::strlen(kFragmentShader));
    ca::Shader fragmentShader(ca::Shader::Fragment);
    fragmentShader.loadFromStream(&fragmentStream);

    m_program.setVertexShader(&vertexShader);
    m_program.setFragmentShader(&fragmentShader);
    m_program.link();

    m_object = ca::Geometry::createRectangle(ca::Rect<F32>{-50.0f, -50.0f, 100.0f, 100.0f}, ca::Color{255, 0, 0, 255});
    m_object.compileAndUpload();

    m_mouse = ca::Geometry::createRectangle(ca::Rect<F32>{-5.0f, -5.0f, 10.0f, 10.0f}, ca::Color{255, 0, 0, 255});
    m_mouse.compileAndUpload();

    return true;
  }

  void onWindowResized(const ca::Size<U32>& clientSize) override { m_clientSize = clientSize; }

  void onMouseMoved(const ca::MouseEvent& event) override { m_mousePos = event.pos; }

  // Override: ca::WindowDelegate
  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color{31, 63, 95});

    ca::Program::bind(&m_program);

    ca::Mat4 projectionMatrix =
        ca::ortho(-static_cast<F32>(m_clientSize.width) / 2.0f, static_cast<F32>(m_clientSize.width) / 2.0f,
                  -static_cast<F32>(m_clientSize.height) / 2.0f, static_cast<F32>(m_clientSize.height) / 2.0f);
    m_program.setUniform("uni_projectionMatrix", projectionMatrix);

    ca::Mat4 viewMatrix = ca::translate(150.0f, 0.0f, 0.0f);
    m_program.setUniform("uni_viewMatrix", viewMatrix);

    ca::Mat4 modelMatrix = ca::translate(0.0f, 0.0f, 0.0f);
    m_program.setUniform("uni_modelMatrix", modelMatrix);

    ca::Mat4 finalMatrix = projectionMatrix * viewMatrix * modelMatrix;

    // m_mousePos = ca::Pos<I32>{50, 250};
    ca::Vec4 adjustedMousePos{-1.f + 2.f * static_cast<F32>(m_mousePos.x) / static_cast<F32>(m_clientSize.width),
                              -1.f + 2.f * static_cast<F32>(m_mousePos.y) / static_cast<F32>(m_clientSize.height), 0.0f,
                              1.0f};

    ca::Mat4 inv = ca::inverse(finalMatrix);
    ca::Vec4 mousePosInWorld = inv * adjustedMousePos;

    m_object.render(canvas);

    ca::Mat4 mouseModelMatrix = ca::translate(mousePosInWorld.x, -mousePosInWorld.y, 0.0f);
    m_program.setUniform("uni_viewMatrix", mouseModelMatrix);

    m_mouse.render(canvas);

    ca::Program::bind(nullptr);
  }

private:
  ca::Size<U32> m_clientSize{500, 500};
  ca::Pos<I32> m_mousePos;
  ca::Program m_program;

  ca::Geometry m_object;
  ca::Geometry m_mouse;

  DISALLOW_COPY_AND_ASSIGN(OrthoWindow);
};

CANVAS_APP(OrthoWindow);

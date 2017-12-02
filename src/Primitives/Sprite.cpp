
#include "canvas/Primitives/Sprite.h"

#include <cstring>

#include "canvas/rendering/shader.h"
#include "canvas/utils/ScopedOpenGLEnable.h"
#include "nucleus/streams/wrapped_memory_input_stream.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

namespace {

const char* kVertexShader =
    "#version 420\n"
    "\n"
    "layout(location = 0) in vec3 vert_position;\n"
    "layout(location = 1) in vec2 vert_texCoord;\n"
    "layout(location = 2) in vec4 vert_color;\n"
    "\n"
    "uniform mat4 uni_mvp;\n"
    "\n"
    "out vec2 frag_texCoord;\n"
    "\n"
    "void main() {\n"
    "  gl_Position = uni_mvp * vec4(vert_position, 1.0);\n"
    "  frag_texCoord = vert_texCoord;\n"
    "}\n";

const char* kFragmentShader =
    "#version 420\n"
    "\n"
    "in vec2 frag_texCoord;\n"
    "\n"
    "uniform sampler2D uni_sampler;\n"
    "\n"
    "out vec4 finalColor;\n"
    "\n"
    "void main() {\n"
    "  finalColor = texture(uni_sampler, frag_texCoord);\n"
    "}\n";

}  // namespace

// static
Program* Sprite::s_shaderProgram = nullptr;

Sprite::Sprite(Texture* texture) : m_texture{texture} {
  // If we have a texture, rebuild the geometry.
  if (texture) {
    updateGeometry();
  }
}

Sprite::~Sprite() {}

ca::Rect<F32> Sprite::getBounds() const {
  if (!m_texture) {
    return Rect<F32>{};
  }

  Size<I32> textureSize = m_texture->getSize();
  const F32 width = static_cast<F32>(textureSize.width) / 2.f;
  const F32 height = static_cast<F32>(textureSize.width) / 2.f;
  return Rect<F32>{-width, -height, width * 2.f, height * 2.f};
}

void Sprite::setTexture(Texture* texture) {
  m_texture = texture;
  updateGeometry();
}

void Sprite::render(Canvas* canvas, const Mat4& transform) const {
  if (!m_texture) {
    return;
  }

  // Make sure the shader program is created and bind it.
  ensureShaderProgram();
  Program::bind(s_shaderProgram);
  DCHECK(s_shaderProgram->setUniform("uni_mvp", transform));

  Texture::bind(m_texture);

  // Enable blending.
  ScopedOpenGLEnable enableBlending{GL_BLEND};
  GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GL_CHECK(glBlendEquation(GL_FUNC_ADD));

  m_geometry.render(canvas);
}

void Sprite::updateGeometry() {
  if (!m_texture) {
    return;
  }

  ensureShaderProgram();

  // Clear out the old geometry.
  m_geometry.clear();

  const auto size = m_texture->getSize();
  Rect<F32> rect{-static_cast<float>(size.width) / 2.f, -static_cast<float>(size.height) / 2.f,
                 static_cast<float>(size.width), static_cast<float>(size.height)};

  m_geometry = Geometry::createRectangle(rect, Color{255, 255, 255, 255});

  m_geometry.compileAndUpload();
}

// static
void Sprite::ensureShaderProgram() {
  if (!s_shaderProgram) {
    nu::WrappedMemoryInputStream vertexStream{kVertexShader, std::strlen(kVertexShader)};
    Shader vertexShader{Shader::Vertex};
    vertexShader.loadFromStream(&vertexStream);

    nu::WrappedMemoryInputStream fragmentStream{kFragmentShader, std::strlen(kFragmentShader)};
    Shader fragmentShader{Shader::Fragment};
    fragmentShader.loadFromStream(&fragmentStream);

    s_shaderProgram = new Program{&vertexShader, &fragmentShader};
    s_shaderProgram->link();
  }
}

}  // namespace ca

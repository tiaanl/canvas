
#include "canvas/Primitives/Sprite.h"

#include <cstring>

#include "canvas/Rendering/Shader.h"
#include "canvas/Resources/ResourceManager.h"
#include "canvas/Utils/ScopedOpenGLEnable.h"
#include "nucleus/Streams/WrappedMemoryInputStream.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

namespace {

const char* kVertexShader =
    "#version 330\n"
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
    "#version 330\n"
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

Sprite::Sprite(ResourceManager* resourceManager, const ResourceRef<Texture>& texture)
  : m_resourceManager(resourceManager), m_texture{texture} {
  DCHECK(m_resourceManager) << "Can't create sprites without a resource manager";

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

void Sprite::setTexture(const ResourceRef<Texture>& texture) {
  m_texture = texture;
  updateGeometry();
}

void Sprite::render(Canvas* canvas, const Mat4& transform) const {
  if (!m_texture) {
    return;
  }

#if 0
  // Make sure the shader program is created and bind it.
  ensureShaderProgram();
  Program::bind(&s_shaderProgram);
  DCHECK(s_shaderProgram.setUniform("uni_mvp", transform));

  Texture::bind(m_texture);

  // Enable blending.
  ScopedOpenGLEnable enableBlending{GL_BLEND};
  GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GL_CHECK(glBlendEquation(GL_FUNC_ADD));

  m_geometry.render(canvas);
#endif  // 0
}

bool Sprite::ensureShaderProgram() {
  if (m_shaderProgram && m_shaderProgram->isLoaded()) {
    return true;
  }

  nu::WrappedMemoryInputStream vertexStream{kVertexShader, std::strlen(kVertexShader) + 1};
  ResourceRef<Shader> vertexShader = m_resourceManager->getOrCreateShader("_canvas_sprite_vertex");
  if (!vertexShader->isLoaded() || !vertexShader->loadFromStream(Shader::Vertex, &vertexStream)) {
    return false;
  }

  nu::WrappedMemoryInputStream fragmentStream{kFragmentShader, std::strlen(kFragmentShader) + 1};
  ResourceRef<Shader> fragmentShader = m_resourceManager->getOrCreateShader("_canvas_sprite_fragment");
  if (!fragmentShader->isLoaded() || !fragmentShader->loadFromStream(Shader::Fragment, &fragmentStream)) {
    return false;
  }

  m_shaderProgram = m_resourceManager->getOrCreateProgram("_canvas_sprite_program");
  if (!m_shaderProgram->isLoaded()) {
    m_shaderProgram->setVertexShader(vertexShader);
    m_shaderProgram->setFragmentShader(fragmentShader);
    if (!m_shaderProgram->link()) {
      return false;
    }
  }

  return true;
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

}  // namespace ca

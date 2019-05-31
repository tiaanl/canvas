
#include "canvas/Primitives/Text.h"

#include <algorithm>
#include <cstring>

#include "canvas/Rendering/Font.h"
#include "canvas/Rendering/Program.h"
#include "canvas/Rendering/Shader.h"
#include "canvas/Resources/ResourceManager.h"
#include "nucleus/Streams/WrappedMemoryInputStream.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

namespace {

// The shaders used by text rendering.

const char* kTextVertexShader =
    "#version 410\n"
    "\n"
    "layout(location = 0) in vec3 vert_position;\n"
    "layout(location = 1) in vec2 vert_texCoord;\n"
    "layout(location = 2) in vec4 vert_color;\n"
    "\n"
    "uniform mat4 uni_mvp;\n"
    "\n"
    "out vec2 frag_texCoord;\n"
    "out vec4 frag_color;\n"
    "\n"
    "void main() {\n"
    "  gl_Position = uni_mvp * vec4(vert_position, 1.0);\n"
    "  frag_texCoord = vert_texCoord;\n"
    "  frag_color = vert_color;\n"
    "}\n";

const char* kTextFragmentShader =
    "#version 410\n"
    "\n"
    "in vec2 frag_texCoord;\n"
    "in vec4 frag_color;\n"
    "\n"
    "uniform sampler2D sampler;\n"
    "\n"
    "out vec4 final;\n"
    "\n"
    "void main() {\n"
    "  final = texture(sampler, frag_texCoord);\n"
    "}\n";

}  // namespace

Text::Text(ResourceManager* resourceManager, nu::String text, nu::String fontName, I32 textSize)
  : m_resourceManager(resourceManager), m_font(resourceManager->getOrCreateFont(fontName)),
    m_text(text), m_textSize(textSize) {
  ensureShaders();

  if (m_font) {
    updateGeometry();
  }
}

void Text::setFont(const ResourceRef<Font>& font) {
  m_font = font;
  updateGeometry();
}

void Text::setText(const nu::String& text) {
  m_text = text;
  updateGeometry();
}

void Text::setTextSize(I32 textSize) {
  m_textSize = textSize;
  updateGeometry();
}

void Text::render(Canvas* canvas, const Mat4& transform) const {
  if (!m_font) {
    return;
  }

  const ca::Texture* texture = m_font->getTexture(m_textSize);
  if (!texture) {
    return;
  }

  // Bind the font's texture.
  Texture::bind(texture);

  // Bind the program.
  Program::bind(m_program);
  m_program->setUniform("uni_mvp", transform);

  // Enable blending.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBlendEquation(GL_FUNC_ADD);

  // Render the text geometry.
  m_geometry.render(canvas);

  // Disable blending when we're done.
  glDisable(GL_BLEND);
}

void Text::ensureShaders() {
  if (m_program && m_program->isLoaded()) {
    return;
  }

  // Create the program by adding the two shaders.
  m_program = m_resourceManager->getOrCreateProgram("elastic-text-program");
  if (!m_program->isLoaded()) {
    // Create the vertex shader.
    ResourceRef<Shader> vertexShader = m_resourceManager->getOrCreateShader("elastic-text-vertex");
    if (!vertexShader->isLoaded()) {
      nu::WrappedMemoryInputStream vertexStream{kTextVertexShader, std::strlen(kTextVertexShader)};
      if (!vertexShader->loadFromStream(Shader::Vertex, &vertexStream)) {
        return;
      }
      vertexShader->setLoaded(true);
    }

    // Create the fragment shader.
    ResourceRef<Shader> fragmentShader =
        m_resourceManager->getOrCreateShader("elastic-text-fragment");
    if (!fragmentShader->isLoaded()) {
      nu::WrappedMemoryInputStream fragmentStream{kTextFragmentShader,
                                                  std::strlen(kTextFragmentShader)};
      if (!fragmentShader->loadFromStream(Shader::Fragment, &fragmentStream)) {
        return;
      }
      fragmentShader->setLoaded(true);
    }

    m_program->setVertexShader(vertexShader);
    m_program->setFragmentShader(fragmentShader);
    m_program->link();
  }
}

void Text::updateGeometry() {
  if (!m_font->isLoaded()) {
    return;
  }

  // Clear out the old geometry.
  m_geometry.clear();

  // If there is no text to render, then that's it.
  if (m_text.isEmpty()) {
    m_geometry.compileAndUpload();

    // Update the bounds.
    m_bounds = Rect<I32>{};

    return;
  }

  Pos<F32> currentPos{0.f, 0.f};
  Color white{255, 255, 255, 255};

  // Reset the position of the bounds.
  m_bounds = ca::Rect<I32>{};

  // Build geometry for each character in the text.
  for (MemSize i = 0; i < m_text.getLength(); ++i) {
    ca::Font::Char ch = static_cast<ca::Font::Char>(m_text[i]);

    // Get the glyph.
    const Font::Glyph& glyph = m_font->getOrInsertGlyph(ch, m_textSize, false);

    F32 left = static_cast<F32>(glyph.bounds.pos.x);
    F32 top = static_cast<F32>(glyph.bounds.pos.y);
    F32 right = static_cast<F32>(glyph.bounds.pos.x + glyph.bounds.size.width);
    F32 bottom = static_cast<F32>(glyph.bounds.pos.y + glyph.bounds.size.height);

    F32 u1 = glyph.textureRect.pos.x;
    F32 v1 = glyph.textureRect.pos.y;
    F32 u2 = glyph.textureRect.pos.x + glyph.textureRect.size.width;
    F32 v2 = glyph.textureRect.pos.y + glyph.textureRect.size.height;

    Vec3 topLeft{currentPos.x + left, currentPos.y + top, 0.f};
    Vec3 topRight{currentPos.x + right, currentPos.y + top, 0.f};
    Vec3 bottomLeft{currentPos.x + left, currentPos.y + bottom, 0.f};
    Vec3 bottomRight{currentPos.x + right, currentPos.y + bottom, 0.f};

    m_geometry.addVertex(Vertex{topLeft, Vec2{u1, v1}, white});
    m_geometry.addVertex(Vertex{topRight, Vec2{u2, v1}, white});
    m_geometry.addVertex(Vertex{bottomLeft, Vec2{u1, v2}, white});
    m_geometry.addVertex(Vertex{bottomLeft, Vec2{u1, v2}, white});
    m_geometry.addVertex(Vertex{topRight, Vec2{u2, v1}, white});
    m_geometry.addVertex(Vertex{bottomRight, Vec2{u2, v2}, white});

    currentPos.x += glyph.advance;

    // Increase the bounds.
    m_bounds.size.width += static_cast<I32>(std::ceil(glyph.advance));
    m_bounds.size.height = std::max(m_bounds.size.height, static_cast<I32>(std::ceil(bottom)));
  }

  m_geometry.compileAndUpload();
}

}  // namespace ca

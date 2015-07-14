// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "canvas/rendering/text.h"

#include <algorithm>

#include "canvas/rendering/font.h"
#include "canvas/rendering/program.h"
#include "canvas/rendering/shader.h"
#include "nucleus/streams/wrapped_memory_input_stream.h"

namespace ca {

namespace {

// The shaders used by text rendering.

const char* kTextVertexShader =
    "#version 420\n"
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
    "#version 420\n"
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

// TODO(tiaanl): These are allocated, but never released.
static Shader* gs_textVertexShader;
static Shader* gs_textFragmentShader;
static Program* gs_textProgram;

}  // namespace

Text::Text() {
  ensureShaders();
}

Text::Text(Font* font, i32 textSize, const std::string& text)
  : m_font(font), m_text(text), m_textSize(textSize) {
  ensureShaders();

  if (m_font) {
    updateGeometry();
  }
}

void Text::setFont(Font* font) {
  m_font = font;
  updateGeometry();
}

void Text::setText(const std::string& text) {
  m_text = text;
  updateGeometry();
}

void Text::setTextSize(i32 textSize) {
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
  Program::bind(gs_textProgram);
  gs_textProgram->setUniform("uni_mvp", transform);

  // Enable blending.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBlendEquation(GL_FUNC_ADD);

  // Render the text geometry.
  m_geometry.render();

  // Disable blending when we're done.
  glDisable(GL_BLEND);
}

void Text::ensureShaders() {
  if (gs_textVertexShader && gs_textFragmentShader && gs_textProgram) {
    return;
  }

  nu::WrappedMemoryInputStream vertexStream{kTextVertexShader,
                                            std::strlen(kTextVertexShader)};
  gs_textVertexShader = new Shader{Shader::Vertex};
  gs_textVertexShader->loadFromStream(&vertexStream);

  nu::WrappedMemoryInputStream fragmentStream{kTextFragmentShader,
                                              std::strlen(kTextFragmentShader)};
  gs_textFragmentShader = new Shader{Shader::Fragment};
  gs_textFragmentShader->loadFromStream(&fragmentStream);

  gs_textProgram = new Program{gs_textVertexShader, gs_textFragmentShader};
  gs_textProgram->link();
}

void Text::updateGeometry() {
  if (!m_font) {
    return;
  }

  // Clear out the old geometry.
  m_geometry.clear();

  // If there is not text to render, then that's it.
  if (m_text.empty()) {
    m_geometry.compileAndUpload();

    // Update the bounds.
    m_bounds = Rect<i32>{};
    m_bounds.size.height = static_cast<i32>(std::round(
        m_font->getAscent(m_textSize) - m_font->getDescent(m_textSize)));
    return;
  }

  f32 left = 0.f;

  float bLeft = 0.f, bTop = 0.f, bRight = 0.f, bBottom = 0.f;

  // Build geometry for each character in the text.
  for (usize i = 0; i < m_text.length(); ++i) {
    char32_t ch = m_text[i];

    // Get the glyph.
    const Font::Glyph& glyph = m_font->getOrInsertGlyph(m_textSize, ch);

    const f32 newLeft = left + glyph.bounds.pos.x;
    const f32 newTop = glyph.bounds.pos.y;
    const f32 newRight = left + glyph.bounds.pos.x + glyph.bounds.size.width;
    const f32 newBottom = glyph.bounds.pos.y + glyph.bounds.size.height;

    bLeft = std::min(bLeft, newLeft);
    bTop = std::min(bTop, newTop);
    bRight = std::max(bRight, newRight);
    bBottom = std::max(bBottom, newBottom);

    // Add vertices for one block.
    // clang-format off

    // 0
    m_geometry.addVertex(
      Vertex{
        Vec3{newLeft, newTop, 0.f},
        Vec2{glyph.textureRect.pos.x, glyph.textureRect.pos.y},
        // Vec2{0.f, 0.f},
        Color{255, 255, 255, 255}
      }
    );
    // 1
    m_geometry.addVertex(
      Vertex{
        Vec3{newRight, newTop, 0.f},
        Vec2{glyph.textureRect.pos.x + glyph.textureRect.size.width, glyph.textureRect.pos.y},
        // Vec2{1.f, 0.f},
        Color{255, 255, 255, 255}
      }
    );
    // 2
    m_geometry.addVertex(
      Vertex{
        Vec3{newRight, newBottom, 0.f},
        Vec2{glyph.textureRect.pos.x + glyph.textureRect.size.width, glyph.textureRect.pos.y + glyph.textureRect.size.height},
        // Vec2{1.f, 1.f},
        Color{255, 255, 255, 255}
      }
    );

    // 0
    m_geometry.addVertex(
      Vertex{
        Vec3{newLeft, newTop, 0.f},
        Vec2{glyph.textureRect.pos.x, glyph.textureRect.pos.y},
        // Vec2{0.f, 0.f},
        Color{255, 255, 255, 255}
      }
    );
    // 2
    m_geometry.addVertex(
      Vertex{
        Vec3{newRight, newBottom, 0.f},
        Vec2{glyph.textureRect.pos.x + glyph.textureRect.size.width, glyph.textureRect.pos.y + glyph.textureRect.size.height},
        // Vec2{1.f, 1.f},
        Color{255, 255, 255, 255}
      }
    );
    // 3
    m_geometry.addVertex(
      Vertex{
        Vec3{newLeft, newBottom, 0.f},
        Vec2{glyph.textureRect.pos.x, glyph.textureRect.pos.y + glyph.textureRect.size.height},
        // Vec2{0.f, 1.f},
        Color{255, 255, 255, 255}
      }
    );
    // clang-format on

    left += glyph.advance;
  }

  m_bounds.pos.x = static_cast<i32>(std::floor(bLeft));
  m_bounds.pos.y = static_cast<i32>(std::floor(bTop));
  m_bounds.size.width = static_cast<i32>(std::ceil(bRight - bLeft));
  m_bounds.size.height = static_cast<i32>(std::ceil(bBottom - bTop));

  m_geometry.compileAndUpload();
}

}  // namespace ca

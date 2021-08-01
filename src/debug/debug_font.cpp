#include "canvas/debug/debug_font.h"

#include "canvas/renderer/renderer.h"
#include "canvas/static_data/all.h"
#include "floats/transform.h"

namespace ca {

namespace {

constexpr F32 kTextureWidth = 256.0f;
constexpr F32 kTextureHeight = 128.0f;

constexpr F32 kGlyphWidth = 8.0f;
constexpr F32 kGlyphHeight = 16.0f;

constexpr I32 kHorizontalGlyphCount = 32;
constexpr I32 kVerticalGlyphCount = 8;

struct Vertex {
  F32 x;
  F32 y;
  F32 u;
  F32 v;
};

auto kVertexShaderSource = R"source(
#version 330

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inTexCoord;

uniform mat4 uTransform;

out vec2 vTexCoord;

void main() {
  gl_Position = uTransform * vec4(inPosition, 0.0f, 1.0f);
  vTexCoord = inTexCoord;
}
)source";

auto kFragmentShaderSource = R"source(
#version 330

in vec2 vTexCoord;

uniform sampler2D uTexture;

out vec4 final;

void main() {
  vec4 pixel = texture(uTexture, vTexCoord);
  final = vec4(1.0f, 1.0f, 1.0f, pixel.r);
}
)source";

}  // namespace

DebugFont::DebugFont(Renderer* renderer) : m_renderer{renderer} {}

bool DebugFont::initialize() {
  // Create the geometry for the characters.

  VertexDefinition def;
  def.addAttribute(ComponentType::Float32, ComponentCount::Two);
  def.addAttribute(ComponentType::Float32, ComponentCount::Two);

  // Build a vertex buffer that has geometry for each glyph.
  Vertex vertices[kHorizontalGlyphCount * kVerticalGlyphCount * 4];
  MemSize glyphIndex = 0;
  for (I32 y = 0; y < kVerticalGlyphCount; ++y) {
    for (I32 x = 0; x < kHorizontalGlyphCount; ++x) {
      const F32 uvLeft = static_cast<F32>(x) * kGlyphWidth / kTextureWidth;
      const F32 uvRight = static_cast<F32>(x + 1) * kGlyphWidth / kTextureWidth;
      const F32 uvTop = static_cast<F32>(y) * kGlyphHeight / kTextureHeight;
      const F32 uvBottom = static_cast<F32>(y + 1) * kGlyphHeight / kTextureHeight;

      vertices[glyphIndex + 0] = {0.0f, 0.0f, uvLeft, uvTop};
      vertices[glyphIndex + 1] = {kGlyphWidth, 0.0f, uvRight, uvTop};
      vertices[glyphIndex + 2] = {kGlyphWidth, kGlyphHeight, uvRight, uvBottom};
      vertices[glyphIndex + 3] = {0.0f, kGlyphHeight, uvLeft, uvBottom};

      glyphIndex += 4;
    }
  }

  m_vertexBufferId = m_renderer->create_vertex_buffer(def, vertices, sizeof(vertices));

  // Create the texture.

  m_textureId =
      m_renderer->create_texture(TextureFormat::Alpha, {256, 128}, monoFont, monoFontSize, false);

  // Create the program.

  m_programId = m_renderer->create_program(ShaderSource::from(kVertexShaderSource),
                                           ShaderSource::from(kFragmentShaderSource));

  // Create and set up some uniforms.

  m_transformUniformId = m_renderer->create_uniform("uTransform");

  return true;
}

void DebugFont::drawText(const fl::Mat4& transform, const fl::Pos& position, nu::StringView text) {
  for (auto index = 0U; index < text.length(); ++index) {
    fl::Vec2 offset{
        static_cast<F32>(position.x) + static_cast<F32>(index) * (kGlyphWidth),
        static_cast<F32>(position.y),
    };

    auto moved = transform * translation_matrix(fl::Vec3{offset, 0.0f});

    UniformBuffer uniforms;
    uniforms.set(m_transformUniformId, moved);

    auto glyphIndex = text[index] - ' ';
    if (glyphIndex == 0) {
      // Skip spaces.
      continue;
    }
    m_renderer->draw(DrawType::TriangleFan, glyphIndex * 4, 4, m_programId, m_vertexBufferId,
                     m_textureId, uniforms);
  }
}

}  // namespace ca

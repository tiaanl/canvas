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

#ifndef CANVAS_RENDERING_FONT_H_
#define CANVAS_RENDERING_FONT_H_

#include <memory>
#include <unordered_map>

#include "nucleus/macros.h"
#include "nucleus/types.h"

#include "canvas/utils/rect.h"
#include "canvas/rendering/texture.h"
#include "stb_truetype.h"

namespace ca {

class Font {
public:
  struct Glyph {
    f32 advance{0.f};
    Rect<f32> bounds;
    Rect<i32> textureRect;
  };

  explicit Font(i32 characterSize = 32);
  ~Font();

  // Load a font from the given stream.
  bool loadFromStream(nu::InputStream* stream);

  // Get the glyph data corresponding to the given code point.
  const Glyph& getOrInsertGlyph(char32_t codePoint);

  // Get the amount of kerning between the first and second characters.
  i32 getKerning(char32_t first, char32_t second) const;

  // Get the line spacing for the font.
  f32 getLineSpacing() const;

  // Get the texture that is backing this font.
  const Texture* getTexture() const { return &m_texture; }

private:
  // A row of glyphs.
  struct Row {
    i32 width = 0;
    i32 top = 0;
    i32 height = 0;

    Row(i32 width, i32 top, i32 height)
      : width{width}, top{top}, height{height} {}
  };

  using GlyphTable = std::unordered_map<u32, Glyph>;

  // Load a new glyph and store it in the cache.
  Glyph loadGlyph(char32_t codePoint);

  // Find a suitable rectangle within the texture for a glyph.
  Rect<i32> findGlyphRect(const Size<i32>& size);

  // The size of the characters we render with this font.
  i32 m_characterSize;

  // Internal font info data.
  stbtt_fontinfo m_fontInfo;

  // The data buffer holding the font data.  We have to keep this alive for the
  // lifetime of the font.
  std::vector<u8> m_fontData;

  // All the glyphs we hold.
  GlyphTable m_glyphs;

  // The texture we use to back this font.
  Texture m_texture;

  // Starting point for the next row on the page.
  i32 m_nextRow;

  // All the rows we have.
  std::vector<Row> m_rows;

  // A temporary pixel buffer that holds the pixel data before it's uploaded to
  // the GPU.
  std::vector<u8> m_pixelBuffer;

  DISALLOW_COPY_AND_ASSIGN(Font);
};

void fontTest();

}  // namespace ca

#endif  // CANVAS_RENDERING_FONT_H_

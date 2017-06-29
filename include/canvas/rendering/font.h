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
  // The type we use for character codepoints.
  using Char = char32_t;

  struct Glyph {
    F32 advance{0.f};
    Rect<F32> bounds;
    Rect<F32> textureRect;
  };

  Font() = default;
  ~Font() = default;

  // Load a font from the given stream.
  bool loadFromStream(nu::InputStream* stream);

  // Get the glyph data corresponding to the given code point.
  const Glyph& getOrInsertGlyph(I32 characterSize, Char codePoint);

  // Get the amount of kerning between the first and second characters.
  I32 getKerning(I32 characterSize, Char first, Char second) const;

  // Get the ascent of the font.
  F32 getAscent(I32 characterSize);

  // Get the descent of the font.
  F32 getDescent(I32 characterSize);

  // Get the texture that is backing this font.
  const Texture* getTexture(I32 characterSize) const;

private:
  // A row of glyphs.
  struct Row {
    I32 width = 0;
    I32 top = 0;
    I32 height = 0;

    Row(I32 width, I32 top, I32 height)
      : width{width}, top{top}, height{height} {}
  };

  // Table mapping a codepoint to it's glyph.
  using GlyphTable = std::unordered_map<Char, Glyph>;

  struct Page {
    // The scale used to render characters for this page.
    F32 fontScale{0.f};

    // Various bits of information about the font.
    F32 ascent{0.f};
    F32 descent{0.f};

    // The glyphs in this page.
    GlyphTable glyphs;

    // The texture containing the glyphs.
    Texture texture;

    // Y position of the next row in the texture.
    I32 nextRow{0};

    // List containing the position of all the existing rows.
    std::vector<Row> rows;

    // Construct a new Page given the font we belong to and the size of the
    // characters on this page.
    Page(Font* font, I32 characterSize);
  };

  Page* getPage(I32 characterSize);

  // Load a new glyph and store it in the cache.
  Glyph loadGlyph(Page* page, Char codePoint);

  // Find a suitable rectangle within the texture for a glyph.
  Rect<I32> findGlyphRect(Page* page, const Size<I32>& size);

  // Internal font info data.
  stbtt_fontinfo m_fontInfo;

  // The data buffer holding the font data.  We have to keep this alive for the
  // lifetime of the font.
  std::vector<U8> m_fontData;

  // All the pages we have rendered so far.
  std::unordered_map<I32, std::unique_ptr<Page>> m_pages;

  // A temporary pixel buffer that holds the pixel data before it's uploaded to
  // the GPU.
  std::vector<U8> m_pixelBuffer;

  DISALLOW_COPY_AND_ASSIGN(Font);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_FONT_H_

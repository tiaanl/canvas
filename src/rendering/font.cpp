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

#include "canvas/rendering/font.h"

#include <vector>

#include "nucleus/logging.h"
#include "nucleus/streams/file_input_stream.h"
#include "nucleus/types.h"
#include "nucleus/utils/stl.h"
#include "canvas/utils/rect.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Handy shortcut.
#define FONT_INFO static_cast<stbtt_fontinfo*>(m_fontInfo.get())

namespace ca {

Font::Font(i32 characterSize) : m_characterSize{characterSize} {
}

Font::~Font() {
}

bool Font::loadFromStream(nu::InputStream* stream) {
  DCHECK(stream);

  std::vector<u8> buffer;
  auto streamLength = stream->getLength();
  stream->read(nu::vectorAsArray(&buffer, streamLength), streamLength);

  if (!stbtt_InitFont(&m_fontInfo, nu::vectorAsArray(&buffer), 0)) {
    LOG(Error) << "Could not load font from stream";
    return false;
  }

  return true;
}

const Font::Glyph& Font::getOrInsertGlyph(char32_t codePoint) {
  auto it = m_glyphs.find(codePoint);
  if (it != std::end(m_glyphs)) {
    return it->second;
  }

  // We glyph doesn't exist, so we have to create it.
  Glyph glyph = loadGlyph(codePoint);
  auto result = m_glyphs.insert(std::make_pair(codePoint, glyph));
  return result.first->second;
}

i32 Font::getKerning(char32_t first, char32_t second) const {
  if (first == 0 || second == 0) {
    return 0;
  }

  return stbtt_GetCodepointKernAdvance(&m_fontInfo, first, second);
}

f32 Font::getLineSpacing() const {

  i32 ascent, descent, lineGap;
  stbtt_GetFontVMetrics(&m_fontInfo, &ascent, &descent, &lineGap);

  return static_cast<float>(lineGap);
}

Font::Glyph Font::loadGlyph(char32_t codePoint) {
  Glyph result;

  // Get the advance of the glyph.
  i32 advance;
  i32 leftSideBearing;
  stbtt_GetCodepointHMetrics(&m_fontInfo, codePoint, &advance,
                             &leftSideBearing);
  result.advance = static_cast<f32>(advance);

  // Get the bounds of the glyph.
  Rect<i32> rect;
  stbtt_GetCodepointBitmapBox(&m_fontInfo, codePoint, 1.f, 1.f, &rect.pos.x,
                              &rect.pos.y, &rect.size.width, &rect.size.height);
  rect.size.width -= rect.pos.x;
  rect.size.height -= rect.pos.y;

  result.bounds.pos.x = static_cast<f32>(rect.pos.x);
  result.bounds.pos.y = static_cast<f32>(rect.pos.y);
  result.bounds.size.width = static_cast<f32>(rect.size.width);
  result.bounds.size.height = static_cast<f32>(rect.size.height);

  auto ff = findGlyphRect(rect.size);

  int a = 10;

  return result;
}

Rect<i32> Font::findGlyphRect(const Size<i32>& size) {
  // Find a row that will fit the glyph.
  Row* bestRow = nullptr;
  f32 bestRatio = 0.f;
  for (auto& row : m_rows) {
    f32 ratio = static_cast<f32>(size.height) / row.height;

    // Ignore rows that are either too small or too high.
    if (ratio < 0.7f || ratio > 1.f) {
      continue;
    }

    // Check if there is enough horizontal space left in the row.
    if (size.width > m_texture.getSize().width - row.width) {
      continue;
    }

    // Make sure that this new row is the best found so far.
    if (ratio < bestRatio) {
      continue;
    }

    bestRow = &row;
    bestRatio = ratio;
  }

  if (!bestRow) {
    i32 rowHeight = size.height + size.height / 10;

    if ((m_nextRow + rowHeight >= m_texture.getSize().height) || (size.width >= m_texture.getSize().width)) {
      NOTREACHED() << "Texture is too small!";
      return Rect<i32>{};
    }

    // We can not create the new row.
    m_rows.emplace_back(0, m_nextRow, rowHeight);
    m_nextRow += rowHeight;
    bestRow = &m_rows.back();
  }

  // Find the glyph's rectangle on the selected row.
  Rect<i32> rect{bestRow->width, bestRow->top, size.width, size.height};

  // Update the row's width.
  bestRow->width += size.width;

  return rect;
}

void fontTest() {
  nu::FileInputStream fontStream{
      nu::FilePath{FILE_PATH_LITERAL("C:\\Windows\\Fonts\\arial.ttf")}};
  std::vector<unsigned char> buffer;
  auto length = fontStream.getLength();
  fontStream.read(nu::vectorAsArray(&buffer, length), length);

  stbtt_fontinfo fontInfo;
  if (!stbtt_InitFont(&fontInfo, nu::vectorAsArray(&buffer), 0)) {
    LOG(Error) << "Could not initialize font";
    return;  
  }

  const i32 bitmapWidth = 512;
  const i32 bitmapHeight = 128;
  const i32 lineHeight = 64;

  std::vector<u8> bitmap;
  nu::vectorAsArray(&bitmap, bitmapWidth * bitmapHeight);

  const f32 fontScale =
      stbtt_ScaleForPixelHeight(&fontInfo, static_cast<float>(lineHeight));

  std::string words = "How are you?";

  i32 x = 0;
  i32 ascent, descent, lineGap;
  stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);
  ascent *= fontScale;
  descent *= fontScale;

  for (i32 i = 0; i < words.length(); ++i) {
    // Get bounding box for character (may be offset to account for chars that
    // dip above or below the line.
    Rect<i32> rect;
    stbtt_GetCodepointBitmapBox(&fontInfo, words[i], fontScale, fontScale,
                                &rect.pos.x, &rect.pos.y, &rect.size.width,
                                &rect.size.height);
    rect.size.width -= rect.pos.x;
    rect.size.height -= rect.pos.y;

    // Computer Y (different characters have different heights.
    i32 y = ascent + rect.pos.y;

    // Render character (stride and offset is important here.
    i32 byteOffset = x + (y * bitmapWidth);
    stbtt_MakeCodepointBitmap(
        &fontInfo, nu::vectorAsArray(&bitmap) + byteOffset, rect.size.width,
        rect.size.height, bitmapWidth, fontScale, fontScale, words[i]);

    // How wide is the character?
    i32 ax;
    stbtt_GetCodepointHMetrics(&fontInfo, words[i], &ax, 0);
    x += ax * fontScale;

    // Add kerning.
    i32 kern = stbtt_GetCodepointKernAdvance(&fontInfo, words[i], words[i + 1]);
    x += kern * fontScale;
  }

  // Save out a 1 channel image.
  stbi_write_png("C:\\Workspace\\canvas\\out.png", bitmapWidth, bitmapHeight, 1,
                 nu::vectorAsArray(&bitmap), bitmapWidth);
}

}  // namespace ca

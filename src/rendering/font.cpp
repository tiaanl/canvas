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
#include "canvas/utils/gl_check.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace ca {

bool Font::loadFromStream(nu::InputStream* stream) {
  DCHECK(stream);

  auto streamLength = stream->getLength();
  stream->read(nu::vectorAsArray(&m_fontData, streamLength), streamLength);

  if (!stbtt_InitFont(&m_fontInfo, nu::vectorAsArray(&m_fontData), 0)) {
    LOG(Error) << "Could not load font from stream";
    return false;
  }

  return true;
}

const Font::Glyph& Font::getOrInsertGlyph(i32 characterSize,
                                          char32_t codePoint) {
  Page* page = nullptr;

  // Get the page for the glyph.
  auto pageIt = m_pages.find(characterSize);
  if (pageIt == std::end(m_pages)) {
    // If the page doesn't exist yet, create a new page.
    auto result = m_pages.emplace(characterSize,
                                  std::make_unique<Page>(this, characterSize));
    page = result.first->second.get();
  } else {
    page = pageIt->second.get();
  }

  DCHECK(page);

  // Get the page corresponding to the character size.
  auto& glyphs = page->glyphs;

  // Find the glyph.
  auto it = glyphs.find(codePoint);
  if (it != std::end(glyphs)) {
    // Find it, so just return the glyph.
    return it->second;
  } else {
    // Can't find the glyph, so we have to create a new one.
    Glyph glyph = loadGlyph(page, codePoint);
    auto result = glyphs.insert(std::make_pair(codePoint, glyph));
    return result.first->second;
  }
}

i32 Font::getKerning(i32 characterSize, char32_t first, char32_t second) const {
  if (first == 0 || second == 0) {
    return 0;
  }

  return stbtt_GetCodepointKernAdvance(&m_fontInfo, first, second);
}

f32 Font::getLineSpacing(i32 characterSize) const {
  i32 ascent, descent, lineGap;
  stbtt_GetFontVMetrics(&m_fontInfo, &ascent, &descent, &lineGap);

  return static_cast<f32>(lineGap);
}

const Texture* Font::getTexture(i32 characterSize) const {
  auto it = m_pages.find(characterSize);
  if (it != std::end(m_pages)) {
    return &it->second->texture;
  }
  return nullptr;
}

Font::Page::Page(Font* font, i32 characterSize) {
  // Calculate the scale for the characterSize.
  fontScale = stbtt_ScaleForPixelHeight(&font->m_fontInfo,
                                        static_cast<float>(characterSize));

  // Make sure the texture is initialized by default.
  Image image;
  image.create(Size<i32>{128, 128}, Color{0, 0, 0, 0});

  // Create the texture.
  texture.createFromImage(image);
}

Font::Glyph Font::loadGlyph(Page* page, char32_t codePoint) {
  Glyph result;

  // Get the advance of the glyph.
  i32 advance;
  stbtt_GetCodepointHMetrics(&m_fontInfo, codePoint, &advance, nullptr);
  result.advance = static_cast<f32>(advance) * page->fontScale;

  // Get the bounds of the glyph.
  Rect<i32> glyphRect;
  stbtt_GetCodepointBitmapBox(&m_fontInfo, codePoint, page->fontScale,
                              page->fontScale, &glyphRect.pos.x,
                              &glyphRect.pos.y, &glyphRect.size.width,
                              &glyphRect.size.height);
  glyphRect.size.width -= glyphRect.pos.x;
  glyphRect.size.height -= glyphRect.pos.y;

  // Find a place for the glyph in the texture.
  Rect<i32> textureRectI = findGlyphRect(page, glyphRect.size);

  const Size<f32> textureSize{
      static_cast<float>(page->texture.getSize().width),
      static_cast<float>(page->texture.getSize().height)};
  result.textureRect.pos.x =
      static_cast<float>(textureRectI.pos.x) / textureSize.width;
  result.textureRect.pos.y =
      static_cast<float>(textureRectI.pos.y) / textureSize.height;
  result.textureRect.size.width =
      static_cast<float>(textureRectI.size.width) / textureSize.width;
  result.textureRect.size.height =
      static_cast<float>(textureRectI.size.height) / textureSize.height;

  // Resize the pixel buffer so that we can fit the rendered glyph in it.
  m_pixelBuffer.resize(glyphRect.size.width * glyphRect.size.height);

  // Render the character to the temp buffer.
  stbtt_MakeCodepointBitmap(&m_fontInfo, nu::vectorAsArray(&m_pixelBuffer),
                            glyphRect.size.width, glyphRect.size.height,
                            glyphRect.size.width, page->fontScale,
                            page->fontScale, codePoint);

  Image image;
  image.create(glyphRect.size, {255, 255, 255, 255});
  for (i32 y = 0; y < glyphRect.size.height; ++y) {
    for (i32 x = 0; x < glyphRect.size.width; ++x) {
      u8 color = m_pixelBuffer[y * glyphRect.size.width + x];
      image.setPixel({x, y}, Color(255, 255, 255, color));
    }
  }

  Texture::bind(&page->texture);
  GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, textureRectI.pos.x,
                           textureRectI.pos.y, textureRectI.size.width,
                           textureRectI.size.height, GL_RGBA, GL_UNSIGNED_BYTE,
                           image.getData().data()));

  result.bounds.pos.x = static_cast<f32>(glyphRect.pos.x);
  result.bounds.pos.y = static_cast<f32>(glyphRect.pos.y);
  result.bounds.size.width = static_cast<f32>(glyphRect.size.width);
  result.bounds.size.height = static_cast<f32>(glyphRect.size.height);

  return result;
}

Rect<i32> Font::findGlyphRect(Page* page, const Size<i32>& size) {
  // Find a row that will fit the glyph.
  Row* bestRow = nullptr;
  f32 bestRatio = 0.f;
  for (auto& row : page->rows) {
    f32 ratio = static_cast<f32>(size.height) / row.height;

    // Ignore rows that are either too small or too high.
    if (ratio < 0.7f || ratio > 1.f) {
      continue;
    }

    // Check if there is enough horizontal space left in the row.
    if (size.width > page->texture.getSize().width - row.width) {
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

    Size<i32> textureSize{page->texture.getSize()};
    if ((page->nextRow + rowHeight >= textureSize.height) ||
        (size.width >= textureSize.width)) {
      NOTREACHED() << "Texture is too small!";
      return Rect<i32>{};
    }

    // We can now create the new row.
    page->rows.emplace_back(0, page->nextRow, rowHeight);
    page->nextRow += rowHeight;
    bestRow = &page->rows.back();
  }

  DCHECK(bestRow);

  // Find the glyph's rectangle on the selected row.
  Rect<i32> rect{bestRow->width, bestRow->top, size.width, size.height};

  // Update the row's width.
  bestRow->width += size.width;

  return rect;
}

}  // namespace ca

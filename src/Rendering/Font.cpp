
#include "canvas/Rendering/Font.h"

#include "canvas/Utils/GLCheck.h"
#include "canvas/Utils/Rect.h"
#include "nucleus/Logging.h"
#include "nucleus/Streams/FileInputStream.h"
#include "nucleus/Types.h"

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_STROKER_H

#include "nucleus/MemoryDebug.h"

namespace ca {

Font::Font(nu::Allocator* allocator)
  : m_allocator(allocator), m_library(nullptr), m_face(nullptr), m_fontData(allocator) {}

Font::~Font() {
  cleanup();
}

bool Font::loadFromStream(nu::InputStream* stream) {
  DCHECK(stream);

  FT_Library library;
  if (FT_Init_FreeType(&library) != FT_Err_Ok) {
    LOG(Error) << "Could not initialize freetype2";
    return false;
  }
  m_library = library;

  // Load the entire stream into out m_fontData buffer.
  nu::InputStream::SizeType bytesRemaining = stream->getBytesRemaining();
  m_fontData.resize(bytesRemaining);
  stream->read(&m_fontData[0], bytesRemaining);

  // Load the new font face from the stream.
  FT_Face face;
  FT_Error err = FT_New_Memory_Face(static_cast<FT_Library>(m_library), static_cast<const FT_Byte*>(&m_fontData[0]),
                                    static_cast<FT_Long>(bytesRemaining), 0, &face);
  if (err != FT_Err_Ok) {
    switch (err) {
      case FT_Err_Unknown_File_Format:
        LOG(Error) << "Invalid font file format.";
        return false;

      case FT_Err_Invalid_Argument:
        LOG(Error) << "Invalid argument when loading font face.";
        return false;

      default:
        LOG(Error) << "Could not load font.";
        return false;
    }
  }

  // Select the unicode character map.
  if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) != FT_Err_Ok) {
    LOG(Error) << "Could not set unicode character set for font.";
    FT_Done_Face(face);
    return false;
  }

  m_face = face;

  return true;
}  // namespace ca

const Font::Glyph& Font::getOrInsertGlyph(U32 codePoint, U32 characterSize, bool bold) const {
  // Get the page corresponding to the character size.
  GlyphTable& glyphs = m_pages[characterSize].glyphs;

  // Build the key by combining the code point, bold flag and outline thickness.
  U64 key = (static_cast<U64>(bold ? 1 : 0) << 31) | static_cast<U64>(codePoint);

  GlyphTable::const_iterator it = glyphs.find(key);
  if (it != glyphs.end()) {
    return it->second;
  } else {
    Glyph glyph = loadGlyph(codePoint, characterSize, bold);
    return glyphs.insert(std::make_pair(key, glyph)).first->second;
  }
}

F32 Font::getKerning(U32 characterSize, Char first, Char second) const {
  // Special case where first or second is 0.
  if (first == 0 || second == 0) {
    return 0.f;
  }

  FT_Face face = static_cast<FT_Face>(m_face);

  if (face && FT_HAS_KERNING(face) && setCurrentSize(characterSize)) {
    // Convert the characters to indices.
    FT_UInt index1 = FT_Get_Char_Index(face, first);
    FT_UInt index2 = FT_Get_Char_Index(face, second);

    // Get the kerning vector.
    FT_Vector kerning;
    FT_Get_Kerning(face, index1, index2, FT_KERNING_DEFAULT, &kerning);

    // X advance is already in pixels for bitmap fonts.
    if (!FT_IS_SCALABLE(face)) {
      return static_cast<F32>(kerning.x);
    }

    // Return the X advance.
    return static_cast<F32>(kerning.x) / static_cast<float>(1 << 6);
  }

  // Invalid font, or no kerning.
  return 0.f;
}

F32 Font::getLineSpacing(U32 characterSize) const {
  FT_Face face = static_cast<FT_Face>(m_face);

  if (face && setCurrentSize(characterSize)) {
    return static_cast<F32>(face->size->metrics.height) / static_cast<float>(1 << 6);
  }

  return 0.f;
}

Texture* Font::getTexture(U32 characterSize) const {
  auto it = m_pages.find(characterSize);
  if (it == m_pages.end()) {
    LOG(Warning) << "No texture found for characterSize: " << characterSize;
    return nullptr;
  }

  return &it->second.texture;
}

bool Font::setCurrentSize(U32 characterSize) const {
  FT_Face face = static_cast<FT_Face>(m_face);
  FT_UShort currentSize = face->size->metrics.x_ppem;

  if (currentSize != characterSize) {
    FT_Error err = FT_Set_Pixel_Sizes(face, 0, characterSize);

    if (err == FT_Err_Invalid_Pixel_Size) {
      if (!FT_IS_SCALABLE(face)) {
        LOG(Error) << "Could not set bitmap font size to " << characterSize;
        LOG(Error) << "Available sizes:";
        for (I32 i = 0; i < face->num_fixed_sizes; ++i) {
          LOG(Error) << "  " << face->available_sizes[i].height;
        }
      }
    }

    return err == FT_Err_Ok;
  }

  return true;
}

Font::Page::Page() : nextRow(3) {
  // Make sure that the texture is initialized by default.
  Image image;
  image.create(Size<I32>{128, 128}, Color{255, 255, 255, 0});

  // Create the texture.
  texture.createFromImage(image);
  // texture.setSmooth(true);
}

void Font::cleanup() {
  if (m_face) {
    FT_Done_Face(static_cast<FT_Face>(m_face));
  }

  if (m_library) {
    FT_Done_FreeType(static_cast<FT_Library>(m_library));
  }

  m_library = nullptr;
  m_face = nullptr;
  m_pages.clear();
  m_pixelBuffer.clear();
}

Font::Glyph Font::loadGlyph(U32 codePoint, U32 characterSize, bool bold) const {
  Glyph result;

  FT_Library library = static_cast<FT_Library>(m_library);
  FT_Face face = static_cast<FT_Face>(m_face);

  if (!setCurrentSize(characterSize)) {
    return result;
  }

  // Load the glyph corresponding to the code point.
  if (FT_Load_Char(face, codePoint, FT_LOAD_TARGET_NORMAL | FT_LOAD_FORCE_AUTOHINT) != FT_Err_Ok) {
    return result;
  }

  FT_Glyph glyphDesc;
  if (FT_Get_Glyph(face->glyph, &glyphDesc) != FT_Err_Ok) {
    return result;
  }

  // Apply the bold modifiers.
  FT_Pos weight = 1 << 6;
  bool outline = glyphDesc->format == FT_GLYPH_FORMAT_OUTLINE;
  if (outline) {
    if (bold) {
      FT_OutlineGlyph outlineGlyph = reinterpret_cast<FT_OutlineGlyph>(glyphDesc);
      FT_Outline_Embolden(&outlineGlyph->outline, weight);
    }
  }

  // Convert the glyph to a bitmap (rasterize it).
  FT_Glyph_To_Bitmap(&glyphDesc, FT_RENDER_MODE_NORMAL, 0, 1);
  FT_Bitmap& bitmap = reinterpret_cast<FT_BitmapGlyph>(glyphDesc)->bitmap;

  // Apply bold if needed.
  if (!outline) {
    if (bold) {
      FT_Bitmap_Embolden(library, &bitmap, weight, weight);
    }
  }

  // Compute the glyph's advance offset.
  result.advance = static_cast<F32>(face->glyph->metrics.horiAdvance) / static_cast<F32>(1 << 6);
  if (bold) {
    result.advance += static_cast<F32>(weight) / static_cast<F32>(1 << 6);
  }

  I32 width = bitmap.width;
  I32 height = bitmap.rows;

  // Leave a small padding around the characters, so that filtering doesn't pollute each glyph with pixels from
  // neighbours.
  const I32 padding = 1;

  I32 ascent = face->size->metrics.ascender + face->size->metrics.descender;

  if (width > 0 && height > 0) {
    // Get the glyph page corresponding to the character size.
    Page& page = m_pages[characterSize];

    // Get the texture size.
    Size<I32> textureSize = page.texture.getSize();

    // Find a good position for the new glyph in the texture.
    Rect<I32> glyphRect = findGlyphRect(page, Size<I32>{width + 2 * padding, height + 2 * padding});

    // Make sure the texture data is positioned in the center of the allocated texture rectangle.
    glyphRect.pos.x += padding;
    glyphRect.pos.y += padding;
    glyphRect.size.width -= 2 * padding;
    glyphRect.size.height -= 2 * padding;

    // Set the texture coordinates. [0.0f...1.0f]
    result.textureRect.pos.x = static_cast<F32>(glyphRect.pos.x) / static_cast<F32>(textureSize.width);
    result.textureRect.pos.y = static_cast<F32>(glyphRect.pos.y) / static_cast<F32>(textureSize.width);
    result.textureRect.size.width = static_cast<F32>(glyphRect.size.width) / static_cast<F32>(textureSize.height);
    result.textureRect.size.height = static_cast<F32>(glyphRect.size.height) / static_cast<F32>(textureSize.height);

    // Compute the glyph's bounding box.
    result.bounds.pos.x = face->glyph->metrics.horiBearingX / (1 << 6);
    result.bounds.pos.y = (ascent - face->glyph->metrics.horiBearingY) / (1 << 6);
    result.bounds.size.width = face->glyph->metrics.width / (1 << 6);
    result.bounds.size.height = face->glyph->metrics.height / (1 << 6);

    // Extract the glyph's pixels from the bitmap.
    m_pixelBuffer.resize(width * height * 4, 255);
    const U8* pixels = bitmap.buffer;
    if (bitmap.pixel_mode == FT_PIXEL_MODE_MONO) {
      // Pixels are 1 bit monochrome values.
      for (I32 y = 0; y < height; ++y) {
        for (I32 x = 0; x < width; ++x) {
          // The color channels remain white, just fill the alpha channel.
          std::size_t index = (x + y * width) * 4 + 3;
          m_pixelBuffer[index] = ((pixels[x / 8]) & (1 << (7 - (x % 8)))) ? 255 : 0;
        }
        pixels += bitmap.pitch;
      }
    } else {
      // Pixels are 8 bits gray levels.
      for (I32 y = 0; y < height; ++y) {
        for (I32 x = 0; x < width; ++x) {
          // The color channels remain white, just fill  the alpha channel.
          std::size_t index = (x + y * width) * 4 + 3;
          m_pixelBuffer[index] = pixels[x];
        }
        pixels += bitmap.pitch;
      }
    }

    page.texture.update(&m_pixelBuffer[0], glyphRect);
  }

  FT_Done_Glyph(glyphDesc);

  return result;
}

Rect<I32> Font::findGlyphRect(Page& page, const Size<I32>& size) const {
  // Find a row that will fit the glyph.
  Row* bestRow = nullptr;
  F32 bestRatio = 0.f;
  for (auto& row : page.rows) {
    F32 ratio = static_cast<F32>(size.height) / row.height;

    // Ignore rows that are either too small or too high.
    if (ratio < 0.7f || ratio > 1.f) {
      continue;
    }

    // Check if there is enough horizontal space left in the row.
    if (size.width > (page.texture.getSize().width - row.width)) {
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
    I32 rowHeight = size.height + size.height / 10;

    Size<I32> textureSize{page.texture.getSize()};
    if ((page.nextRow + rowHeight >= textureSize.height) || (size.width >= textureSize.width)) {
      NOTREACHED() << "Texture is too small!";
      return Rect<I32>{};
    }

    // We can now create the new row.
    page.rows.emplaceBack(page.nextRow, rowHeight);
    page.nextRow += rowHeight;
    bestRow = &page.rows.last();
  }

  DCHECK(bestRow);

  // Find the glyph's rectangle on the selected row.
  Rect<I32> rect{static_cast<I32>(bestRow->width), static_cast<I32>(bestRow->top), static_cast<I32>(size.width),
                 static_cast<I32>(size.height)};

  // Update the row's width.
  bestRow->width += size.width;

  return rect;
}

}  // namespace ca

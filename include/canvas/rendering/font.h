
#ifndef CANVAS_RENDERING_FONT_H_
#define CANVAS_RENDERING_FONT_H_

#include <memory>
#include <unordered_map>

#include "nucleus/macros.h"
#include "nucleus/types.h"

#include "canvas/rendering/texture.h"
#include "canvas/utils/rect.h"
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

  Font();
  ~Font();

  // Load a font from the given stream.
  bool loadFromStream(nu::InputStream* stream);

  // Get the glyph data corresponding to the given code point.
  const Glyph& getOrInsertGlyph(U32 codePoint, U32 characterSize, bool bold) const;

  // Get the amount of kerning between the first and second characters.
  F32 getKerning(U32 characterSize, Char first, Char second) const;

  // Get the line spacing.
  F32 getLineSpacing(U32 characterSize) const;

  // Get the texture that is backing this font.
  Texture* getTexture(U32 characterSize) const;

private:
  struct Row {
    // Current width of the row.
    U32 width;

    // Y position of the row in the texture.
    U32 top;

    // Height of the row.
    U32 height;

    Row(U32 top, U32 height) : width(0), top(top), height(height) {}
  };

  using GlyphTable = std::unordered_map<U64, Glyph>;

  struct Page {
    // Table mapping code points to their corresponding glyph.
    GlyphTable glyphs;

    // Texture containing the pixels of the glyphs.
    Texture texture;

    // Y position of the next new row in the texture.
    U32 nextRow;

    // List containing the position of all the existing rows.
    std::vector<Row> rows;

    Page();
  };

  // Free all internal resources.
  void cleanup();

  // Load a new glyph and store it in the cache.
  Glyph loadGlyph(U32 codePoint, U32 characterSize, bool bold) const;

  // Find a suitable rectangle within the texture for a glyph.
  Rect<I32> findGlyphRect(Page& page, const Size<I32>& size) const;

  // Make sure that the given size is the current one.
  bool setCurrentSize(U32 characterSize) const;

  using PageTable = std::unordered_map<U32, Page>;

  // Pointer to the internal library.
  void* m_library;

  // Pointer to the internal font face.
  void* m_face;

  // Pointer to the internal stream record.
  void* m_streamRec;

  // Pointer to the stroker.
  void* m_stroker;

  // Table containing the glyph pages by character size.
  mutable PageTable m_pages;

  // Pixel buffer holding a glyph's pixels before being written to the texture.
  mutable std::vector<U8> m_pixelBuffer;

  DISALLOW_COPY_AND_ASSIGN(Font);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_FONT_H_

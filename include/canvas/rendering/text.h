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

#ifndef CANVAS_RENDERING_TEXT_H_
#define CANVAS_RENDERING_TEXT_H_

#include <string>

#include "canvas/math/mat4.h"
#include "canvas/rendering/geometry.h"
#include "nucleus/macros.h"

namespace ca {

class Canvas;
class Font;

class Text {
public:
  Text();
  explicit Text(Font* font, i32 textSize = 30,
                const std::string& text = std::string{});
  ~Text() = default;

  // Get/set the font used to render the text.
  Font* getFont() const { return m_font; }
  void setFont(Font* font);

  // Set the text we want to render.
  void setText(const std::string& text);

  // Set the size of the text we want to render.
  void setTextSize(i32 textSize);

  // Get the bounds of the text we're rendering.
  const Rect<i32>& getBounds() const { return m_bounds; }

  // Render the text.
  void render(Canvas* canvas, const Mat4& transform) const;

private:
  // Make sure the shaders for text rendering is initialized.
  void ensureShaders();

  // Take the font and create the geometry we use to render the text glyphs.
  void updateGeometry();

  // The font we want to render.
  Font* m_font{nullptr};

  // The text we want to render.
  std::string m_text;

  // The size of the text we want to render.
  i32 m_textSize{30};

  // The geometry we render.
  Geometry m_geometry{Geometry::Triangles};

  // The bounds of the geometry.
  Rect<i32> m_bounds;

  DISALLOW_COPY_AND_ASSIGN(Text);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_TEXT_H_

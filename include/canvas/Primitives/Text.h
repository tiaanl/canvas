
#ifndef CANVAS_RENDERING_TEXT_H_
#define CANVAS_RENDERING_TEXT_H_

#include "canvas/Math/Mat4.h"
#include "canvas/Rendering/Geometry.h"
#include "canvas/Rendering/Program.h"
#include "canvas/Resources/Resource.h"
#include "nucleus/Macros.h"
#include "nucleus/Memory/ScopedPtr.h"
#include "nucleus/Types.h"

namespace ca {

class Canvas;
class Font;
class ResourceManager;

class Text {
public:
  COPY_DELETE(Text);
  MOVE_DELETE(Text);

  explicit Text(ResourceManager* resourceManager, nu::String text = "text",
                nu::String fontName = "default", I32 textSize = 32);
  ~Text() = default;

  // Get/set the font used to render the text.
  const ResourceRef<Font>& getFont() const {
    return m_font;
  }
  void setFont(const ResourceRef<Font>& font);

  // Set the text we want to render.
  void setText(const nu::String& text);

  // Set the size of the text we want to render.
  void setTextSize(I32 textSize);

  // Get the bounds of the text we're rendering.
  const Rect<I32>& getBounds() const {
    return m_bounds;
  }

  // Render the text.
  void render(Canvas* canvas, const Mat4& transform) const;

private:
  // Make sure the shaders for text rendering is initialized.
  void ensureShaders();

  // Take the font and create the geometry we use to render the text glyphs.
  void updateGeometry();

  ResourceManager* m_resourceManager = nullptr;

  // Shaders we use to render text.
  ResourceRef<Program> m_program;

  // The font we want to render.
  ResourceRef<Font> m_font;

  // The text we want to render.
  nu::String m_text;

  // The size of the text we want to render.
  I32 m_textSize = 30;

  // The geometry we render.
  Geometry m_geometry{Geometry::Triangles};

  // The bounds of the geometry.
  Rect<I32> m_bounds;
};

}  // namespace ca

#endif  // CANVAS_RENDERING_TEXT_H_

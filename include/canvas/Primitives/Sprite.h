
#ifndef CANVAS_RENDERING_SPRITE_H_
#define CANVAS_RENDERING_SPRITE_H_

#include "canvas/Math/Mat4.h"
#include "canvas/Rendering/Canvas.h"
#include "canvas/Rendering/Geometry.h"
#include "canvas/Rendering/Program.h"
#include "canvas/Rendering/Texture.h"
#include "nucleus/Macros.h"

namespace ca {

class Sprite {
public:
  explicit Sprite(Texture* texture = nullptr);
  ~Sprite();

  // Get the bounds of the sprite.
  ca::Rect<F32> getBounds() const;

  void setTexture(Texture* texture);

  // Render the sprite on the specified canvas at the specified transform
  // location.
  void render(Canvas* canvas, const Mat4& transform) const;

private:
  // Rebuild the geometry when we change the internals of the sprite.
  void updateGeometry();

  // Make sure we created the shader that we'll use to render all sprites.
  static void ensureShaderProgram();

  // The shader program we use to render the sprite.
  static Program s_shaderProgram;
  static bool s_shaderProgramInitialized;
  static Resource<Shader> s_vertexShader;
  static Resource<Shader> s_fragmentShader;

  // The texture we want to render.
  Texture* m_texture;

  // The geometry we'll use to render the sprite.
  Geometry m_geometry;

  DISALLOW_COPY_AND_ASSIGN(Sprite);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_SPRITE_H_

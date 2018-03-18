
#ifndef CANVAS_RENDERING_SPRITE_H_
#define CANVAS_RENDERING_SPRITE_H_

#include "canvas/Math/Mat4.h"
#include "canvas/Rendering/Canvas.h"
#include "canvas/Rendering/Geometry.h"
#include "canvas/Rendering/Program.h"
#include "canvas/Rendering/Texture.h"
#include "nucleus/Macros.h"

namespace ca {

class ResourceManager;

class Sprite {
public:
  COPY_DELETE(Sprite);
  MOVE_DELETE(Sprite);

  explicit Sprite(ResourceManager* resourceManager, const ResourceRef<Texture>& texture = nullptr);
  ~Sprite();

  // Get the bounds of the sprite.
  ca::Rect<F32> getBounds() const;

  void setTexture(const ResourceRef<Texture>& texture);

  // Render the sprite on the specified canvas at the specified transform
  // location.
  void render(Canvas* canvas, const Mat4& transform) const;

private:
  // Make sure we created the shader that we'll use to render all sprites.
  bool ensureShaderProgram();

  // Rebuild the geometry when we change the internals of the sprite.
  void updateGeometry();

  // The resource manager we use for storing the shader programs.
  ResourceManager* m_resourceManager;

  // The shader program we use to render sprites.
  ResourceRef<Program> m_shaderProgram;

  // The texture we want to render.
  ResourceRef<Texture> m_texture;

  // The geometry we'll use to render the sprite.
  Geometry m_geometry;
};

}  // namespace ca

#endif  // CANVAS_RENDERING_SPRITE_H_

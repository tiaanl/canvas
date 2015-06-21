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

#ifndef CANVAS_RENDERING_SPRITE_H_
#define CANVAS_RENDERING_SPRITE_H_

#include "nucleus/macros.h"

#include "canvas/math/mat4.h"
#include "canvas/rendering/canvas.h"
#include "canvas/rendering/geometry.h"
#include "canvas/rendering/program.h"
#include "canvas/rendering/texture.h"

namespace ca {

class Sprite {
public:
  explicit Sprite(Texture* texture = nullptr);
  ~Sprite();

  void setTexture(Texture* texture);

  // Render the sprite on the specified canvas at the specified transform
  // location.
  void render(Canvas* canvas, const Mat4& transform);

private:
  // Rebuild the geometry when we change the internals of the sprite.
  void updateGeometry();

  // Make sure we created the shader that we'll use to render all sprites.
  static void ensureShaderProgram();

  // The shader program we use to render the sprite.
  static Program* s_shaderProgram;

  // The texture we want to render.
  Texture* m_texture;

  // The geometry we'll use to render the sprite.
  Geometry m_geometry;

  DISALLOW_COPY_AND_ASSIGN(Sprite);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_SPRITE_H_

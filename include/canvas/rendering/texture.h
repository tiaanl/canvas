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

#ifndef CANVAS_RENDERING_TEXTURE_H_
#define CANVAS_RENDERING_TEXTURE_H_

#include "nucleus/macros.h"

#include "canvas/opengl.h"
#include "canvas/utils/image.h"

namespace ca {

class Texture {
public:
  Texture() = default;
  ~Texture();

  // Bind the texture.
  void bind() const;

  // Create the texture from Image data.
  bool createFromImage(const Image& image);

private:
  // Create/recreate a new OpenGL name.
  void createNewName();

  // The OpenGL name of the texture.
  GLuint m_name{0};

  DISALLOW_COPY_AND_ASSIGN(Texture);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_TEXTURE_H_


#ifndef CANVAS_RENDERING_TEXTURE_H_
#define CANVAS_RENDERING_TEXTURE_H_

#include "nucleus/Macros.h"
#include "nucleus/Types.h"

#include "canvas/opengl.h"
#include "canvas/utils/image.h"
#include "canvas/utils/rect.h"

namespace ca {

class Texture {
public:
  // Bind the specified texture.
  static void bind(const Texture* texture);

  Texture() = default;
  ~Texture();

  // Get the size of the texture.
  const Size<I32>& getSize() const { return m_size; }

  // Create a blank texture.
  bool create(const Size<I32>& size);

  // Create the texture from Image data.
  bool createFromImage(const Image& image);

  // Update a portion of the texture on the GPU.
  void update(const U8* pixels, const Rect<I32>& rect);

private:
  // Create/recreate a new OpenGL name.
  void createNewName();

  // The OpenGL name of the texture.
  GLuint m_name{0};

  // The size of the texture.
  Size<I32> m_size;

  DISALLOW_COPY_AND_ASSIGN(Texture);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_TEXTURE_H_


#ifndef CANVAS_RESOURCES_TEXTURE_RESOURCE_H_
#define CANVAS_RESOURCES_TEXTURE_RESOURCE_H_

#include "canvas/Rendering/Texture.h"
#include "nucleus/Memory/RefCounted.h"
#include "nucleus/Memory/ScopedPtr.h"
#include "nucleus/Memory/ScopedRefPtr.h"

namespace ca {

class TextureResource : public nu::RefCountedThreadSafe<TextureResource> {
public:
  TextureResource();

  const nu::ScopedPtr<Texture>& getTexture() const { return m_texture; }

private:
  friend nu::RefCountedThreadSafe<TextureResource>;
  ~TextureResource();

  nu::ScopedPtr<Texture> m_texture;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_TEXTURE_RESOURCE_H_

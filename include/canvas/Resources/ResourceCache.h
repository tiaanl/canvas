
#ifndef CANVAS_RESOURCES_RESOURCE_CACHE_H_
#define CANVAS_RESOURCES_RESOURCE_CACHE_H_

#include "canvas/Rendering/Texture.h"
#include "canvas/Utils/Image.h"
#include "nucleus/Allocators/DefaultAllocator.h"
#include "nucleus/Files/FilePath.h"

namespace ca {

class ResourceCache {
public:
  ResourceCache(nu::Allocator* allocator = nu::getDefaultAllocator());
  ~ResourceCache();

  const nu::FilePath& getRootPath() const { return m_rootPath; }

  void setRootPath(const nu::FilePath& rootPath);

  Image* getImage(const nu::String& path);
  Texture* getTexture(const nu::String& path);

private:
  nu::FilePath getFilePathForResourcePath(const nu::String& path);

  nu::FilePath m_rootPath;

  template <typename T>
  struct Pair {
    nu::String path;
    T resource;

    Pair(const nu::String& path, T&& resource) : path(path), resource(nu::move(resource)) {}
    Pair(Pair&& other) noexcept : path(nu::move(other.path)), resource(nu::move(other.resource)) {}
  };

  nu::DynamicArray<Pair<Image>> m_images;
  nu::DynamicArray<Pair<Texture>> m_textures;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_CACHE_H_

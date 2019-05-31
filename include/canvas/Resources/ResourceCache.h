
#ifndef CANVAS_RESOURCES_RESOURCE_CACHE_H_
#define CANVAS_RESOURCES_RESOURCE_CACHE_H_

#include "canvas/Rendering/Shader.h"
#include "canvas/Rendering/Texture.h"
#include "canvas/Resources/Resource.h"
#include "canvas/Utils/Image.h"
#include "nucleus/FilePath.h"

namespace ca {

template <typename ResourceType>
class ResourceCache {
public:
  COPY_DELETE(ResourceCache);
  MOVE_DELETE(ResourceCache);

  ResourceCache() = default;
  ~ResourceCache() = default;

  bool has(const nu::String& path) const {
    for (MemSize i = 0; i < m_cache.getSize(); ++i) {
      if (m_cache[i].path == path) {
        return true;
      }
    }

    return false;
  }

  ResourceRef<ResourceType> get(const nu::String& path) const {
    Pair* pair = findPair(path);
    if (pair) {
      return {&pair->resource};
    }

    return nullptr;
  }

  template <typename... Args>
  ResourceRef<ResourceType> getOrCreate(const nu::String& path, Args&&... args) {
    // Check if the pair already exists.
    Pair* pair = findPair(path);

    // If it exists, then we just return the existing resource.
    if (pair) {
      return pair->resource;
    }

    // Create a new empty resource and save it to the cache.
    m_cache.emplaceBack(path,
                        nu::makeScopedRefPtr<Resource<ResourceType>>(std::forward<Args>(args)...));
    pair = &m_cache.last();

    // Set the name of the new resource.
    pair->resource->setName(path);

    return pair->resource;
  }

private:
  struct Pair {
    COPY_DELETE(Pair);

    nu::String path;
    ResourceRef<ResourceType> resource;
  };

  Pair* findPair(const nu::String& path) const {
    for (MemSize i = 0; i < m_cache.getSize(); ++i) {
      if (m_cache[i].path == path) {
        return const_cast<Pair*>(&m_cache[i]);
      }
    }

    return nullptr;
  }

  nu::DynamicArray<Pair> m_cache;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_CACHE_H_

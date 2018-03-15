
#ifndef CANVAS_RESOURCES_RESOURCE_CACHE_H_
#define CANVAS_RESOURCES_RESOURCE_CACHE_H_

#include "canvas/Rendering/Shader.h"
#include "canvas/Rendering/Texture.h"
#include "canvas/Resources/Resource.h"
#include "canvas/Utils/Image.h"
#include "nucleus/FilePath.h"
#include "nucleus/Ref.h"

namespace ca {

template <typename ResourceType>
class ResourceCache {
public:
  COPY_DELETE(ResourceCache);
  MOVE_DELETE(ResourceCache);

  ResourceCache() = default;
  ~ResourceCache() = default;

  bool has(const nu::String& path) const {
    for (USize i = 0; i < m_cache.getSize(); ++i) {
      if (m_cache[i].path == path) {
        return true;
      }
    }

    return false;
  }

  ResourceRef<ResourceType> get(const nu::String& path) const {
    for (USize i = 0; i < m_cache.getSize(); ++i) {
      if (m_cache[i].path == path) {
        return {const_cast<Resource<ResourceType>*>(&m_cache[i].resource)};
      }
    }

    return {};
  }

  template <typename... Args>
  ResourceRef<ResourceType> getOrCreate(const nu::String& path, Args&&... args) {
    // Check if the pair already exists.
    Pair* pair = findPair(path);

    // If it exists, then we just return the existing resource.
    if (pair) {
      return {&pair->resource};
    }

    // Create a new empty resource.
    ResourceType newResource{std::forward<Args>(args)...};

    // Save it in the cache.
    m_cache.emplaceBack(path, std::move(newResource));
    pair = &m_cache.last();

    return {&pair->resource};
  }

  ResourceRef<ResourceType> put(const nu::String& path, ResourceType&& resource) {
    Pair* pair = findPair(path);

    if (pair) {
      pair->resource.get() = std::forward<ResourceType>(resource);
    } else {
      m_cache.emplaceBack(path, std::forward<ResourceType>(resource));
      pair = &m_cache.last();
    }

    return {&pair->resource};
  }

private:
  struct Pair {
    nu::String path;
    Resource<ResourceType> resource;

    Pair(const nu::String& path, ResourceType&& resource) : path(path), resource(std::move(resource)) {}
    Pair(Pair&& other) noexcept : path(std::move(other.path)), resource(std::move(other.resource)) {}
  };

  Pair* findPair(const nu::String& path) {
    for (USize i = 0; i < m_cache.getSize(); ++i) {
      if (m_cache[i].path == path) {
        return &m_cache[i];
      }
    }

    return nullptr;
  }

  nu::DynamicArray<Pair> m_cache;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_CACHE_H_

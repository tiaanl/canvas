
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

  ResourceRef<ResourceType> put(const nu::String& path, ResourceType&& resource) {
    Pair* pair = nullptr;

    for (USize i = 0; i < m_cache.getSize(); ++i) {
      if (m_cache[i].path == path) {
        pair = &m_cache[i];
      }
    }

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

  nu::DynamicArray<Pair> m_cache;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_CACHE_H_

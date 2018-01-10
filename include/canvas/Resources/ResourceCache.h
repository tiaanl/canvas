
#ifndef CANVAS_RESOURCES_RESOURCE_CACHE_H_
#define CANVAS_RESOURCES_RESOURCE_CACHE_H_

#include "canvas/Rendering/Shader.h"
#include "canvas/Rendering/Texture.h"
#include "canvas/Resources/Resource.h"
#include "canvas/Utils/Image.h"
#include "nucleus/Allocators/Allocated.h"
#include "nucleus/Allocators/DefaultAllocator.h"
#include "nucleus/FilePath.h"
#include "nucleus/Ref.h"

namespace ca {

template <typename T>
class ResourceCache {
public:
  explicit ResourceCache(nu::Allocator* allocator) : m_cache(allocator) {}

  bool has(const nu::String& path) const {
    for (USize i = 0; i < m_cache.getSize(); ++i) {
      if (m_cache[i].path == path) {
        return true;
      }
    }

    return false;
  }

  ResourceRef<T> get(const nu::String& path) const {
    for (USize i = 0; i < m_cache.getSize(); ++i) {
      if (m_cache[i].path == path) {
        return {const_cast<Resource<T>*>(&m_cache[i].resource)};
      }
    }

    return {};
  }

  ResourceRef<T> put(const nu::String& path, T&& resource) {
    Pair<Resource<T>>* pair = nullptr;

    for (USize i = 0; i < m_cache.getSize(); ++i) {
      if (m_cache[i].path == path) {
        pair = &m_cache[i];
      }
    }

    if (pair) {
      pair->resource = std::forward<T>(resource);
    } else {
      m_cache.emplaceBack(path, std::forward<T>(resource));
      pair = &m_cache.last();
    }

    return {&pair->resource};
  }

private:
  template <typename T>
  struct Pair {
    nu::String path;
    T resource;

    Pair(const nu::String& path, T&& resource) : path(path), resource(std::move(resource)) {}
    Pair(Pair&& other) noexcept : path(std::move(other.path)), resource(std::move(other.resource)) {}
  };

  nu::DynamicArray<Pair<Resource<T>>> m_cache;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_CACHE_H_

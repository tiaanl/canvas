
#ifndef CANVAS_RESOURCES_RESOURCE_H_
#define CANVAS_RESOURCES_RESOURCE_H_

#include "nucleus/RefCounted.h"
#include "nucleus/Utils/Move.h"

namespace ca {

template <typename T>
class Resource : public nu::RefCounted {
public:
  using ResourceType = T;

  template <typename... Args>
  Resource(Args&&... args) : m_resource(nu::forward<Args>(args)...) {}

  Resource(const ResourceType& resource) : m_resource(resource) {}

  Resource(ResourceType&& resource) : m_resource(nu::move(resource)) {}

  Resource(const Resource& other) = delete;

  Resource(Resource&& other) : m_resource(nu::move(other.m_resource)) {}

  ~Resource() = default;

  Resource& operator=(const ResourceType& resource) {
    m_resource = resource;
    return *this;
  }

  Resource& operator=(ResourceType&& resource) {
    m_resource = nu::move(resource);
    return *this;
  }

  Resource& operator=(const Resource& other) = delete;

  Resource& operator=(Resource&& other) {
    m_resource = nu::move(other.m_resource);
    return *this;
  }

  ResourceType& get() {
    return m_resource;
  }

  const ResourceType& get() const {
    return m_resource;
  }

  void release() {
    if (nu::RefCounted::release()) {
      int a = 0;
    }
  }

private:
  ResourceType m_resource;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_H_

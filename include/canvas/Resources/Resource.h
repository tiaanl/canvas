
#ifndef CANVAS_RESOURCES_RESOURCE_H_
#define CANVAS_RESOURCES_RESOURCE_H_

#include "nucleus/Logging.h"
#include "nucleus/Ref.h"
#include "nucleus/RefCounted.h"

namespace ca {

template <typename T>
class Resource;

template <typename T>
struct ResourceTraits {
  static void destruct(const Resource<T>* resource) {
    // LOG(Info) << "Destructing resource.";
  }
};

template <typename T>
class Resource : public nu::RefCounted<Resource<T>, ResourceTraits<T>> {
public:
  using ResourceType = T;

  template <typename... Args>
  Resource(Args&&... args) : m_resource(std::forward<Args>(args)...) {}

  Resource(const ResourceType& resource) : m_resource(resource) {}

  Resource(ResourceType&& resource) : m_resource(std::move(resource)) {}

  Resource(const Resource& other) = delete;

  Resource(Resource&& other) : m_resource(std::move(other.m_resource)) {}

  ~Resource() = default;

  Resource& operator=(const ResourceType& resource) {
    m_resource = resource;
    return *this;
  }

  Resource& operator=(ResourceType&& resource) {
    m_resource = std::move(resource);
    return *this;
  }

  Resource& operator=(const Resource& other) = delete;

  Resource& operator=(Resource&& other) {
    m_resource = std::move(other.m_resource);
    return *this;
  }

  ResourceType& get() {
    return m_resource;
  }

  const ResourceType& get() const {
    return m_resource;
  }

private:
  ResourceType m_resource;
};

template <typename T>
using ResourceRef = nu::Ref<Resource<T>>;

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_H_

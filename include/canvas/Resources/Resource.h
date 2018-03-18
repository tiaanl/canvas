
#ifndef CANVAS_RESOURCES_RESOURCE_H_
#define CANVAS_RESOURCES_RESOURCE_H_

#include "nucleus/Logging.h"
#include "nucleus/Ref.h"
#include "nucleus/RefCounted.h"
#include "nucleus/Text/String.h"

namespace ca {

template <typename T>
class Resource;

template <typename T>
struct ResourceTraits {
  static void destruct(const Resource<T>* resource) {
    LOG(Info) << "Destructing resource. (" << resource->getName() << ")";
  }
};

template <typename T>
class Resource : public T, public nu::RefCounted<Resource<T>, ResourceTraits<T>> {
public:
  COPY_DELETE(Resource);

  Resource() : T{}, nu::RefCounted<Resource<T>, ResourceTraits<T>>{} {}

  // template <typename... Args>
  // Resource(Args&&... args) : T{std::forward<Args>(args)...} {}

  Resource(Resource&& other) : T{std::forward<T>(other)} {}

  Resource& operator=(Resource&&) = delete;

  const nu::String& getName() const {
    return m_name;
  }

  void setName(const nu::String& name) {
    m_name = name;
  }

  bool isLoaded() const {
    return m_isLoaded;
  }

  void setLoaded(bool loaded) {
    m_isLoaded = loaded;
  }

private:
  nu::String m_name{};
  bool m_isLoaded = false;
};

template <typename T>
using ResourceRef = nu::Ref<Resource<T>>;

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_H_

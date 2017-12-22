
#ifndef CANVAS_RESOURCES_RESOURCE_MANAGER_H_
#define CANVAS_RESOURCES_RESOURCE_MANAGER_H_

#include "nucleus/Files/FilePath.h"

namespace ca {

class ResourceManager {
public:
    explicit ResourceManager(nu::Allocator* allocator = nu::getDefaultAllocator());
    ~ResourceManager();

    const nu::FilePath& getRootPath() const {
      return m_rootPath;
    }

    void setRootPath(const nu::FilePath& rootPath) {
      m_rootPath = rootPath;
    }

private:
    nu::Allocator* m_allocator;
    nu::FilePath m_rootPath;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_MANAGER_H_

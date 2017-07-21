
#ifndef CANVAS_RESOURCES_RESOURCE_MANAGER_H_
#define CANVAS_RESOURCES_RESOURCE_MANAGER_H_

#include <unordered_map>

#include "canvas/Resources/TextureResource.h"
#include "nucleus/files/file_path.h"

namespace ca {

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    const nu::FilePath& getRootPath() const { return m_rootPath; }
    void setRootPath(const nu::FilePath& rootPath);

    nu::ScopedRefPtr<TextureResource> getTexture(const std::string& name);

private:
    nu::FilePath m_rootPath;

    std::unordered_map<std::string, nu::ScopedRefPtr<TextureResource>> m_textures;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_MANAGER_H_

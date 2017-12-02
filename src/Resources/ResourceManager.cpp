
#include "canvas/Resources/ResourceManager.h"
#include "nucleus/logging.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

void ResourceManager::setRootPath(const nu::FilePath& rootPath) {
  m_rootPath = rootPath;
}

nu::ScopedRefPtr<TextureResource> ResourceManager::getTexture(const std::string& name) {
  nu::FilePath::StringType namePath(name.begin(), name.end());

  nu::FilePath path = m_rootPath;
  path = path.append(namePath);

  //    LOG(Info) << path;

  return nu::ScopedRefPtr<TextureResource>{};
}

}  // namespace ca

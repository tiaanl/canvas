
#include "canvas/Resources/ResourceManager.h"
#include "nucleus/Streams/FileInputStream.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

ResourceManager::ResourceManager(nu::Allocator* allocator) : m_images(allocator), m_textures(allocator) {}

const nu::FilePath& ResourceManager::getRootPath() const {
  return m_rootPath;
}

void ResourceManager::setRootPath(const nu::FilePath& rootPath) {
  m_rootPath = rootPath;
}

ResourceRef<Image> ResourceManager::getImage(const nu::String& path) {
  ResourceRef<Image> resource = m_images.get(path);
  if (!resource.isEmpty()) {
    return resource;
  }

  nu::FileInputStream stream{getFilePathForResource(path)};
  if (!stream.openedOk()) {
    LOG(Error) << "Could not open resource (" << path << ")";
    return {nullptr};
  }

  Image newImage;
  if (!newImage.loadFromStream(&stream)) {
    LOG(Error) << "Could not load resource (" << path << ")";
    return {nullptr};
  }

  return m_images.put(path, std::move(newImage));
}

ResourceRef<Texture> ResourceManager::getTexture(const nu::String& path) {
  auto resource = getImage(path);
  if (resource.isEmpty()) {
    return {};
  }

  Texture newTexture;
  newTexture.createFromImage(resource.get()->get());

  return m_textures.put(path, std::move(newTexture));
}

nu::FilePath ResourceManager::getFilePathForResource(const nu::String& path) {
  return m_rootPath.append(nu::FilePath::normalizeSeparators(path));
}

}  // namespace ca

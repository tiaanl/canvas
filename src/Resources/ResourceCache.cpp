
#include "canvas/Resources/ResourceCache.h"

#include "nucleus/Streams/FileInputStream.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

ResourceCache::ResourceCache(nu::Allocator* allocator) : m_images(allocator), m_textures(allocator) {}

ResourceCache::~ResourceCache() = default;

void ResourceCache::setRootPath(const nu::FilePath &rootPath) {
  m_rootPath = rootPath;
}

Image* ResourceCache::getImage(const nu::String& path) {
  for (USize i = 0; i < m_images.getSize(); ++i) {
    if (m_images[i].path == path) {
      return &m_images[i].resource;
    }
  }

  nu::FileInputStream stream{getFilePathForResourcePath(path)};
  if (!stream.openedOk()) {
    return nullptr;
  }

  Image newImage;
  if (!newImage.loadFromStream(&stream)) {
    return nullptr;
  }

  m_images.emplaceBack(path, std::move(newImage));

  return &m_images.last().resource;
}

Texture* ResourceCache::getTexture(const nu::String& path) {
  for (USize i = 0; i < m_textures.getSize(); ++i) {
    if (m_textures[i].path == path) {
      return &m_textures[i].resource;
    }
  }

  Image* image = getImage(path);
  if (!image) {
    return nullptr;
  }

  Texture newTexture;
  if (!newTexture.createFromImage(*image)) {
    return nullptr;
  }

  m_textures.emplaceBack(path, nu::move(newTexture));

  return &m_textures.last().resource;
}

nu::FilePath ResourceCache::getFilePathForResourcePath(const nu::String& path) {
  return m_rootPath.append(nu::FilePath::normalizeSeparators(path));
}

}  // namespace ca

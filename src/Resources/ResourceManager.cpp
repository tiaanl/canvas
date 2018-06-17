
#include <utility>

#include "canvas/Resources/ResourceManager.h"
#include "nucleus/Streams/FileInputStream.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

namespace {

template <typename ResourceType>
ResourceRef<ResourceType> createResourceFromFile(ResourceCache<ResourceType>& cache,
                                                 const nu::String& name, const nu::FilePath& path) {
  auto resource = cache.getOrCreate(name);
  if (resource->isLoaded()) {
    return resource;
  }

  nu::FileInputStream stream{path};
  if (!stream.openedOk()) {
    LOG(Error) << "Could not load file resource: " << name << " (" << path << ")";
    return ResourceRef<ResourceType>{nullptr};
  }

  if (!resource->loadFromStream(&stream)) {
    LOG(Error) << "Could not load file resource: " << name << " (" << path << ")";
    return ResourceRef<ResourceType>{nullptr};
  }

  resource->setLoaded(true);

  return ResourceRef<ResourceType>{resource};
}

template <typename ResourceType>
ResourceRef<ResourceType> createResourceFromFile(ResourceCache<ResourceType>& cache,
                                                 const nu::FilePath& path) {
  return createResourceFromFile<ResourceType>(cache, path.getPath(), path);
}

}  // namespace

ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() = default;

void ResourceManager::createDefaults() {
#if OS(WIN)
  createResourceFromFile(m_fonts, "default", nu::FilePath{"C:\\Windows\\Fonts\\Arial.ttf"});
#elif OS(MACOSX)
  createResourceFromFile(m_fonts, "default", nu::FilePath{"/Library/Fonts/Arial.ttf"});
#endif
}

const nu::FilePath& ResourceManager::getRootPath() const {
  return m_rootPath;
}

void ResourceManager::setRootPath(const nu::FilePath& rootPath) {
  m_rootPath = rootPath;
}

ResourceRef<Image> ResourceManager::loadImage(const nu::String& path) {
  auto resource = m_images.getOrCreate(path);
  if (resource->isLoaded()) {
    return resource;
  }

  nu::FileInputStream stream{getFilePathForResource(path)};
  if (!stream.openedOk()) {
    LOG(Error) << "Could not open resource (" << path << ")";
    return {nullptr};
  }

  if (!resource->loadFromStream(&stream)) {
    LOG(Error) << "Could not load resource (" << path << ")";
    return {nullptr};
  }

  resource->setLoaded(true);

  return {resource};
}

ResourceRef<Texture> ResourceManager::loadTexture(const nu::String& path) {
  auto resource = m_textures.getOrCreate(path);
  if (resource->isLoaded()) {
    return resource;
  }

  auto image = m_images.getOrCreate(path);
  if (!resource->createFromImage(*image)) {
    LOG(Error) << "Could not create texture from image (" << path << ")";
    return {nullptr};
  }

  resource->setLoaded(true);

  return ResourceRef<Texture>{resource};
}

ResourceRef<Font> ResourceManager::loadFont(const nu::String& path) {
  return createResourceFromFile(m_fonts, getFilePathForResource(path));
}

ResourceRef<Shader> ResourceManager::getOrCreateShader(const nu::String& path) {
  return m_shaders.getOrCreate(path);
}

ResourceRef<Program> ResourceManager::getOrCreateProgram(const nu::String& path) {
  return m_programs.getOrCreate(path);
}

ResourceRef<Font> ResourceManager::getOrCreateFont(const nu::String& path) {
  return m_fonts.getOrCreate(path);
}

nu::FilePath ResourceManager::getFilePathForResource(const nu::String& path) {
  return m_rootPath.append(nu::FilePath::normalizeSeparators(path));
}

}  // namespace ca

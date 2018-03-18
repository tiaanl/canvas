
#include <utility>

#include "canvas/Resources/ResourceManager.h"
#include "nucleus/Streams/FileInputStream.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() = default;

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

  return {resource};
}

#if 0
ResourceRef<Shader> ResourceManager::getShader(const nu::String& path, Shader::ShaderType shaderType) {
  ResourceRef<Shader> resource = m_shaders.get(path);
  if (!resource.isEmpty()) {
    return resource;
  }

  nu::FileInputStream stream{getFilePathForResource(path)};
  if (!stream.openedOk()) {
    LOG(Error) << "Could not open resource (" << path << ")";
    return {nullptr};
  }

  Shader newShader{shaderType};
  if (!newShader.loadFromStream(&stream)) {
    LOG(Error) << "Could not load resource (" << path << ")";
    return {nullptr};
  }

  return m_shaders.put(path, std::move(newShader));
}

ResourceRef<Program> ResourceManager::getProgram(const nu::String& path) {
  ResourceRef<Program> resource = m_programs.get(path);
  if (!resource.isEmpty()) {
    return resource;
  }

  return nullptr;
}
#endif  // 0

ResourceRef<Shader> ResourceManager::getOrCreateShader(const nu::String& path) {
  return m_shaders.getOrCreate(path);
}

ResourceRef<Program> ResourceManager::getOrCreateProgram(const nu::String& path) {
  return m_programs.getOrCreate(path);
}

nu::FilePath ResourceManager::getFilePathForResource(const nu::String& path) {
  return m_rootPath.append(nu::FilePath::normalizeSeparators(path));
}

}  // namespace ca

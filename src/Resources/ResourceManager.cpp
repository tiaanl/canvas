
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

ResourceRef<Shader> ResourceManager::insertShader(const nu::String& path, Shader&& shader) {
  return m_shaders.put(path, std::forward<ca::Shader>(shader));
}

ResourceRef<Program> ResourceManager::insertProgram(const nu::String& path, Program&& program) {
  return m_programs.put(path, std::forward<ca::Program>(program));
}

nu::FilePath ResourceManager::getFilePathForResource(const nu::String& path) {
  return m_rootPath.append(nu::FilePath::normalizeSeparators(path));
}

}  // namespace ca

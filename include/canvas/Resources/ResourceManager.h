
#ifndef CANVAS_RESOURCES_RESOURCE_MANAGER_H_
#define CANVAS_RESOURCES_RESOURCE_MANAGER_H_

#include "canvas/Resources/ResourceCache.h"
#include "nucleus/Allocators/Allocator.h"
#include "nucleus/FilePath.h"
#include "nucleus/Macros.h"

namespace ca {

class ResourceManager {
public:
  COPY_DELETE(ResourceManager);
  MOVE_DELETE(ResourceManager);

  explicit ResourceManager(nu::Allocator* allocator);

  const nu::FilePath& getRootPath() const;
  void setRootPath(const nu::FilePath& rootPath);

  ResourceRef<Image> getImage(const nu::String& path);
  ResourceRef<Texture> getTexture(const nu::String& path);
  // ResourceRef<Shader> getShader(const nu::String& path, Shader::ShaderType shaderType);

private:
  nu::FilePath getFilePathForResource(const nu::String& path);

  nu::FilePath m_rootPath;

  ResourceCache<Image> m_images;
  ResourceCache<Texture> m_textures;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_MANAGER_H_

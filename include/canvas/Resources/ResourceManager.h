
#ifndef CANVAS_RESOURCES_RESOURCE_MANAGER_H_
#define CANVAS_RESOURCES_RESOURCE_MANAGER_H_

#include "canvas/Rendering/Program.h"
#include "canvas/Rendering/Shader.h"
#include "canvas/Resources/ResourceCache.h"
#include "nucleus/Allocators/Allocator.h"
#include "nucleus/FilePath.h"
#include "nucleus/Macros.h"
#include "nucleus/Memory/Ptr.h"

namespace ca {

class ResourceManager {
public:
  COPY_DELETE(ResourceManager);
  MOVE_DELETE(ResourceManager);

  ResourceManager();
  ~ResourceManager();

  const nu::FilePath& getRootPath() const;
  void setRootPath(const nu::FilePath& rootPath);

  ResourceRef<Image> getImage(const nu::String& path);
  ResourceRef<Texture> getTexture(const nu::String& path);
  ResourceRef<Shader> getShader(const nu::String& path, Shader::ShaderType shaderType);
  ResourceRef<Program> getProgram(const nu::String& path);

  ResourceRef<Shader> getOrCreateShader(const nu::String& path, Shader::ShaderType shaderType);
  ResourceRef<Program> getOrCreateProgram(const nu::String& path);

private:
  nu::FilePath getFilePathForResource(const nu::String& path);

  nu::FilePath m_rootPath;

  ResourceCache<Image> m_images;
  ResourceCache<Texture> m_textures;
  ResourceCache<Shader> m_shaders;
  ResourceCache<Program> m_programs;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_MANAGER_H_

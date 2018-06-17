
#ifndef CANVAS_RESOURCES_RESOURCE_MANAGER_H_
#define CANVAS_RESOURCES_RESOURCE_MANAGER_H_

#include "canvas/Rendering/Font.h"
#include "canvas/Rendering/Program.h"
#include "canvas/Rendering/Shader.h"
#include "canvas/Resources/ResourceCache.h"
#include "nucleus/Allocators/Allocator.h"
#include "nucleus/FilePath.h"
#include "nucleus/Macros.h"

namespace ca {

class ResourceManager {
public:
  COPY_DELETE(ResourceManager);
  MOVE_DELETE(ResourceManager);

  ResourceManager();
  ~ResourceManager();

  // Create a set of default resources.
  void createDefaults();

  const nu::FilePath& getRootPath() const;
  void setRootPath(const nu::FilePath& rootPath);

  ResourceRef<Image> loadImage(const nu::String& path);
  ResourceRef<Texture> loadTexture(const nu::String& path);
  ResourceRef<Font> loadFont(const nu::String& path);

  ResourceRef<Shader> getOrCreateShader(const nu::String& path);
  ResourceRef<Program> getOrCreateProgram(const nu::String& path);
  ResourceRef<Font> getOrCreateFont(const nu::String& path);

private:
  nu::FilePath getFilePathForResource(const nu::String& path);

  nu::FilePath m_rootPath;

  ResourceCache<Image> m_images;
  ResourceCache<Texture> m_textures;
  ResourceCache<Shader> m_shaders;
  ResourceCache<Program> m_programs;
  ResourceCache<Font> m_fonts;
};

}  // namespace ca

#endif  // CANVAS_RESOURCES_RESOURCE_MANAGER_H_

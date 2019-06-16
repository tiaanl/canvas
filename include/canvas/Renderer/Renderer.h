
#ifndef CANVAS_RENDERER_RENDERER_H_
#define CANVAS_RENDERER_RENDERER_H_

#include "canvas/Renderer/Command.h"
#include "canvas/Renderer/Types.h"
#include "canvas/Renderer/VertexDefinition.h"
#include "canvas/Utils/Image.h"
#include "canvas/Utils/ShaderSource.h"
#include "canvas/Utils/Size.h"
#include "nucleus/Containers/DynamicArray.h"

namespace ca {

class Renderer {
public:
  Renderer() = default;
  ~Renderer() = default;

  ProgramId createProgram(const ShaderSource& vertexShader, const ShaderSource& fragmentShader);
  VertexBufferId createVertexBuffer(const VertexDefinition& bufferDefinition, void* data,
                                    MemSize dataSize);
  IndexBufferId createIndexBuffer(ComponentType componentType, void* data, MemSize dataSize);
  TextureId createTexture(const Image& image);

  void pushCommand(const Command& command);

  void beginFrame();
  void endFrame();

private:
  DELETE_COPY_AND_MOVE(Renderer);

  struct ProgramData {
    U32 id;
  };

  struct VertexBufferData {
    U32 id;
  };

  struct IndexBufferData {
    U32 id;
    ComponentType componentType;
  };

  struct TextureData {
    U32 id;
    Size<I32> size;
  };

  void processCommand(const ClearBuffersData& data);
  void processCommand(const DrawData& data);

  nu::DynamicArray<TextureData> m_textures;
  nu::DynamicArray<VertexBufferData> m_vertexBuffers;
  nu::DynamicArray<IndexBufferData> m_indexBuffers;
  nu::DynamicArray<ProgramData> m_programs;

  nu::DynamicArray<Command> m_commands;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_RENDERER_H_

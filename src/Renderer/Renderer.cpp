
#include "canvas/Renderer/Renderer.h"

#include "canvas/OpenGL.h"
#include "canvas/Renderer/VertexDefinition.h"
#include "canvas/Utils/GLCheck.h"
#include "canvas/Utils/Image.h"
#include "canvas/Utils/ShaderSource.h"

namespace ca {

namespace {

U32 getOglType(ComponentType type) {
  switch (type) {
    case ComponentType::Float32:
      return GL_FLOAT;

    case ComponentType::Signed8:
      return GL_BYTE;

    case ComponentType::Unsigned8:
      return GL_UNSIGNED_BYTE;

    case ComponentType::Signed16:
      return GL_SHORT;

    case ComponentType::Unsigned16:
      return GL_UNSIGNED_SHORT;

    case ComponentType::Signed32:
      return GL_INT;

    case ComponentType::Unsigned32:
      return GL_UNSIGNED_INT;

    default:
      DCHECK(false) << "Invalid component type.";
      return 0;
  }
}

bool compileShaderSource(const ShaderSource& source, U32 shaderType, U32* idOut) {
  U32 id = glCreateShader(shaderType);

  auto s = source.getSource();

  // Set the source of the shader.
  const GLchar* src = s.getData();
  const GLint length = static_cast<const GLint>(s.getLength());
  GL_CHECK(glShaderSource(id, 1, &src, &length));
  GL_CHECK(glCompileShader(id));

  GLint success;
  GL_CHECK(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
  if (success == GL_FALSE) {
    // Get the size of the log messages.
    GLint logSize = 0;
    GL_CHECK(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logSize));

    nu::DynamicArray<GLchar> log;
    log.resize(static_cast<MemSize>(logSize));
    GL_CHECK(glGetShaderInfoLog(id, logSize, &logSize, log.getData()));

    LOG(Error) << log.getData();

    return false;
  }

  *idOut = id;
  return true;
}

}  // namespace

ProgramId Renderer::createProgram(const ShaderSource& vertexShader,
                                  const ShaderSource& fragmentShader) {
  ProgramData result;

  result.id = glCreateProgram();

  // Compile and attach the shaders.
  U32 vertexShaderId, fragmentShaderId;

  if (!compileShaderSource(vertexShader, GL_VERTEX_SHADER, &vertexShaderId)) {
    return ProgramId{kInvalidResourceId};
  }

  if (!compileShaderSource(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderId)) {
    return ProgramId{kInvalidResourceId};
  }

  // Attach the shaders.
  GL_CHECK(glAttachShader(result.id, vertexShaderId));
  GL_CHECK(glAttachShader(result.id, fragmentShaderId));

  // Link the program.
  GL_CHECK(glLinkProgram(result.id));

  // Release the references to the shaders.
  GL_CHECK(glDeleteShader(fragmentShaderId));
  GL_CHECK(glDeleteShader(vertexShaderId));

  GLint success;
  glGetProgramiv(result.id, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    // Check if there were any information.
    GLint infoLength = 0;
    GL_CHECK(glGetProgramiv(result.id, GL_INFO_LOG_LENGTH, &infoLength));

    if (infoLength > 0) {
      nu::String buffer;
      buffer.resize(infoLength);
      GL_CHECK(
          glGetProgramInfoLog(result.id, infoLength, &infoLength, (GLchar*)buffer.getRawBytes()));
      if (infoLength) {
        LOG(Error) << buffer;
      }
      return ProgramId{kInvalidResourceId};
    } else {
      LOG(Warning) << "Program not linked and no information available!";
    }
  }

  m_programs.pushBack(result);
  return ProgramId{m_programs.getSize() - 1};
}

VertexBufferId Renderer::createVertexBuffer(const VertexDefinition& vertexDefinition, void* data,
                                            MemSize dataSize) {
  VertexBufferData result;

  // Create a vertex array object and bind it.
  GL_CHECK(glGenVertexArrays(1, &result.id));
  GL_CHECK(glBindVertexArray(result.id));

  // Create a buffer with our vertex data.
  GLuint bufferId;
  GL_CHECK(glGenBuffers(1, &bufferId));
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, bufferId));
  GL_CHECK(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));

  // Create each attribute.

  U32 componentNumber = 0;
  U32 offset = 0;
  for (const auto& attr : vertexDefinition.getAttributes()) {
    glVertexAttribPointer(componentNumber, U32(attr.getCount()), getOglType(attr.getType()),
                          GL_FALSE, vertexDefinition.getStride(), (GLvoid*)((U8*)0 + offset));
    glEnableVertexAttribArray(componentNumber);

    ++componentNumber;
    offset += attr.getSizeInBytes();
  }

  // Reset the current VAO bind.
  GL_CHECK(glBindVertexArray(0));

  // We can delete the buffer here, because the VAO is holding a reference to it.
  glDeleteBuffers(1, &bufferId);

#if 0
  result.numComponents = U32(dataSize / componentSize);
#endif  // 0

  m_vertexBuffers.pushBack(result);
  return VertexBufferId{m_vertexBuffers.getSize() - 1};
}

IndexBufferId Renderer::createIndexBuffer(ComponentType componentType, void* data,
                                          MemSize dataSize) {
  GLuint bufferId;
  GL_CHECK(glGenBuffers(1, &bufferId));
  GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId));
  GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));

  m_indexBuffers.emplaceBack(bufferId, componentType);
  return IndexBufferId{m_indexBuffers.getSize() - 1};
}

TextureId Renderer::createTexture(const Image& image) {
  TextureData result;

  GL_CHECK(glGenTextures(1, &result.id));

  result.size = image.getSize();

  // Bind the texture.
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, result.id));

  // Upload the image data.
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, result.size.width, result.size.height, 0,
                        GL_RGBA, GL_UNSIGNED_BYTE, image.getData().getData()));

  // Set the texture clamping.
  const bool smooth = false;
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST));

  // Unbind the texture we were working on.
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

  // Create the texture in the buffer.
  m_textures.pushBack(result);

  return TextureId{m_textures.getSize() - 1};
}

UniformId Renderer::createUniform(const nu::StringView& name, ComponentType componentType,
                                  MemSize componentCount) {
  UniformData uniformData = {name, componentType, componentCount};
  m_uniforms.pushBack(uniformData);
  return UniformId{m_uniforms.getSize() - 1};
}

void Renderer::pushCommand(const Command& command) {
  m_commands.pushBack(command);
}

void Renderer::beginFrame() {
  m_commands.clear();
}

void Renderer::endFrame() {
  for (auto& command : m_commands) {
    switch (command.type) {
      case CommandType::ClearBuffers:
        processCommand(command.clearBuffersData);
        break;

      case CommandType::Draw:
        processCommand(command.drawData);
        break;
    }
  }
}

void Renderer::processCommand(const ClearBuffersData& data) {
  GL_CHECK(glClearColor(data.color.r, data.color.g, data.color.b, data.color.a));
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::processCommand(const DrawData& data) {
  auto& programData = m_programs[data.programId.id];
  GL_CHECK(glUseProgram(programData.id));

  auto& vertexBufferData = m_vertexBuffers[data.vertexBufferId.id];
  GL_CHECK(glBindVertexArray(vertexBufferData.id));

  auto& indexBufferData = m_indexBuffers[data.indexBufferId.id];
  GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferData.id));

  if (isValid(data.textureId)) {
    auto& textureData = m_textures[data.textureId.id];
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureData.id));
  }

  U32 oglType = getOglType(indexBufferData.componentType);

  // Process uniforms.
  for (const auto& uniformEntry : data.uniforms) {
    const auto& uniformData = m_uniforms[uniformEntry.uniformId.id];
    U32 location = glGetUniformLocation(programData.id, uniformData.name.getData());
    GL_CHECK(glUniform1fv(location, uniformEntry.values.getSize(), uniformEntry.values.getData()));
  }

  U32 drawType = GL_TRIANGLES;
  switch (data.drawType) {
    case DrawType::Triangles:
      drawType = GL_TRIANGLES;
      break;

    case DrawType::TriangleStrip:
      drawType = GL_TRIANGLE_FAN;
      break;

    case DrawType::TriangleFan:
      drawType = GL_TRIANGLE_FAN;
      break;

    default:
      DCHECK(false) << "Invalid draw type";
      break;
  }

  GL_CHECK(glDrawElements(drawType, data.numIndices, oglType, nullptr));
}

}  // namespace ca


#include "canvas/Renderer/RenderContext.h"

#include "canvas/OpenGL.h"
#include "canvas/Utils/GLCheck.h"
#include "canvas/Utils/Image.h"
#include "canvas/Utils/ShaderSource.h"

namespace ca {

namespace {

static U32 kComponentTypeMap[] = {
    GL_FLOAT,           // Float32
    GL_BYTE,            // Signed8
    GL_UNSIGNED_BYTE,   // Unsigned8
    GL_SHORT,           // Signed16
    GL_UNSIGNED_SHORT,  // Unsigned16
    GL_INT,             // Signed32
    GL_UNSIGNED_INT,    // Unsigned32
};

bool compileShaderSource(const ShaderSource& source, U32 shaderType, U32* idOut) {
  U32 id = glCreateShader(shaderType);

  nu::StringView s = source.getSource();

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

TextureId RenderContext::createTexture(const Image& image) {
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

  return m_textures.getSize() - 1;
}

ProgramId RenderContext::createProgram(const ShaderSource& vertexShader,
                                       const ShaderSource& fragmentShader) {
  ProgramData result;

  result.id = glCreateProgram();

  // Compile and attach the shaders.
  U32 vertexShaderId, fragmentShaderId;

  if (!compileShaderSource(vertexShader, GL_VERTEX_SHADER, &vertexShaderId)) {
    return 0;
  }

  if (!compileShaderSource(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderId)) {
    return 0;
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
      return false;
    } else {
      LOG(Warning) << "Program not linked and no information available!";
    }
  }

  m_programs.pushBack(result);
  return m_programs.getSize() - 1;
}

GeometryId RenderContext::createGeometryInternal(const BufferDefinition& bufferDefinition,
                                                 void* data, MemSize dataSize,
                                                 MemSize componentSize) {
#if BUILD(DEBUG)
  U32 totalComponents = 0;
  for (auto& attr : bufferDefinition.getAttributes()) {
    totalComponents += attr.numberOfComponents;
  }
  DCHECK(totalComponents == bufferDefinition.getComponentsPerVertex());
#endif  // BUILD(DEBUG)

  GeometryData result;

  // Create a vertex array object and bind it.
  GL_CHECK(glGenVertexArrays(1, &result.id));
  GL_CHECK(glBindVertexArray(result.id));

  // Create a buffer with our vertex data.
  GLuint bufferId;
  GL_CHECK(glGenBuffers(1, &bufferId));
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, bufferId));
  GL_CHECK(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));

  // Create each attribute.
  const auto& attributes = bufferDefinition.getAttributes();
  MemSize stride = bufferDefinition.getComponentsPerVertex() * componentSize;
  MemSize offset = 0;
  for (MemSize i = 0; i < attributes.getSize(); ++i) {
    const auto& attribute = attributes[i];

    glVertexAttribPointer(i, attribute.numberOfComponents,
                          kComponentTypeMap[static_cast<U32>(attribute.componentType)], GL_FALSE,
                          stride, (GLvoid*)offset);
    glEnableVertexAttribArray(i);

    offset += attribute.numberOfComponents * componentSize;
  }

  // Reset the current VAO bind.
  GL_CHECK(glBindVertexArray(0));

  // We can delete the buffer here, because the VAO is holding a reference to it.
  glDeleteBuffers(1, &bufferId);

  result.numComponents = dataSize / componentSize;

  m_geometries.pushBack(result);
  return m_geometries.getSize() - 1;
}

}  // namespace ca

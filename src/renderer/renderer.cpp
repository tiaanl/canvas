
#include "canvas/renderer/renderer.h"

#include "canvas/opengl.h"
#include "canvas/renderer/vertex_definition.h"
#include "canvas/utils/gl_check.h"
#include "canvas/utils/shader_source.h"
#include "nucleus/logging.h"

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
  const GLchar* src = s.data();
  GLint length = static_cast<GLint>(s.length());
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
    GL_CHECK(glGetShaderInfoLog(id, logSize, &logSize, log.data()));

    LOG(Error) << log.data();

    return false;
  }

  *idOut = id;
  return true;
}

U32 mode_from_draw_type(DrawType draw_type) {
  U32 mode = GL_TRIANGLES;
  switch (draw_type) {
    case DrawType::Points:
      mode = GL_POINTS;
      break;

    case DrawType::Lines:
      mode = GL_LINES;
      break;

    case DrawType::LineStrip:
      mode = GL_LINE_STRIP;
      break;

    case DrawType::Triangles:
      mode = GL_TRIANGLES;
      break;

    case DrawType::TriangleStrip:
      mode = GL_TRIANGLE_STRIP;
      break;

    case DrawType::TriangleFan:
      mode = GL_TRIANGLE_FAN;
      break;

    default:
      DCHECK(false) << "Invalid draw type";
      break;
  }

  return mode;
}

}  // namespace

Renderer::Renderer() = default;

Renderer::~Renderer() = default;

ProgramId Renderer::create_program(const ShaderSource& vertexShader,
                                   const ShaderSource& fragmentShader) {
  return create_program(vertexShader, {}, fragmentShader);
}

ProgramId Renderer::create_program(const ShaderSource& vertexShader,
                                   const ShaderSource& geometryShader,
                                   const ShaderSource& fragmentShader) {
  bool has_geometry_shader_ = !geometryShader.getSource().empty();

  ProgramData result;

  result.id = glCreateProgram();

  // Compile and attach the shaders.
  U32 vertexShaderId, geometryShaderId, fragmentShaderId;

  if (!compileShaderSource(vertexShader, GL_VERTEX_SHADER, &vertexShaderId)) {
    return {};
  }

  if (has_geometry_shader_) {
    if (!compileShaderSource(geometryShader, GL_GEOMETRY_SHADER, &geometryShaderId)) {
      return {};
    }
  }

  if (!compileShaderSource(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderId)) {
    return {};
  }

  // Attach the shaders.
  GL_CHECK(glAttachShader(result.id, vertexShaderId));
  if (has_geometry_shader_) {
    GL_CHECK(glAttachShader(result.id, geometryShaderId));
  }
  GL_CHECK(glAttachShader(result.id, fragmentShaderId));

  // Link the program.
  GL_CHECK(glLinkProgram(result.id));

  // Release the references to the shaders.
  GL_CHECK(glDeleteShader(fragmentShaderId));
  if (has_geometry_shader_) {
    GL_CHECK(glDeleteShader(geometryShaderId));
  }
  GL_CHECK(glDeleteShader(vertexShaderId));

  GLint success;
  glGetProgramiv(result.id, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    // Check if there were any information.
    GLint infoLength = 0;
    GL_CHECK(glGetProgramiv(result.id, GL_INFO_LOG_LENGTH, &infoLength));

    if (infoLength > 0) {
      nu::DynamicString buffer;
      buffer.resize(infoLength);
      GL_CHECK(glGetProgramInfoLog(result.id, infoLength, &infoLength, (GLchar*)buffer.data()));
      if (infoLength) {
        LOG(Error) << buffer.view();
      }
      return {};
    } else {
      LOG(Warning) << "Program not linked and no information available!";
    }
  }

  programs_.pushBack(result);

  return ProgramId{programs_.size() - 1};
}

void Renderer::delete_program(ProgramId programId) {
  auto programData = programs_[programId.id];
  glDeleteProgram(programData.id);
}

VertexBufferId Renderer::create_vertex_buffer(const VertexDefinition& bufferDefinition,
                                              const void* data, MemSize dataSize) {
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
  for (auto& attr : bufferDefinition) {
    glVertexAttribPointer(componentNumber, U32(attr.getCount()), getOglType(attr.getType()),
                          GL_FALSE, bufferDefinition.getStride(),
                          (GLvoid*)(static_cast<MemSize>(offset)));
    glEnableVertexAttribArray(componentNumber);

    ++componentNumber;
    offset += attr.getSizeInBytes();
  }

  // Reset the current VAO bind.
  GL_CHECK(glBindVertexArray(0));

  // We can delete the buffer here, because the VAO is holding a reference to it.
  // GL_CHECK(glDeleteBuffers(1, &bufferId));

#if 0
  auto pushBackResult =
      m_vertexBuffers.constructBack([&result](VertexBufferData* storage) { *storage = result; });
#else
  auto pushBackResult = vertex_buffers_.emplaceBack(result);
#endif

  return VertexBufferId{pushBackResult.index()};
}

void Renderer::vertex_buffer_data(VertexBufferId id, void* data, MemSize dataSize) {
  auto vertexBufferData = vertex_buffers_[id.id];

  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferData.id));
  GL_CHECK(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));
}

void Renderer::delete_vertex_buffer(VertexBufferId id) {
  auto data = vertex_buffers_[id.id];

  GL_CHECK(glDeleteVertexArrays(1, &data.id));
}

IndexBufferId Renderer::create_index_buffer(ComponentType componentType, const void* data,
                                            MemSize dataSize) {
  GLuint bufferId;
  GL_CHECK(glGenBuffers(1, &bufferId));
  GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId));
  GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));

#if 0
  auto pushBackResult =
      m_indexBuffers.constructBack([&bufferId, &componentType](IndexBufferData* storage) {
        storage->id = bufferId;
        storage->componentType = componentType;
      });
#else
  auto pushBackResult = index_buffers_.emplaceBack(bufferId, componentType);
#endif

  return IndexBufferId{pushBackResult.index()};
}

void Renderer::index_buffer_data(IndexBufferId id, void* data, MemSize dataSize) {
  auto indexBufferData = index_buffers_[id.id];

  GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferData.id));
  GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));
}

void Renderer::delete_index_buffer(IndexBufferId id) {
  auto indexBufferData = index_buffers_[id.id];

  GL_CHECK(glDeleteBuffers(1, &indexBufferData.id));
}

TextureId Renderer::create_texture(TextureFormat format, const fl::Size& size, const void* data,
                                   MemSize dataSize, bool smooth) {
  if (format == TextureFormat::Unknown) {
    LOG(Warning) << "Can not create texture from image with unknown format.";
    return {};
  }

  TextureData result;

  result.size = size;

  const GLint internalFormat = GL_RGBA;

  GLint glFormat = GL_RGBA;
  U32 components;

  // Upload the image data.
  switch (format) {
    case TextureFormat::RGB:
      glFormat = GL_RGBA;
      components = 3;
      break;

    case TextureFormat::RGBA:
      glFormat = GL_RGBA;
      components = 4;
      break;

    case TextureFormat::Alpha:
      glFormat = GL_RED;
      components = 1;
      break;

    default:
      components = 0;
      NOTREACHED();
      break;
  }

  if (components * size.width * size.height > dataSize) {
    LOG(Warning) << "The provided data is not enough to fill the texture rectangle. (size = "
                 << size << ", dataSize = " << dataSize << ")";
    return {};
  }

  GL_CHECK(glGenTextures(1, &result.id));

  // Bind the texture.
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, result.id));

  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, result.size.width, result.size.height, 0,
                        glFormat, GL_UNSIGNED_BYTE, data));

  // Set the texture clamping.
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST));

  // Unbind the texture we were working on.
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

  // Create the texture in the buffer.
#if 0
  auto r = m_textures.constructBack([&result](TextureData* storage) {
    storage->id = result.id;
    storage->size = result.size;
  });
#else
  auto r = textures_.emplaceBack(result.id, result.size);
#endif  // 0

  return TextureId{r.index()};
}

UniformId Renderer::create_uniform(const nu::StringView& name) {
  UniformData uniformData = {name};
  uniforms_.pushBack(uniformData);
  return UniformId{uniforms_.size() - 1};
}

PipelineBuilder Renderer::create_pipeline_builder() const {
  return PipelineBuilder{const_cast<Renderer*>(this)};
}

void Renderer::resize(const fl::Size& size) {
  size_ = size;
  GL_CHECK(glViewport(0, 0, size.width, size.height));
}

void Renderer::begin_frame() {
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::end_frame() {}

void Renderer::clear(const Color& color) {
  GL_CHECK(glClearColor(color.r, color.g, color.b, color.a));
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(DrawType draw_type, U32 vertex_offset, U32 vertex_count, ProgramId program_id,
                    VertexBufferId vertex_buffer_id, const TextureSlots& textures,
                    const UniformBuffer& uniforms) {
  pre_draw(program_id, textures, uniforms);

  if (!vertex_buffer_id.is_valid()) {
    LOG(Error) << "Draw command without vertex buffer.";
    return;
  }

  auto& vertexBufferData = vertex_buffers_[vertex_buffer_id.id];
  GL_CHECK(glBindVertexArray(vertexBufferData.id));

  auto mode = mode_from_draw_type(draw_type);
  GL_CHECK(glDrawArrays(mode, vertex_offset, vertex_count));

  post_draw();
}

void Renderer::draw(DrawType draw_type, U32 index_count, ProgramId program_id,
                    VertexBufferId vertex_buffer_id, IndexBufferId index_buffer_id,
                    const TextureSlots& textures, const UniformBuffer& uniforms) {
  pre_draw(program_id, textures, uniforms);

  if (!vertex_buffer_id.is_valid()) {
    LOG(Error) << "Draw command without vertex buffer.";
    return;
  }

  if (!index_buffer_id.is_valid()) {
    LOG(Error) << "Draw command without index buffer.";
    return;
  }

  auto& vertexBufferData = vertex_buffers_[vertex_buffer_id.id];
  GL_CHECK(glBindVertexArray(vertexBufferData.id));

  auto& indexBufferData = index_buffers_[index_buffer_id.id];
  GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferData.id));

  U32 oglType = getOglType(indexBufferData.component_type);

  U32 mode = mode_from_draw_type(draw_type);

  GL_CHECK(glDrawElements(mode, index_count, oglType, nullptr));

  post_draw();
}

void Renderer::pre_draw(ProgramId program_id, const TextureSlots& textures,
                        const UniformBuffer& uniforms) {
  if (!program_id.is_valid()) {
    LOG(Error) << "Draw command without program.";
    return;
  }

  auto& programData = programs_[program_id.id];
  GL_CHECK(glUseProgram(programData.id));

  textures.for_each_valid_slot([&](U32 slot, TextureId texture_id) {
    auto& textureData = textures_[texture_id.id];
    GL_CHECK(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureData.id));
  });

  // Process uniforms.
  uniforms.apply([&](UniformId uniformId, ComponentType type, U32 count, const void* values) {
    const auto& uniformData = uniforms_[uniformId.id];
    char buf[64];
    std::strncpy(buf, uniformData.name.data(), uniformData.name.length());
    buf[uniformData.name.length()] = '\0';
    I32 location = glGetUniformLocation(programData.id, buf);
    if (location == -1) {
      LOG(Warning) << "Could not get location for uniform: " << buf;
      return;
    }

    if (type == ComponentType::Float32) {
      switch (count) {
        case 1:
          GL_CHECK(glUniform1fv(location, 1, (GLfloat*)values));
          break;

        case 2:
          GL_CHECK(glUniform2fv(location, 1, (GLfloat*)values));
          break;

        case 3:
          GL_CHECK(glUniform3fv(location, 1, (GLfloat*)values));
          break;

        case 4:
          GL_CHECK(glUniform4fv(location, 1, (GLfloat*)values));
          break;

        case 16:
          GL_CHECK(glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)values));
          break;

        default:
          DCHECK(false) << "Invalid uniform size.";
          break;
      }
    } else if (type == ComponentType::Signed32) {
      DCHECK(count == 1);
      GL_CHECK(glUniform1i(location, *(GLint*)values));
    } else if (type == ComponentType::Unsigned32) {
      DCHECK(count == 1);
      GL_CHECK(glUniform1ui(location, *(GLuint*)values));
    } else {
      DCHECK(false) << "Unsupported uniform component type.";
    }
  });

  if (render_state_.depth_test()) {
    GL_CHECK(glEnable(GL_DEPTH_TEST));
  }

  if (render_state_.cull_face()) {
    GL_CHECK(glEnable(GL_CULL_FACE));
  }

  GL_CHECK(glEnable(GL_BLEND));
  GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::post_draw() {
  for (U32 i = 0; i < TextureSlots::MAX_TEXTURE_SLOTS; ++i) {
    GL_CHECK(glActiveTexture(GL_TEXTURE0 + i));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
  }

  GL_CHECK(glDisable(GL_BLEND));

  if (render_state_.cull_face()) {
    GL_CHECK(glDisable(GL_CULL_FACE));
  }

  if (render_state_.depth_test()) {
    GL_CHECK(glDisable(GL_DEPTH_TEST));
  }
}

}  // namespace ca

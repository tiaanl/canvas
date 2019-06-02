
#include "canvas/Renderer/RenderGroup.h"

#include "canvas/OpenGL.h"
#include "canvas/Renderer/RenderCommand.h"
#include "canvas/Renderer/Renderer.h"
#include "canvas/Utils/GLCheck.h"
#include "nucleus/Logging.h"

namespace ca {

void RenderGroup::render(Renderer* renderContext) {
  setUpMatrices();

  for (auto& command : m_commands) {
    switch (command.type) {
      case RenderCommandType::ClearColorBuffer:
        processData(renderContext, &command.clearColorBufferData);
        break;

      case RenderCommandType::RenderGeometry:
        processData(renderContext, &command.renderGeometryData);
        break;

      default:
        DCHECK(false);
        break;
    }
  }
}

void RenderGroup::clearColorBuffer(const Color& color) {
  RenderCommand command;

  command.type = RenderCommandType::ClearColorBuffer;
  command.clearColorBufferData.color = color;

  m_commands.pushBack(command);
}

void RenderGroup::clearDepthBuffer(F32 depth) {
  RenderCommand command;

  command.type = RenderCommandType::ClearDepthBuffer;
  command.clearDepthBufferData.depth = depth;

  m_commands.pushBack(command);
}

void RenderGroup::renderGeometry(GeometryId geometryId, TextureId textureId, ProgramId programId) {
  RenderCommand command;

  command.type = RenderCommandType::RenderGeometry;
  command.renderGeometryData.geometryId = geometryId;
  command.renderGeometryData.textureId = textureId;
  command.renderGeometryData.programId = programId;

  m_commands.pushBack(command);
}

void RenderGroup::setUpMatrices() {
  // TODO: Kill this
  m_projection = RenderGroupProjection::Orthographic;
}

// static
void RenderGroup::processData(Renderer*, ClearColorBufferData* data) {
  glClearColor(data->color.r, data->color.g, data->color.b, data->color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

// static
void RenderGroup::processData(Renderer* renderer, RenderGeometryData* data) {
  auto& programData = renderer->m_programs[data->programId];
  auto& geometryData = renderer->m_geometries[data->geometryId];
  auto& textureData = renderer->m_textures[data->textureId];

  GL_CHECK(glUseProgram(programData.id));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureData.id));
  GL_CHECK(glBindVertexArray(geometryData.id));
  GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, geometryData.numComponents));
}

}  // namespace ca

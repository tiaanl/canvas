
#include "canvas/Renderer/Encoder.h"

#include "canvas/Renderer/Command.h"
#include "canvas/Renderer/Renderer.h"

namespace ca {

void CommandBuilder::submit() {
  m_renderer->pushCommand(m_command);
}

void DrawCommandBuilder::submit() {
  DCHECK(isValid(m_command.drawData.programId)) << "Program must be specified";
  DCHECK(isValid(m_command.drawData.vertexBufferId)) << "Vertex buffer must be specified";
  DCHECK(isValid(m_command.drawData.indexBufferId)) << "Index buffer must be specified";
  DCHECK(m_command.drawData.numIndices > 0) << "numIndices must be specified";

  CommandBuilder::submit();
}

}  // namespace ca

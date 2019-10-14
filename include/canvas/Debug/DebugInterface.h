#ifndef CANVAS_DEBUG_DEBUG_INTERFACE_H_
#define CANVAS_DEBUG_DEBUG_INTERFACE_H_

#include "nucleus/Macros.h"

namespace ca {

class Renderer;

class DebugInterface {
public:
  explicit DebugInterface(Renderer* renderer);

  auto render() -> void;

private:
  DELETE_COPY_AND_MOVE(DebugInterface);

  Renderer* m_renderer;
};

}  // namespace ca

#endif  // CANVAS_DEBUG_DEBUG_INTERFACE_H_

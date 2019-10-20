#ifndef CANVAS_DEBUG_PROFILE_PRINTER_H_
#define CANVAS_DEBUG_PROFILE_PRINTER_H_

#include "canvas/Math/Mat4.h"
#include "canvas/Utils/Pos.h"
#include "nucleus/Profiling.h"

namespace ca {

class Renderer;
class DebugFont;

class ProfilePrinter {
public:
  ProfilePrinter(Renderer* renderer, DebugFont* debugFont, const Mat4& transform);

  auto draw(nu::detail::ProfileMetrics::Block* root, const Pos& position) -> void;

private:
  Renderer* m_renderer;
  DebugFont* m_debugFont;
  Mat4 m_transform;

  Pos m_cursor;
};

}  // namespace ca

#endif  // CANVAS_DEBUG_PROFILE_PRINTER_H_

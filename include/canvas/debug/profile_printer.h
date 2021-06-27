#pragma once

#include "floats/mat4.h"
#include "floats/pos.h"
#include "nucleus/profiling.h"

namespace ca {

#if 0

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

#endif  // 0

}  // namespace ca

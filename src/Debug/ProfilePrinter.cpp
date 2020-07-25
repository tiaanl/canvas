#include "canvas/Debug/ProfilePrinter.h"

#include "canvas/Debug/DebugFont.h"

namespace ca {

#if 0

ProfilePrinter::ProfilePrinter(Renderer* renderer, DebugFont* debugFont, const Mat4& transform)
  : m_renderer{renderer}, m_debugFont{debugFont}, m_transform{transform} {}

auto ProfilePrinter::draw(nu::detail::ProfileMetrics::Block* root, const Pos& position) -> void {
  m_cursor = position;
}

#endif  // 0

}  // namespace ca

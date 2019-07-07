
#include "canvas/Math/Transform.h"
#include "nucleus/Testing.h"

namespace ca {

TEST_CASE("orthographic projection") {
  auto ortho = orthographicProjection(0, 0, 1600, 900, 0.1f, 1000.0f);
}

}  // namespace ca

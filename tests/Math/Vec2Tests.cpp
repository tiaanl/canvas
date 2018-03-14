
#include "canvas/Math/Vec2.h"
#include "nucleus/Testing.h"

namespace ca {

TEST_CASE("Vec2Basic") {
  Vec2 v1;
  REQUIRE(v1.x == 0.f);
  REQUIRE(v1.y == 0.f);

  Vec2 v3{1.f, 2.f};
  REQUIRE(v3.x == 1.f);
  REQUIRE(v3.y == 2.f);
}

}  // namespace ca

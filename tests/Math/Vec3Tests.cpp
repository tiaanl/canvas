
#include "canvas/Math/Vec3.h"
#include "nucleus/Testing.h"

namespace ca {

TEST_CASE("Vec3Basic") {
  Vec3 v1;
  REQUIRE(v1.x == 0.f);
  REQUIRE(v1.y == 0.f);
  REQUIRE(v1.z == 0.f);

  Vec3 v2{1.f, 2.f, 3.f};
  REQUIRE(v2.x == 1.f);
  REQUIRE(v2.y == 2.f);
  REQUIRE(v2.z == 3.f);
}

}  // namespace ca


#include "canvas/Math/Vec4.h"
#include "nucleus/Testing.h"

namespace ca {

TEST_CASE("Vec4Basic") {
  Vec4 v1;
  REQUIRE(v1.x == 0.f);
  REQUIRE(v1.y == 0.f);
  REQUIRE(v1.z == 0.f);
  REQUIRE(v1.w == 0.f);

  Vec4 v2{1.f, 2.f, 3.f, 4.f};
  REQUIRE(v2.x == 1.f);
  REQUIRE(v2.y == 2.f);
  REQUIRE(v2.z == 3.f);
  REQUIRE(v2.w == 4.f);
}

}  // namespace ca

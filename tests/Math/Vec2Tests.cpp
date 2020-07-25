
#include "canvas/Math/Vec2.h"
#include "nucleus/Testing.h"

namespace ca {

TEST_CASE("Vec2 construct") {
  auto v1 = Vec2{1.0f, 2.0f};
  CHECK(v1.x == 1.0f);
  CHECK(v1.y == 2.0f);
}

TEST_CASE("Vec2 operators") {
  auto v1 = Vec2{1.0f, 2.0f};
  auto v2 = Vec2{3.0f, 4.0f};

  SECTION("add") {
    auto r = v1 + v2;
    CHECK(r.x == 4.0f);
    CHECK(r.y == 6.0f);

    v1 += v2;
    CHECK(v1.x == 4.0f);
    CHECK(v1.y == 6.0f);
  }

  SECTION("subtract") {
    auto r = v1 - v2;
    CHECK(r.x == -2.0f);
    CHECK(r.y == -2.0f);

    v1 -= v2;
    CHECK(v1.x == -2.0f);
    CHECK(v1.y == -2.0f);
  }

  SECTION("multiply") {
    auto r = v1 * 5.0f;
    CHECK(r.x == 5.0f);
    CHECK(r.y == 10.0f);

    v1 *= 5.0f;
    CHECK(v1.x == 5.0f);
    CHECK(v1.y == 10.0f);
  }

  SECTION("divide") {
    auto r = v1 / 5.0f;
    CHECK(r.x == 0.2f);
    CHECK(r.y == 0.4f);

    v1 /= 5.0f;
    CHECK(v1.x == 0.2f);
    CHECK(v1.y == 0.4f);
  }
}

}  // namespace ca
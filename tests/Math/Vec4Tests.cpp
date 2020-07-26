#include <catch2/catch.hpp>

#include "canvas/Math/Vec4.h"

namespace ca {

TEST_CASE("Vec4 construct") {
  auto v1 = Vec4{1.0f, 2.0f, 3.0f, 4.0f};
  CHECK(v1.x == 1.0f);
  CHECK(v1.y == 2.0f);
  CHECK(v1.z == 3.0f);
  CHECK(v1.w == 4.0f);

  auto v2 = Vec4{Vec3{1.0f, 2.0f, 3.0f}, 4.0f};
  CHECK(v2.x == 1.0f);
  CHECK(v2.y == 2.0f);
  CHECK(v2.z == 3.0f);
  CHECK(v2.w == 4.0f);
}

TEST_CASE("Vec4 operators") {
  auto v1 = Vec4{1.0f, 2.0f, 3.0f, 4.0f};
  auto v2 = Vec4{3.0f, 4.0f, 5.0f, 6.0f};

  SECTION("add") {
    auto r = v1 + v2;
    CHECK(r.x == 4.0f);
    CHECK(r.y == 6.0f);
    CHECK(r.z == 8.0f);
    CHECK(r.w == 10.0f);

    v1 += v2;
    CHECK(v1.x == 4.0f);
    CHECK(v1.y == 6.0f);
    CHECK(v1.z == 8.0f);
    CHECK(v1.w == 10.0f);
  }

  SECTION("subtract") {
    auto r = v1 - v2;
    CHECK(r.x == -2.0f);
    CHECK(r.y == -2.0f);
    CHECK(r.z == -2.0f);
    CHECK(r.w == -2.0f);

    v1 -= v2;
    CHECK(v1.x == -2.0f);
    CHECK(v1.y == -2.0f);
    CHECK(v1.z == -2.0f);
    CHECK(v1.w == -2.0f);
  }

  SECTION("multiply") {
    auto r = v1 * 5.0f;
    CHECK(r.x == 5.0f);
    CHECK(r.y == 10.0f);
    CHECK(r.z == 15.0f);
    CHECK(r.w == 20.0f);

    v1 *= 5.0f;
    CHECK(v1.x == 5.0f);
    CHECK(v1.y == 10.0f);
    CHECK(v1.z == 15.0f);
    CHECK(v1.w == 20.0f);
  }

  SECTION("divide") {
    auto r = v1 / 5.0f;
    CHECK(r.x == 0.2f);
    CHECK(r.y == 0.4f);
    CHECK(r.z == 0.6f);
    CHECK(r.w == 0.8f);

    v1 /= 5.0f;
    CHECK(v1.x == 0.2f);
    CHECK(v1.y == 0.4f);
    CHECK(v1.z == 0.6f);
    CHECK(v1.w == 0.8f);
  }
}

}  // namespace ca

#include <catch2/catch.hpp>

#include "canvas/Math/Vec3.h"

namespace ca {

TEST_CASE("Vec3 construct") {
  auto v1 = Vec3{1.0f, 2.0f, 3.0f};
  CHECK(v1.x == 1.0f);
  CHECK(v1.y == 2.0f);
  CHECK(v1.z == 3.0f);

  auto v2 = Vec3{Vec2{1.0f, 2.0f}, 3.0f};
  CHECK(v2.x == 1.0f);
  CHECK(v2.y == 2.0f);
  CHECK(v2.z == 3.0f);
}

TEST_CASE("Vec3 operators") {
  auto v1 = Vec3{1.0f, 2.0f, 3.0f};
  auto v2 = Vec3{3.0f, 4.0f, 5.0f};

  SECTION("add") {
    auto r = v1 + v2;
    CHECK(r.x == 4.0f);
    CHECK(r.y == 6.0f);
    CHECK(r.z == 8.0f);

    v1 += v2;
    CHECK(v1.x == 4.0f);
    CHECK(v1.y == 6.0f);
    CHECK(v1.z == 8.0f);
  }

  SECTION("subtract") {
    auto r = v1 - v2;
    CHECK(r.x == -2.0f);
    CHECK(r.y == -2.0f);
    CHECK(r.z == -2.0f);

    v1 -= v2;
    CHECK(v1.x == -2.0f);
    CHECK(v1.y == -2.0f);
    CHECK(v1.z == -2.0f);
  }

  SECTION("multiply") {
    auto r = v1 * 5.0f;
    CHECK(r.x == 5.0f);
    CHECK(r.y == 10.0f);
    CHECK(r.z == 15.0f);

    v1 *= 5.0f;
    CHECK(v1.x == 5.0f);
    CHECK(v1.y == 10.0f);
    CHECK(v1.z == 15.0f);
  }

  SECTION("divide") {
    auto r = v1 / 5.0f;
    CHECK(r.x == 0.2f);
    CHECK(r.y == 0.4f);
    CHECK(r.z == 0.6f);

    v1 /= 5.0f;
    CHECK(v1.x == 0.2f);
    CHECK(v1.y == 0.4f);
    CHECK(v1.z == 0.6f);
  }
}

TEST_CASE("Vec3 utilities") {
  auto v1 = Vec3{1.0f, 2.0f, 3.0f};
  auto v2 = Vec3{3.0f, 4.0f, 5.0f};

  SECTION("dotProduct") {
    auto result = dotProduct(v1, v2);
    CHECK(result == 26.0f);
  }

  SECTION("crossProduct") {
    auto result = crossProduct(v1, v2);
    CHECK(result.x == -2.0f);
    CHECK(result.y == 4.0f);
    CHECK(result.z == -2.0f);
  }

  SECTION("lengthSquared") {
    auto result = lengthSquared(v1);
    CHECK(result == 14.0f);
  }

  SECTION("length") {
    auto result = length(v1);
    CHECK(result == squareRoot(14.0f));
  }

  SECTION("normalize") {
    auto result = normalize(v1);
    F32 x = 1.0f / squareRoot(14.0f);
    CHECK(result.x == 1.0f * x);
    CHECK(result.y == 2.0f * x);
    CHECK(result.z == 3.0f * x);
  }
}

}  // namespace ca

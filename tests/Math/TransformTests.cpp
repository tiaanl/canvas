#include <catch2/catch.hpp>

#include "canvas/Math/Transform.h"

namespace ca {

TEST_CASE("another transform test") {
  Mat4 projection = perspectiveProjection(degrees(45.0f), 1.0f, 0.1f, 100.0f);

  auto result1 = projection * Vec4{0.0f, 0.0f, 0.0f, 1.0f};
  CHECK(result1.x == 0.0f);
  CHECK(result1.y == 0.0f);
  CHECK(nearZero(result1.z + 0.2002002f));
  CHECK(result1.w == 0.0f);

  auto result2 = projection * Vec4{10.0f, 10.0f, 10.0f, 1.0f};
  CHECK(nearZero(result2.x - 17.925909f));
  CHECK(nearZero(result2.y - 17.925909f));
  CHECK(nearZero(result2.z - -10.2202196f));
  CHECK(nearZero(result2.w - -10.0f));
}

TEST_CASE("frustum matrix") {
  {
    Mat4 m = frustumMatrix(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f);

    auto result1 = m * ca::Vec4{0.0f, 0.0f, 0.0f, 1.0f};
    CHECK(result1.x == 0.0f);
    CHECK(result1.y == 0.0f);
    CHECK(result1.z == -1.0f);
    CHECK(result1.w == 0.0f);

    auto result2 = m * ca::Vec4{1.0f, 1.0f, -1.0f, 1.0f};
    CHECK(result2.x == 1.0f);
    CHECK(result2.y == 1.0f);
    CHECK(result2.z == -1.0f);
    CHECK(result2.w == 1.0f);

    auto result3 = m * ca::Vec4{1.0f, 1.0f, 1.0f, 1.0f};
    CHECK(result3.x == 1.0f);
    CHECK(result3.y == 1.0f);
    CHECK(result3.z == -1.0f);
    CHECK(result3.w == -1.0f);
  }

  {
    Mat4 m = frustumMatrix(-20.0f, 30.0f, -20.0f, 30.0f, -20.0f, 30.0f);

    auto result1 = m * Vec4{0.0f, 0.0f, 0.0f, 0.0f};
    CHECK(result1.x == 0.0f);
    CHECK(result1.y == 0.0f);
    CHECK(result1.z == 0.0f);
    CHECK(result1.w == 0.0f);

    auto result2 = m * Vec4{-20.0f, -20.0f, -20.0f, 0.0f};
    CHECK(result2.x == 12.0f);
    CHECK(result2.y == 12.0f);
    CHECK(result2.z == 4.0f);
    CHECK(result2.w == 20.0f);
  }
}

}  // namespace ca


#include "canvas/Math/Transform.h"
#include "nucleus/Testing.h"

TEST_CASE("Ortho") {
  F32 left = 0.f;
  F32 right = 1600.f;
  F32 top = 0.f;
  F32 bottom = 900.f;
  F32 near = -1.f;
  F32 far = 1.f;

  ca::Mat4 ortho = ca::ortho(left, right, bottom, top);

  // clang-format off
  ca::Mat4 expected = ca::Mat4{
          2.f / (right - left), 0.f, 0.f, 0.f,
          0.f, 2.f / (top - bottom), 0.f, 0.f,
          0.f, 0.f, 2.f / (far - near), 0.f,
          -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.f
  };
  // clang-format on

  REQUIRE(ortho == expected);
}

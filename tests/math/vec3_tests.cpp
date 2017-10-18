
#include "canvas/math/vec3.h"
#include "gtest/gtest.h"

namespace ca {

TEST(Vec3Test, Basic) {
  Vec3 v1;
  EXPECT_EQ(0.f, v1.x);
  EXPECT_EQ(0.f, v1.y);
  EXPECT_EQ(0.f, v1.z);

  Vec3 v2{1.f, 2.f, 3.f};
  EXPECT_EQ(1.f, v2.x);
  EXPECT_EQ(2.f, v2.y);
  EXPECT_EQ(3.f, v2.z);
}

}  // namespace ca

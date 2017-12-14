
#include "canvas/Math/Vec2.h"
#include "gtest/gtest.h"

namespace ca {

TEST(Vec2Test, Basic) {
  Vec2 v1;
  EXPECT_EQ(0.f, v1.x);
  EXPECT_EQ(0.f, v1.y);

  Vec2 v2{1.f};
  EXPECT_EQ(1.f, v2.x);
  EXPECT_EQ(0.f, v2.y);

  Vec2 v3{1.f, 2.f};
  EXPECT_EQ(1.f, v3.x);
  EXPECT_EQ(2.f, v3.y);
}

}  // namespace ca

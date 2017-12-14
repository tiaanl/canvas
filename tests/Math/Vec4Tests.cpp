
#include "canvas/Math/Vec4.h"
#include "gtest/gtest.h"

namespace ca {

TEST(Vec4Test, Basic) {
  Vec4 v1;
  EXPECT_EQ(0.f, v1.x);
  EXPECT_EQ(0.f, v1.y);
  EXPECT_EQ(0.f, v1.z);
  EXPECT_EQ(0.f, v1.w);

  Vec4 v2{1.f, 2.f, 3.f, 4.f};
  EXPECT_EQ(1.f, v2.x);
  EXPECT_EQ(2.f, v2.y);
  EXPECT_EQ(3.f, v2.z);
  EXPECT_EQ(4.f, v2.w);
}

}  // namespace ca

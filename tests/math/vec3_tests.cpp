// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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

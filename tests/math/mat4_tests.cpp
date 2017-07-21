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

#include "canvas/math/mat4.h"
#include "canvas/math/transform.h"
#include "gtest/gtest.h"

namespace ca {

TEST(Mat4Test, Basic) {
    Mat4 v1;
    EXPECT_EQ(1.f, v1[0][0]);
    EXPECT_EQ(0.f, v1[0][1]);
    EXPECT_EQ(0.f, v1[0][2]);
    EXPECT_EQ(0.f, v1[0][3]);
    EXPECT_EQ(0.f, v1[1][0]);
    EXPECT_EQ(1.f, v1[1][1]);
    EXPECT_EQ(0.f, v1[1][2]);
    EXPECT_EQ(0.f, v1[1][3]);
    EXPECT_EQ(0.f, v1[2][0]);
    EXPECT_EQ(0.f, v1[2][1]);
    EXPECT_EQ(1.f, v1[2][2]);
    EXPECT_EQ(0.f, v1[2][3]);
    EXPECT_EQ(0.f, v1[3][0]);
    EXPECT_EQ(0.f, v1[3][1]);
    EXPECT_EQ(0.f, v1[3][2]);
    EXPECT_EQ(1.f, v1[3][3]);
}

std::ostream& operator<<(std::ostream& os, const Mat4& mat) {
    os << "\n";
    for (auto col = 0; col < 4; ++col) {
        for (auto row = 0; row < 4; ++row) {
            os.width(6);
            os.setf(std::ios::fixed, std::ios::floatfield);
            os.precision(2);
            os << std::showpoint << mat[col][row] << "  ";
        }
        os << "\n";
    }

    return os;
}

TEST(Mat4Test, Multiply) {
    const Mat4 first{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f};

    const Mat4 second{13.f, 14.f, 15.f, 16.f, 9.f, 10.f, 11.f, 12.f, 5.f, 6.f, 7.f, 8.f, 1.f, 2.f, 3.f, 4.f};

    Mat4 actual1 = first * second;

    const Mat4 expected1{426.f, 484.f, 542.f, 600.f, 314.f, 356.f, 398.f, 440.f,
                         202.f, 228.f, 254.f, 280.f, 90.f,  100.f, 110.f, 120.f};

    EXPECT_EQ(expected1, actual1);
}

TEST(Mat4Test, MultiplyByVector) {
    const Mat4 first{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f};

    const Vec4 result1 = first * Vec4{1.f, 2.f, 3.f, 4.f};
    const Vec4 expected1{90.f, 100.f, 110.f, 120.f};

    EXPECT_EQ(expected1, result1);
}

TEST(Mat4Test, Inverse) {
    const Mat4 first{3.f, 9.f, 4.f, 9.f, 5.f, 7.f, 2.f, 5.f, 1.f, 2.f, 3.f, 3.f, 6.f, 8.f, 7.f, 4.f};

    const Mat4 result1 = inverse(first);

    const Mat4 expected2{-81.f / 226.f, 107.f / 226.f, 51.f / 113.f, -14.f / 113.f, 36.f / 113.f, -35.f / 113.f,
                         -83.f / 113.f, 25.f / 113.f,  -1.f / 113.f, -21.f / 113.f, 18.f / 113.f, 15.f / 113.f,
                         -19.f / 226.f, 53.f / 226.f,  58.f / 113.f, -27.f / 113.f};

    EXPECT_EQ(expected2, result1);
}

}  // namespace ca

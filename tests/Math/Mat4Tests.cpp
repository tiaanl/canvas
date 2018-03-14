
#include "canvas/Math/Mat4.h"
#include "canvas/Math/Transform.h"
#include "nucleus/Testing.h"

namespace ca {

TEST_CASE("Mat4Basic") {
  Mat4 v1;
  REQUIRE(v1[0][0] == 1.f);
  REQUIRE(v1[0][1] == 0.f);
  REQUIRE(v1[0][2] == 0.f);
  REQUIRE(v1[0][3] == 0.f);
  REQUIRE(v1[1][0] == 0.f);
  REQUIRE(v1[1][1] == 1.f);
  REQUIRE(v1[1][2] == 0.f);
  REQUIRE(v1[1][3] == 0.f);
  REQUIRE(v1[2][0] == 0.f);
  REQUIRE(v1[2][1] == 0.f);
  REQUIRE(v1[2][2] == 1.f);
  REQUIRE(v1[2][3] == 0.f);
  REQUIRE(v1[3][0] == 0.f);
  REQUIRE(v1[3][1] == 0.f);
  REQUIRE(v1[3][2] == 0.f);
  REQUIRE(v1[3][3] == 1.f);
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

TEST_CASE("Multiply") {
  const Mat4 first{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f};

  const Mat4 second{13.f, 14.f, 15.f, 16.f, 9.f, 10.f, 11.f, 12.f, 5.f, 6.f, 7.f, 8.f, 1.f, 2.f, 3.f, 4.f};

  Mat4 actual1 = first * second;

  const Mat4 expected1{426.f, 484.f, 542.f, 600.f, 314.f, 356.f, 398.f, 440.f,
                       202.f, 228.f, 254.f, 280.f, 90.f,  100.f, 110.f, 120.f};

  REQUIRE(actual1 == expected1);
}

TEST_CASE("MultiplyByVector") {
  const Mat4 first{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f};

  const Vec4 result1 = first * Vec4{1.f, 2.f, 3.f, 4.f};
  const Vec4 expected1{90.f, 100.f, 110.f, 120.f};

  REQUIRE(result1 == expected1);
}

TEST_CASE("Inverse") {
  const Mat4 first{3.f, 9.f, 4.f, 9.f, 5.f, 7.f, 2.f, 5.f, 1.f, 2.f, 3.f, 3.f, 6.f, 8.f, 7.f, 4.f};

  const Mat4 result1 = inverse(first);

  const Mat4 expected2{-81.f / 226.f, 107.f / 226.f, 51.f / 113.f, -14.f / 113.f, 36.f / 113.f, -35.f / 113.f,
                       -83.f / 113.f, 25.f / 113.f,  -1.f / 113.f, -21.f / 113.f, 18.f / 113.f, 15.f / 113.f,
                       -19.f / 226.f, 53.f / 226.f,  58.f / 113.f, -27.f / 113.f};

  REQUIRE(result1 == expected2);
}

}  // namespace ca

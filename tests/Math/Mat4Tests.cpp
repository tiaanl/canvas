#include "canvas/Math/Mat4.h"
#include "nucleus/Testing.h"

namespace ca {

TEST_CASE("Mat4 statics") {
  CHECK(Mat4::identity.col[0].x == 1.0f);
  CHECK(Mat4::identity.col[0].y == 0.0f);
  CHECK(Mat4::identity.col[0].z == 0.0f);
  CHECK(Mat4::identity.col[0].w == 0.0f);

  CHECK(Mat4::identity.col[1].x == 0.0f);
  CHECK(Mat4::identity.col[1].y == 1.0f);
  CHECK(Mat4::identity.col[1].z == 0.0f);
  CHECK(Mat4::identity.col[1].w == 0.0f);

  CHECK(Mat4::identity.col[2].x == 0.0f);
  CHECK(Mat4::identity.col[2].y == 0.0f);
  CHECK(Mat4::identity.col[2].z == 1.0f);
  CHECK(Mat4::identity.col[2].w == 0.0f);

  CHECK(Mat4::identity.col[3].x == 0.0f);
  CHECK(Mat4::identity.col[3].y == 0.0f);
  CHECK(Mat4::identity.col[3].z == 0.0f);
  CHECK(Mat4::identity.col[3].w == 1.0f);
}

TEST_CASE("Mat4 construct") {
  auto right = Vec3{1.0f, 2.0f, 3.0f};
  auto up = Vec3{4.0f, 5.0f, 6.0f};
  auto forward = Vec3{7.0f, 8.0f, 9.0f};

  auto m1 = Mat4{right, up, forward};

  CHECK(m1.col[0].x == 1.0f);
  CHECK(m1.col[0].y == 2.0f);
  CHECK(m1.col[0].z == 3.0f);
  CHECK(m1.col[0].w == 0.0f);

  CHECK(m1.col[1].x == 4.0f);
  CHECK(m1.col[1].y == 5.0f);
  CHECK(m1.col[1].z == 6.0f);
  CHECK(m1.col[1].w == 0.0f);

  CHECK(m1.col[2].x == 7.0f);
  CHECK(m1.col[2].y == 8.0f);
  CHECK(m1.col[2].z == 9.0f);
  CHECK(m1.col[2].w == 0.0f);

  CHECK(m1.col[3].x == 0.0f);
  CHECK(m1.col[3].y == 0.0f);
  CHECK(m1.col[3].z == 0.0f);
  CHECK(m1.col[3].w == 1.0f);
}

TEST_CASE("Mat4 matrix * matrix") {
  Mat4 m1{{1.0f, 2.0f, 3.0f, 4.0f},
          {5.0f, 6.0f, 7.0f, 8.0f},
          {9.0f, 10.0f, 11.0f, 12.0f},
          {13.0f, 14.0f, 15.0f, 16.0f}};
  Mat4 m2{{3.0f, 4.0f, 5.0f, 6.0f},
          {7.0f, 8.0f, 9.0f, 10.0f},
          {11.0f, 12.0f, 13.0f, 14.0f},
          {15.0f, 16.0f, 17.0f, 18.0f}};

  Mat4 result = m1 * m2;

  /*
    1	146	258	370	482
    2	164	292	420	548
    3	182	326	470	614
    4	200	360	520	680
  */

  CHECK(result.col[0].x == 146.0f);
  CHECK(result.col[0].y == 164.0f);
  CHECK(result.col[0].z == 182.0f);
  CHECK(result.col[0].w == 200.0f);

  CHECK(result.col[1].x == 258.0f);
  CHECK(result.col[1].y == 292.0f);
  CHECK(result.col[1].z == 326.0f);
  CHECK(result.col[1].w == 360.0f);

  CHECK(result.col[2].x == 370.0f);
  CHECK(result.col[2].y == 420.0f);
  CHECK(result.col[2].z == 470.0f);
  CHECK(result.col[2].w == 520.0f);

  CHECK(result.col[3].x == 482.0f);
  CHECK(result.col[3].y == 548.0f);
  CHECK(result.col[3].z == 614.0f);
  CHECK(result.col[3].w == 680.0f);
}

TEST_CASE("Mat4 mat4 * vec4") {
  Mat4 m{{1.0f, 2.0f, 3.0f, 4.0f},
         {5.0f, 6.0f, 7.0f, 8.0f},
         {9.0f, 10.0f, 11.0f, 12.0f},
         {13.0f, 14.0f, 15.0f, 16.0f}};

  Vec4 v{1.0f, 2.0f, 3.0f, 4.0f};

  auto result = m * v;

  CHECK(result.x == 90.0f);
  CHECK(result.y == 100.0f);
  CHECK(result.z == 110.0f);
  CHECK(result.w == 120.0f);
}

TEST_CASE("Mat4 vec4 * mat4") {
  Vec4 v{1.0f, 2.0f, 3.0f, 4.0f};

  Mat4 m{{1.0f, 2.0f, 3.0f, 4.0f},
         {5.0f, 6.0f, 7.0f, 8.0f},
         {9.0f, 10.0f, 11.0f, 12.0f},
         {13.0f, 14.0f, 15.0f, 16.0f}};

  auto result = v * m;

  CHECK(result.x == 30.0f);
  CHECK(result.y == 70.0f);
  CHECK(result.z == 110.0f);
  CHECK(result.w == 150.0f);
}

TEST_CASE("Mat4 transpose") {
  Mat4 m{{1.0f, 2.0f, 3.0f, 4.0f},
         {5.0f, 6.0f, 7.0f, 8.0f},
         {9.0f, 10.0f, 11.0f, 12.0f},
         {13.0f, 14.0f, 15.0f, 16.0f}};

  auto result = transpose(m);

  CHECK(result.col[0].x == 1.0f);
  CHECK(result.col[0].y == 5.0f);
  CHECK(result.col[0].z == 9.0f);
  CHECK(result.col[0].w == 13.0f);

  CHECK(result.col[1].x == 2.0f);
  CHECK(result.col[1].y == 6.0f);
  CHECK(result.col[1].z == 10.0f);
  CHECK(result.col[1].w == 14.0f);

  CHECK(result.col[2].x == 3.0f);
  CHECK(result.col[2].y == 7.0f);
  CHECK(result.col[2].z == 11.0f);
  CHECK(result.col[2].w == 15.0f);

  CHECK(result.col[3].x == 4.0f);
  CHECK(result.col[3].y == 8.0f);
  CHECK(result.col[3].z == 12.0f);
  CHECK(result.col[3].w == 16.0f);
}

TEST_CASE("Mat4 inverse") {
  // -2   1   5   2
  //  4   0  -3  -1
  // -6  -3   0   8
  //  1   0  -1   3

  // determinant = -89

  //  30/89    59/89   10/89   -27/89
  // -52/89  -126/89  -47/89   118/89
  //  39/89    50/89   13/89   -44/89
  //   3/89    -3/89    1/89    24/89

  auto m = Mat4{{-2.0f, 4.0f, -6.0f, 1.0f},
                {1.0f, 0.0f, -3.0f, 0.0f},
                {5.0f, -3.0f, 0.0f, -1.0f},
                {2.0f, -1.0f, 8.0f, 3.0f}};

  auto result = inverse(m);

  CHECK(result.col[0].x == 30.0f / 89.0f);
  CHECK(result.col[0].y == -52.0f / 89.0f);
  CHECK(result.col[0].z == 39.0f / 89.0f);
  CHECK(result.col[0].w == 3.0f / 89.0f);

  CHECK(result.col[1].x == 59.0f / 89.0f);
  CHECK(result.col[1].y == -126.0f / 89.0f);
  CHECK(result.col[1].z == 50.0f / 89.0f);
  CHECK(result.col[1].w == -3.0f / 89.0f);

  CHECK(result.col[2].x == 10.0f / 89.0f);
  CHECK(result.col[2].y == -47.0f / 89.0f);
  CHECK(result.col[2].z == 13.0f / 89.0f);
  CHECK(result.col[2].w == 1.0f / 89.0f);

  CHECK(result.col[3].x == -27.0f / 89.0f);
  CHECK(result.col[3].y == 118.0f / 89.0f);
  CHECK(result.col[3].z == -44.0f / 89.0f);
  CHECK(result.col[3].w == 24.0f / 89.0f);
}

}  // namespace ca

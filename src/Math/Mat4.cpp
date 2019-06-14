
#include "canvas/Math/Mat4.h"

namespace ca {

// static
Mat4 Mat4::identity{{1.0f, 0.0f, 0.0f, 0.0f},
                    {0.0f, 1.0f, 0.0f, 0.0f},
                    {0.0f, 0.0f, 1.0f, 0.0f},
                    {0.0f, 0.0f, 0.0f, 1.0f}};

Mat4 operator*(const Mat4& left, const Mat4& right) {
  return Mat4{{left.col[0].x * right.col[0].x + left.col[1].x * right.col[0].y +
                   left.col[2].x * right.col[0].z + left.col[3].x * right.col[0].w,
               left.col[0].y * right.col[0].x + left.col[1].y * right.col[0].y +
                   left.col[2].y * right.col[0].z + left.col[3].y * right.col[0].w,
               left.col[0].z * right.col[0].x + left.col[1].z * right.col[0].y +
                   left.col[2].z * right.col[0].z + left.col[3].z * right.col[0].w,
               left.col[0].w * right.col[0].x + left.col[1].w * right.col[0].y +
                   left.col[2].w * right.col[0].z + left.col[3].w * right.col[0].w},
              {left.col[0].x * right.col[1].x + left.col[1].x * right.col[1].y +
                   left.col[2].x * right.col[1].z + left.col[3].x * right.col[1].w,
               left.col[0].y * right.col[1].x + left.col[1].y * right.col[1].y +
                   left.col[2].y * right.col[1].z + left.col[3].y * right.col[1].w,
               left.col[0].z * right.col[1].x + left.col[1].z * right.col[1].y +
                   left.col[2].z * right.col[1].z + left.col[3].z * right.col[1].w,
               left.col[0].w * right.col[1].x + left.col[1].w * right.col[1].y +
                   left.col[2].w * right.col[1].z + left.col[3].w * right.col[1].w},
              {left.col[0].x * right.col[2].x + left.col[1].x * right.col[2].y +
                   left.col[2].x * right.col[2].z + left.col[3].x * right.col[2].w,
               left.col[0].y * right.col[2].x + left.col[1].y * right.col[2].y +
                   left.col[2].y * right.col[2].z + left.col[3].y * right.col[2].w,
               left.col[0].z * right.col[2].x + left.col[1].z * right.col[2].y +
                   left.col[2].z * right.col[2].z + left.col[3].z * right.col[2].w,
               left.col[0].w * right.col[2].x + left.col[1].w * right.col[2].y +
                   left.col[2].w * right.col[2].z + left.col[3].w * right.col[2].w},
              {left.col[0].x * right.col[3].x + left.col[1].x * right.col[3].y +
                   left.col[2].x * right.col[3].z + left.col[3].x * right.col[3].w,
               left.col[0].y * right.col[3].x + left.col[1].y * right.col[3].y +
                   left.col[2].y * right.col[3].z + left.col[3].y * right.col[3].w,
               left.col[0].z * right.col[3].x + left.col[1].z * right.col[3].y +
                   left.col[2].z * right.col[3].z + left.col[3].z * right.col[3].w,
               left.col[0].w * right.col[3].x + left.col[1].w * right.col[3].y +
                   left.col[2].w * right.col[3].z + left.col[3].w * right.col[3].w}};
}

Vec4 operator*(const Mat4& left, const Vec4& right) {
  return {left.col[0].x * right.x + left.col[1].x * right.y + left.col[2].x * right.z +
              left.col[3].x * right.w,
          left.col[0].y * right.x + left.col[1].y * right.y + left.col[2].y * right.z +
              left.col[3].y * right.w,
          left.col[0].z * right.x + left.col[1].z * right.y + left.col[2].z * right.z +
              left.col[3].z * right.w,
          left.col[0].w * right.x + left.col[1].w * right.y + left.col[2].w * right.z +
              left.col[3].w * right.w};
}

Vec4 operator*(const Vec4& left, const Mat4& right) {
  return {left.x * right.col[0].x + left.y * right.col[0].y + left.z * right.col[0].z +
              left.w * right.col[0].w,
          left.x * right.col[1].x + left.y * right.col[1].y + left.z * right.col[1].z +
              left.w * right.col[1].w,
          left.x * right.col[2].x + left.y * right.col[2].y + left.z * right.col[2].z +
              left.w * right.col[2].w,
          left.x * right.col[3].x + left.y * right.col[3].y + left.z * right.col[3].z +
              left.w * right.col[3].w};
}

Mat4 transpose(const Mat4& m) {
  return {{m.col[0].x, m.col[1].x, m.col[2].x, m.col[3].x},
          {m.col[0].y, m.col[1].y, m.col[2].y, m.col[3].y},
          {m.col[0].z, m.col[1].z, m.col[2].z, m.col[3].z},
          {m.col[0].w, m.col[1].w, m.col[2].w, m.col[3].w}};
}

static F32 coFactor(F32 c1r1, F32 c1r2, F32 c2r1, F32 c2r2) {
  F32 c1 = c1r1 * c2r2;
  F32 c2 = c1r2 * c2r1;
  return c1 - c2;
}

static F32 coFactor(F32 c1r1, F32 c1r2, F32 c1r3, F32 c2r1, F32 c2r2, F32 c2r3, F32 c3r1, F32 c3r2,
                    F32 c3r3) {
  F32 c1 = c1r1 * coFactor(c2r2, c2r3, c3r2, c3r3);
  F32 c2 = c2r1 * coFactor(c1r2, c1r3, c3r2, c3r3);
  F32 c3 = c3r1 * coFactor(c1r2, c1r3, c2r2, c2r3);

  return c1 - c2 + c3;
}

Mat4 inverse(const Mat4& m) {
  F32 c1r1 = m.col[0].x;
  F32 c1r2 = m.col[0].y;
  F32 c1r3 = m.col[0].z;
  F32 c1r4 = m.col[0].w;

  F32 c2r1 = m.col[1].x;
  F32 c2r2 = m.col[1].y;
  F32 c2r3 = m.col[1].z;
  F32 c2r4 = m.col[1].w;

  F32 c3r1 = m.col[2].x;
  F32 c3r2 = m.col[2].y;
  F32 c3r3 = m.col[2].z;
  F32 c3r4 = m.col[2].w;

  F32 c4r1 = m.col[3].x;
  F32 c4r2 = m.col[3].y;
  F32 c4r3 = m.col[3].z;
  F32 c4r4 = m.col[3].w;

  F32 determinant = (c1r1 * coFactor(c2r2, c2r3, c2r4, c3r2, c3r3, c3r4, c4r2, c4r3, c4r4)) -
                    (c2r1 * coFactor(c1r2, c1r3, c1r4, c3r2, c3r3, c3r4, c4r2, c4r3, c4r4)) +
                    (c3r1 * coFactor(c1r2, c1r3, c1r4, c2r2, c2r3, c2r4, c4r2, c4r3, c4r4)) -
                    (c4r1 * coFactor(c1r2, c1r3, c1r4, c2r2, c2r3, c2r4, c3r2, c3r3, c3r4));

  F32 invDet = 1.0f / determinant;

  return {
      {
          +coFactor(c2r2, c2r3, c2r4, c3r2, c3r3, c3r4, c4r2, c4r3, c4r4) * invDet,
          -coFactor(c1r2, c1r3, c1r4, c3r2, c3r3, c3r4, c4r2, c4r3, c4r4) * invDet,
          +coFactor(c1r2, c1r3, c1r4, c2r2, c2r3, c2r4, c4r2, c4r3, c4r4) * invDet,
          -coFactor(c1r2, c1r3, c1r4, c2r2, c2r3, c2r4, c3r2, c3r3, c3r4) * invDet,
      },
      {
          -coFactor(c2r1, c2r3, c2r4, c3r1, c3r3, c3r4, c4r1, c4r3, c4r4) * invDet,
          +coFactor(c1r1, c1r3, c1r4, c3r1, c3r3, c3r4, c4r1, c4r3, c4r4) * invDet,
          -coFactor(c1r1, c1r3, c1r4, c2r1, c2r3, c2r4, c4r1, c4r3, c4r4) * invDet,
          +coFactor(c1r1, c1r3, c1r4, c2r1, c2r3, c2r4, c3r1, c3r3, c3r4) * invDet,
      },
      {
          +coFactor(c2r1, c2r2, c2r4, c3r1, c3r2, c3r4, c4r1, c4r2, c4r4) * invDet,
          -coFactor(c1r1, c1r2, c1r4, c3r1, c3r2, c3r4, c4r1, c4r2, c4r4) * invDet,
          +coFactor(c1r1, c1r2, c1r4, c2r1, c2r2, c2r4, c4r1, c4r2, c4r4) * invDet,
          -coFactor(c1r1, c1r2, c1r4, c2r1, c2r2, c2r4, c3r1, c3r2, c3r4) * invDet,
      },
      {
          -coFactor(c2r1, c2r2, c2r3, c3r1, c3r2, c3r3, c4r1, c4r2, c4r3) * invDet,
          +coFactor(c1r1, c1r2, c1r3, c3r1, c3r2, c3r3, c4r1, c4r2, c4r3) * invDet,
          -coFactor(c1r1, c1r2, c1r3, c2r1, c2r2, c2r3, c4r1, c4r2, c4r3) * invDet,
          +coFactor(c1r1, c1r2, c1r3, c2r1, c2r2, c2r3, c3r1, c3r2, c3r3) * invDet,

      },
  };
}

}  // namespace ca


#include "canvas/Math/Transform.h"

namespace ca {

Mat4 scaleMatrix(F32 scale) {
  return scaleMatrix(Vec3{scale, scale, scale});
}

Mat4 scaleMatrix(const Vec3& scale) {
  return Mat4{
      Vec4{scale.x, 0.0f, 0.0f, 0.0f},
      Vec4{0.0f, scale.y, 0.0f, 0.0f},
      Vec4{0.0f, 0.0f, scale.z, 0.0f},
      Vec4{0.0f, 0.0f, 0.0f, 1.0f},
  };
}

Mat4 translationMatrix(const Vec3& translate) {
  Mat4 result = ca::Mat4::identity;
  result.col[3] = Vec4{translate, 1.0f};
  return result;
}

Mat4 orthographicProjection(F32 left, F32 right, F32 top, F32 bottom, F32 near, F32 far) {
  auto col1 = Vec4{2.0f / (right - left), 0.0f, 0.0f, 0.0f};

  auto col2 = Vec4{0.0f, 2.0f / (top - bottom), 0.0f, 0.0f};

  auto col3 = Vec4{0.0f, 0.0f, -2.0f / (far - near), 0.0f};

  auto col4 = Vec4{-(right + left) / (right - left), -(top + bottom) / (top - bottom),
                   -(far + near) / (far - near), 1.0f};

  return Mat4{col1, col2, col3, col4};
}

}  // namespace ca

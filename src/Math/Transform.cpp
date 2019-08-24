
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

Mat4 rotationMatrix(const Vec3& axis, Angle angle) {
  const auto normalizedAxis = normalize(axis);

  const F32 sinTheta = sine(angle);
  const F32 cosTheta = cosine(angle);
  const F32 cosValue = 1.0f - cosTheta;

  return {
      {
          (normalizedAxis.x * normalizedAxis.x * cosValue) + cosTheta,
          (normalizedAxis.x * normalizedAxis.y * cosValue) + (normalizedAxis.z * sinTheta),
          (normalizedAxis.x * normalizedAxis.z * cosValue) - (normalizedAxis.y * sinTheta),
          0.0f,
      },
      {
          (normalizedAxis.y * normalizedAxis.x * cosValue) - (normalizedAxis.z * sinTheta),
          (normalizedAxis.y * normalizedAxis.y * cosValue) + cosTheta,
          (normalizedAxis.y * normalizedAxis.z * cosValue) + (normalizedAxis.x * sinTheta),
          0.0f,
      },
      {
          (normalizedAxis.z * normalizedAxis.x * cosValue) + (normalizedAxis.y * sinTheta),
          (normalizedAxis.z * normalizedAxis.y * cosValue) - (normalizedAxis.x * sinTheta),
          (normalizedAxis.z * normalizedAxis.z * cosValue) + cosTheta,
          0.0f,
      },
      {
          0.0f,
          0.0f,
          0.0f,
          1.0f,
      },
  };
}

Mat4 frustumMatrix(F32 left, F32 right, F32 bottom, F32 top, F32 near, F32 far) {
  F32 dx = right - left;
  F32 dy = top - bottom;
  F32 dz = far - near;

  return {{
              (2.0f * near) / dx,
              0.0f,
              0.0f,
              0.0f,
          },
          {
              0.0f,
              (2.0f * near) / dy,
              0.0f,
              0.0f,
          },
          {
              (right + left) / dx,
              (top + bottom) / dy,
              -(far + near) / dz,
              -1.0f,
          },
          {
              0.0f,
              0.0f,
              -(2.0f * near * far) / dz,
              0.0f,
          }};
}

Mat4 orthographicProjection(F32 left, F32 right, F32 top, F32 bottom, F32 near, F32 far) {
  auto col1 = Vec4{2.0f / (right - left), 0.0f, 0.0f, 0.0f};

  auto col2 = Vec4{0.0f, 2.0f / (top - bottom), 0.0f, 0.0f};

  auto col3 = Vec4{0.0f, 0.0f, -2.0f / (far - near), 0.0f};

  auto col4 = Vec4{-(right + left) / (right - left), -(top + bottom) / (top - bottom),
                   -(far + near) / (far - near), 1.0f};

  return Mat4{col1, col2, col3, col4};
}

Mat4 perspectiveProjection(Angle fieldOfView, F32 aspectRatio, F32 near, F32 far) {
  F32 t = tangent(fieldOfView / 2.0f);

  F32 height = near * t;
  F32 width = height * aspectRatio;

  return frustumMatrix(-width, width, -height, height, near, far);
}

Mat4 createViewMatrix(const Vec3& position, const Quaternion& orientation) {
  Mat3 rotation = orientation.toRotationMatrix();

  Mat3 transposedRotation = transpose(rotation);
  Vec3 trans = -transposedRotation * position;

  Mat4 viewMatrix = Mat4{transposedRotation};
  viewMatrix.col[3] = Vec4{trans, 1.0f};

  return viewMatrix;
}

Mat4 createModelMatrix(const ca::Mat4& translation, const ca::Mat4& rotation,
                       const ca::Mat4& scale) {
  return translation * rotation * scale;
}

}  // namespace ca

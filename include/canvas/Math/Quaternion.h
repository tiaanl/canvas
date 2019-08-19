#ifndef CANVAS_MATH_QUATERNION_H_
#define CANVAS_MATH_QUATERNION_H_

#include "canvas/Math/Angle.h"
#include "canvas/Math/Mat3.h"
#include "nucleus/Logging.h"

namespace ca {

struct AxisAngle {
  Vec3 axis;
  Angle angle;
};

// Unit quaternion:
//   w^2 + x^2 + y^2 + z^2 == 1
struct Quaternion {
  static const Quaternion identity;

  static Quaternion fromEulerAngles(F32 yaw, F32 pitch, F32 roll) {
    return {};
  }

  F32 w;
  Vec3 v;

  Quaternion() : w{1.0f}, v{Vec3::zero} {}
  Quaternion(F32 w, const Vec3& v) : w{w}, v{v} {}

  Quaternion operator*(F32 scale) const {
    return {w * scale, v * scale};
  }

  friend Quaternion operator*(F32 scale, const Quaternion& q) {
    return q * scale;
  }

  Quaternion operator*(const Quaternion& other) const {
    return {w * other.w - dotProduct(v, other.v),
            v * other.w + other.v * w + crossProduct(v, other.v)};
  }

  Quaternion operator^(F32 t) const {
    AxisAngle axisAngle = toAxisAngle();
    F32 at = axisAngle.angle.radians() * t;
    return {at, axisAngle.axis};
  }

  Vec3 operator*(const Vec3& other) const {
    Vec3 cross = crossProduct(v, other);
    return other + cross * (2.0f * w) + crossProduct(v, cross) * 2.0f;
  }

  AxisAngle toAxisAngle() const {
    Vec3 axis = (nearZero(lengthSquared(v))) ? Vec3::right : normalize(v);

    DCHECK(nearZero(absolute(lengthSquared(axis) - 1)));

    return {axis, Angle::fromRadians(arcCosine(w) * 2.0f)};
  }

  Mat3 toRotationMatrix() const {
    Mat3 Result = Mat3::identity;

    F32 qxx(v.x * v.x);
    F32 qyy(v.y * v.y);
    F32 qzz(v.z * v.z);
    F32 qxz(v.x * v.z);
    F32 qxy(v.x * v.y);
    F32 qyz(v.y * v.z);
    F32 qwx(w * v.x);
    F32 qwy(w * v.y);
    F32 qwz(w * v.z);

    Result.col[0].x = 1.0f - 2.0f * (qyy + qzz);
    Result.col[0].y = 2.0f * (qxy + qwz);
    Result.col[0].z = 2.0f * (qxz - qwy);

    Result.col[1].x = 2.0f * (qxy - qwz);
    Result.col[1].y = 1.0f - 2.0f * (qxx + qzz);
    Result.col[1].z = 2.0f * (qyz + qwx);

    Result.col[2].x = 2.0f * (qxz + qwy);
    Result.col[2].y = 2.0f * (qyz - qwx);
    Result.col[2].z = 1.0f - 2.0f * (qxx + qyy);

    return Result;
  }
};

// Create a quaternion from an axis angle rotation.
Quaternion fromAxisAngle(const ca::Vec3& axis, const Angle& angle);

// Create a quaternion from a rotation matrix.
Quaternion fromRotationMatrix(const Mat3& rotationMatrix);

inline F32 length(const Quaternion& q) {
  return squareRoot(q.w * q.w + dotProduct(q.v, q.v));
}

inline Quaternion normalize(const Quaternion& q) {
  return 1.0f / length(q) * q;
}

// Invert the given quaternion.
Quaternion inverse(const Quaternion& q);

Quaternion slerp(const Quaternion& a, const Quaternion& b, F32 t);

}  // namespace ca

#endif  // CANVAS_MATH_QUATERNION_H_

#ifndef CANAVS_MATH_MAT3_H_
#define CANAVS_MATH_MAT3_H_

#include "canvas/Math/Mat3.h"

namespace ca {

// static
Mat3 Mat3::identity = {
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
};

Mat3 transpose(const Mat3& m) {
  return {
      {m.col[0].x, m.col[1].x, m.col[2].x},
      {m.col[0].y, m.col[1].y, m.col[2].y},
      {m.col[0].z, m.col[1].z, m.col[2].z},
  };
}

}  // namespace ca

#endif  // CANAVS_MATH_MAT3_H_

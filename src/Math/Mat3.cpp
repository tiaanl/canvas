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

}  // namespace ca

#endif  // CANAVS_MATH_MAT3_H_


#ifndef CANVAS_UTILS_GL_CHECK_H_
#define CANVAS_UTILS_GL_CHECK_H_

#include "nucleus/Config.h"

#if BUILD(DEBUG)
#define GL_CHECK(Op)                                                                                                   \
  Op;                                                                                                                  \
  ::ca::glCheck()
#else
#define GL_CHECK(Op) (Op)
#endif

namespace ca {

bool glCheck();

}  // namespace ca

#endif  // CANVAS_UTILS_GL_CHECK_H_

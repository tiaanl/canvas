#pragma once

#include "nucleus/config.h"

#if BUILD(DEBUG)
#define GL_CHECK(Op)                                                                               \
  Op;                                                                                              \
  ::ca::glCheck()
#else
#define GL_CHECK(Op) (Op)
#endif

namespace ca {

bool glCheck();

}  // namespace ca

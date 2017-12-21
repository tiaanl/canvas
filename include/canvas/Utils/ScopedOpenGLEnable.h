
#ifndef CANVAS_UTILS_SCOPEDOPENGLENABLE_H_
#define CANVAS_UTILS_SCOPEDOPENGLENABLE_H_

#include "canvas/OpenGL.h"
#include "GLCheck.h"

struct ScopedOpenGLEnable {
  GLuint m_flag;

  ScopedOpenGLEnable(GLuint flag) : m_flag(flag) { GL_CHECK(glEnable(m_flag)); }

  ~ScopedOpenGLEnable() { GL_CHECK(glDisable(m_flag)); }
};

#endif  // CANVAS_UTILS_SCOPEDOPENGLENABLE_H_
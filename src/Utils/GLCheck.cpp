
#include "canvas/Utils/GLCheck.h"

#include "canvas/OpenGL.h"
#include "nucleus/Debugger.h"
#include "nucleus/Logging.h"
#include "nucleus/MemoryDebug.h"

namespace ca {

bool glCheck() {
  GLint error = glGetError();

  if (error != GL_NO_ERROR) {
    switch (error) {
      case GL_INVALID_ENUM:
        LOG(Error) << "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.  The offending "
                      "command is ignored and has no other side effect than to set the error flag.";
        break;

      case GL_INVALID_VALUE:
        LOG(Error) << "GL_INVALID_VALUE";
        break;

      case GL_INVALID_OPERATION:
        LOG(Error) << "GL_INVALID_OPERATION";
        break;

      default:
        LOG(Error) << "Unknown OpenGL error.";
        break;
    }

    nu::breakDebugger();

    return false;
  }

  return true;
}

}  // namespace ca

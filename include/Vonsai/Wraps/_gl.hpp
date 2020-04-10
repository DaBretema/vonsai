#pragma once

#include "../Utils/Logger.hpp"
#include <glad/glad.h>


namespace Vonsai::GL {

inline bool loadExtensions(void *a_proc) { return gladLoadGLLoader((GLADloadproc)a_proc); }

inline void defaultSetup() {
  glFrontFace(GL_CCW);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.75f, 0.25f, 0.75f, 1.f);
}

} // namespace Vonsai::GL


// Verify OpenGL action
#define GL_ASSERT(funcToCheck) \
  ___glErrClear();             \
  funcToCheck;                 \
  ___glAssert(__FILE__, __LINE__);

// Avoid fake errors
static inline void ___glErrClear() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

// Parse real errors after a gl func is executed
static inline void ___glAssert(char const *file, int line) {
  if (auto glError = glGetError()) {
    char const *errStr;
    switch (glError) {
      case GL_INVALID_ENUM: errStr = "Invalid enum"; break;
      case GL_INVALID_VALUE: errStr = "Invalid value"; break;
      case GL_INVALID_OPERATION: errStr = "Invalid operation"; break;
      default: errStr = "Unrecognised GLenum"; break;
    }
    vo_print("\nOPENGL ERROR - {}:{}\n↪ ({}) {}\n", file, line, errStr, glError);
  }
}

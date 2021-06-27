#pragma once

#include <nucleus/Config.h>
#include <nucleus/HighResolutionTimer.h>
#include <nucleus/Macros.h>
#include <nucleus/Memory/ScopedPtr.h>
#include <nucleus/Profiling.h>
#include <nucleus/message_loop/message_loop.h>

#include <nucleus/main_header.hpp>

#include "canvas/Windows/Window.h"
#include "canvas/Windows/WindowDelegate.h"
#include "canvas/message_loop/message_pump_ui.h"

namespace ca {

template <typename DelegateType, typename... Args>
static I32 run(Args&&... args) {
  // The single window we are managing.
  ca::Window window;

  // The delegate that processes window state events.
  DelegateType delegate{std::forward<Args>(args)...};

  if (!window.initialize(&delegate)) {
    LOG(Error) << "Could not set up window.";
    return 1;
  }

  ca::MessagePumpUI pump{&window};
  nu::MessageLoop ml{&pump};
  ml.run();

  return 0;
}

}  // namespace ca

#if COMPILER(MSVC)
#define MEMORY_DUMP _CrtDumpMemoryLeaks();
#else
#define MEMORY_DUMP
#endif

#define CANVAS_APP(DelegateType)                                                                   \
  NU_MAIN_HEADER {                                                                                 \
    I32 result = 0;                                                                                \
    {                                                                                              \
      nu::Profiling profiling;                                                                     \
      result = run<DelegateType>();                                                                \
    }                                                                                              \
    MEMORY_DUMP                                                                                    \
    return result;                                                                                 \
  }

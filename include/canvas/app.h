#pragma once

#include <nucleus/config.h>
#include <nucleus/high_resolution_timer.h>
#include <nucleus/macros.h>
#include <nucleus/memory/scoped_ptr.h>
#include <nucleus/message_loop/message_loop.h>
#include <nucleus/profiling.h>

#include <nucleus/main_header.hpp>

#include "canvas/message_loop/message_pump_ui.h"
#include "canvas/windows/window.h"
#include "canvas/windows/window_delegate.h"

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
      result = ca::run<DelegateType>();                                                            \
    }                                                                                              \
    MEMORY_DUMP                                                                                    \
    return result;                                                                                 \
  }

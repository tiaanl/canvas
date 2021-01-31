#ifndef CANVAS_APP_H_
#define CANVAS_APP_H_

#include "canvas/Windows/Window.h"
#include "canvas/Windows/WindowDelegate.h"
#include "nucleus/Config.h"
#include "nucleus/HighPerformanceTimer.h"
#include "nucleus/Macros.h"
#include "nucleus/Memory/ScopedPtr.h"
#include "nucleus/Profiling.h"

#if OS(WIN32)
#include "nucleus/Win/WindowsMixin.h"
#endif

namespace ca {

template <typename T>
class App {
public:
  NU_DELETE_COPY_AND_MOVE(App);

  using DelegateType = T;

  // Construct a new app with the specified delegate that will control the app.
  App() = default;

  // Run the application and only return once all the windows are closed.
  I32 run() {
    if (!m_window.initialize(&m_delegate)) {
      LOG(Error) << "Could not set up window.";
      return 1;
    }

    auto tick = nu::getCurrentHighPerformanceTick();
    while (m_window.processEvents()) {
      auto now = nu::getCurrentHighPerformanceTick();
      m_delegate.tick(static_cast<F32>(1000000.0 / 60.0 / (now - tick)));
      tick = now;

      m_window.paint();
    }

    return 0;
  }

private:
  // The single window we are managing.
  Window m_window;

  // The delegate that processes window state events.
  DelegateType m_delegate;
};

}  // namespace ca

#if OS(WIN)
#define MAIN_HEADER int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
#define MAIN_HEADER int main(int, char*[])
#endif

#if COMPILER(MSVC)
#define MEMORY_DUMP _CrtDumpMemoryLeaks();
#else
#define MEMORY_DUMP
#endif

#define CANVAS_APP(DelegateType)                                                                   \
  MAIN_HEADER {                                                                                    \
    I32 result = 0;                                                                                \
    {                                                                                              \
      nu::Profiling profiling;                                                                     \
      ca::App<DelegateType> app;                                                                   \
      result = app.run();                                                                          \
    }                                                                                              \
    MEMORY_DUMP                                                                                    \
    return result;                                                                                 \
  }

#endif  // CANVAS_APP_H_

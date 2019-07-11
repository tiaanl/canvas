
#ifndef CANVAS_APP_H_
#define CANVAS_APP_H_

#include "canvas/Windows/Window.h"
#include "canvas/Windows/WindowDelegate.h"
#include "nucleus/Allocators/DefaultAllocator.h"
#include "nucleus/Config.h"
#include "nucleus/Macros.h"
#include "nucleus/Memory/ScopedPtr.h"
#include "nucleus/Win/WindowsMixin.h"

namespace ca {

template <typename T>
class App {
public:
  using DelegateType = T;

  // Construct a new app with the specified delegate that will control the app.
  App() = default;

  // Run the application and only return once all the windows are closed.
  I32 run() {
    if (!m_window.initialize(&m_delegate)) {
      LOG(Error) << "Could not set up window.";
      return 1;
    }

    while (m_window.processEvents()) {
      m_window.paint();
    }

    return 0;
  }

private:
  DELETE_COPY_AND_MOVE(App);

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
    ca::App<DelegateType> app;                                                                     \
    I32 result = app.run();                                                                        \
    MEMORY_DUMP                                                                                    \
    return result;                                                                                 \
  }

#endif  // CANVAS_APP_H_

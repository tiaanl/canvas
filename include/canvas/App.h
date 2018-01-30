
#ifndef CANVAS_APP_H_
#define CANVAS_APP_H_

#include "canvas/Windows/Window.h"
#include "canvas/Windows/WindowDelegate.h"
#include "nucleus/Allocators/Allocated.h"
#include "nucleus/Allocators/DefaultAllocator.h"
#include "nucleus/Config.h"
#include "nucleus/Macros.h"
#include "nucleus/Win/WindowsMixin.h"

namespace ca {

template <typename T>
class App {
public:
  using DelegateType = T;

  // Construct a new app with the specified delegate that will control the app.
  App() {}

  // Run the application and only return once all the windows are closed.
  void run() {
    // Set up the window.
    m_window = Window::create(&m_delegate, m_delegate.getTitle());

    while (m_window->processEvents()) {
      m_window->paint();
    }
  }

private:
  COPY_DELETE(App);
  MOVE_DELETE(App);

  DelegateType m_delegate;

  // The single window we are managing.
  std::unique_ptr<Window> m_window;
};

}  // namespace ca

#if OS(WIN)
#define MAIN_HEADER int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
#define MAIN_HEADER int main(int, char* [])
#endif

#if COMPILER(MSVC)
#define MEMORY_DUMP _CrtDumpMemoryLeaks();
#else
#define MEMORY_DUMP
#endif

#define CANVAS_APP(DelegateType)                                                                                       \
  MAIN_HEADER {                                                                                                        \
    {                                                                                                                  \
      ca::App<DelegateType> app;                                                                                       \
      app.run();                                                                                                       \
    }                                                                                                                  \
    MEMORY_DUMP                                                                                                        \
    return 0;                                                                                                          \
  }

#endif  // CANVAS_APP_H_

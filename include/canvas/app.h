
#ifndef CANVAS_APP_H_
#define CANVAS_APP_H_

#include "canvas/windows/window_delegate.h"
#include "nucleus/Memory/ScopedPtr.h"
#include "nucleus/config.h"
#include "nucleus/macros.h"
#include "nucleus/win/windows_mixin.h"

namespace ca {

class Window;

class App {
public:
  // Construct a new app with the specified delegate that will control the app.
  explicit App(WindowDelegate* delegate);

  // Destruct the app.
  ~App();

  // Run the application and only return once all the windows are closed.
  void run();

private:
  // The single window we are managing.
  nu::ScopedPtr<Window> m_window;

  DISALLOW_COPY_AND_ASSIGN(App);
};

}  // namespace ca

#if OS(WIN)
#define MAIN_HEADER int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
#define MAIN_HEADER int main(int argc, char* argv[])
#endif

#if COMPILER(MSVC)
#define MEMORY_DUMP _CrtDumpMemoryLeaks();
#else
#define MEMORY_DUMP
#endif

#define CANVAS_APP(DelegateType)                                                                                       \
  MAIN_HEADER {                                                                                                        \
    {                                                                                                                  \
      nu::ScopedPtr<DelegateType> d = nu::MakeScopedPtr<DelegateType>();                                               \
      ca::App app{d.get()};                                                                                            \
      app.run();                                                                                                       \
    }                                                                                                                  \
    MEMORY_DUMP                                                                                                        \
    return 0;                                                                                                          \
  }

#endif  // CANVAS_APP_H_

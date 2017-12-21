
#ifndef CANVAS_APP_H_
#define CANVAS_APP_H_

#include "canvas/Windows/WindowDelegate.h"
#include "nucleus/Config.h"
#include "nucleus/Macros.h"
#include "nucleus/Memory/Allocated.h"
#include "nucleus/Win/WindowsMixin.h"

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
  nu::Allocated<Window> m_window;

  DISALLOW_COPY_AND_ASSIGN(App);
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

#define CANVAS_APP(DelegateType)                                                                                       \
  MAIN_HEADER {                                                                                                        \
    {                                                                                                                  \
      auto d = nu::allocate<DelegateType>(nu::getDefaultAllocator());                                                  \
      ca::App app{d.get()};                                                                                            \
      app.run();                                                                                                       \
    }                                                                                                                  \
    MEMORY_DUMP                                                                                                        \
    return 0;                                                                                                          \
  }

#endif  // CANVAS_APP_H_

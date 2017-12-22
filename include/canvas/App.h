
#ifndef CANVAS_APP_H_
#define CANVAS_APP_H_

#include "canvas/Resources/ResourceManager.h"
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
  explicit App(WindowDelegate* delegate, nu::Allocator* allocator = nu::getDefaultAllocator());

  // Destruct the app.
  ~App();

  // Run the application and only return once all the windows are closed.
  void run();

private:
  nu::Allocator* m_allocator;

  // The single window we are managing.
  nu::Allocated<Window> m_window;

  ResourceManager m_resourceManager;

  DISALLOW_COPY_AND_ASSIGN(App);
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
      nu::GlobalAllocator allocator;                                                                                   \
      auto d = nu::allocate<DelegateType>(&allocator);                                                                 \
      ca::App app{d.get(), &allocator};                                                                                 \
      app.run();                                                                                                       \
    }                                                                                                                  \
    MEMORY_DUMP                                                                                                        \
    return 0;                                                                                                          \
  }

#endif  // CANVAS_APP_H_

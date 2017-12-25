
#include "canvas/App.h"

#include "canvas/Windows/Window.h"
#include "nucleus/Logging.h"
#include "nucleus/Utils/Files.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

App::App(nu::Allocator* allocator) : m_allocator(allocator), m_window(m_allocator) {}

App::~App() = default;

void App::run(WindowDelegate* delegate) {
  // Set up the window.
  m_window = Window::create(nu::getDefaultAllocator(), delegate, delegate->getTitle());

  while (m_window->processEvents()) {
    m_window->paint();
  }
}

}  // namespace ca

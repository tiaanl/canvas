
#include "canvas/App.h"

#include "canvas/Windows/Window.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

App::App(WindowDelegate* delegate) : m_window(Window::create(delegate, delegate->getTitle())) {}

App::~App() {}

void App::run() {
  while (m_window->processEvents()) {
    m_window->paint();
  }
}

}  // namespace ca

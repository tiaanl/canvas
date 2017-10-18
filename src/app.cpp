
#include "canvas/app.h"

#include "canvas/windows/window.h"

namespace ca {

App::App(WindowDelegate* delegate) : m_window(Window::create(delegate, delegate->getTitle())) {}

App::~App() {}

void App::run() {
  while (m_window->processEvents()) {
    m_window->paint();
  }
}

}  // namespace ca

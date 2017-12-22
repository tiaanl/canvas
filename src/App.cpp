
#include "canvas/App.h"

#include "canvas/Windows/Window.h"
#include "nucleus/Logging.h"
#include "nucleus/Utils/Files.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

App::App(nu::Allocator* allocator) : m_allocator(allocator), m_window(m_allocator), m_resourceManager(allocator) {}

App::~App() = default;

void App::run(WindowDelegate* delegate) {
  nu::FilePath rootPath{nu::getCurrentWorkingDirectory(m_allocator), m_allocator};

  LOG(Info) << "Resource directory: " << rootPath;

  // Set up the resource manager.
  m_resourceManager.setRootPath(nu::getCurrentWorkingDirectory(m_allocator));

  // Set up the window.
  m_window = Window::create(nu::getDefaultAllocator(), delegate, delegate->getTitle());

  while (m_window->processEvents()) {
    m_window->paint();
  }
}

}  // namespace ca


#include "canvas/App.h"

#include "canvas/Windows/Window.h"
#include "nucleus/Logging.h"
#include "nucleus/Utils/Files.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

App::App(WindowDelegate* delegate, nu::Allocator* allocator)
  : m_allocator(allocator), m_window(Window::create(nu::getDefaultAllocator(), delegate, delegate->getTitle())),
    m_resourceManager(allocator) {}

App::~App() {}

void App::run() {
  nu::FilePath rootPath{nu::getCurrentWorkingDirectory(m_allocator), m_allocator};

  LOG(Info) << "Resource directory: " << rootPath;

  // Set up the resource manager.
  m_resourceManager.setRootPath(nu::getCurrentWorkingDirectory(m_allocator));

  while (m_window->processEvents()) {
    m_window->paint();
  }
}

}  // namespace ca

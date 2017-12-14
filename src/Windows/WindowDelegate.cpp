
#include "canvas/Windows/WindowDelegate.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

bool WindowDelegate::onWindowCreated() {
  return true;
}

void WindowDelegate::onWindowResized(const Size<U32>& size) {}

void WindowDelegate::onMouseMoved(const MouseEvent& evt) {}

void WindowDelegate::onMousePressed(const MouseEvent& evt) {}

void WindowDelegate::onMouseReleased(const MouseEvent& evt) {}

void WindowDelegate::onMouseWheel(const MouseWheelEvent& evt) {}

void WindowDelegate::onKeyPressed(const KeyEvent& evt) {}

void WindowDelegate::onKeyReleased(const KeyEvent& evt) {}

}  // namespace ca

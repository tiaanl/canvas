
#include "canvas/Windows/WindowDelegate.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

bool WindowDelegate::onWindowCreated(Renderer*) {
  return true;
}

void WindowDelegate::onWindowResized(const Size<U32>&) {}

void WindowDelegate::onMouseMoved(const MouseEvent&) {}

void WindowDelegate::onMousePressed(const MouseEvent&) {}

void WindowDelegate::onMouseReleased(const MouseEvent&) {}

void WindowDelegate::onMouseWheel(const MouseWheelEvent&) {}

void WindowDelegate::onKeyPressed(const KeyEvent&) {}

void WindowDelegate::onKeyReleased(const KeyEvent&) {}

}  // namespace ca

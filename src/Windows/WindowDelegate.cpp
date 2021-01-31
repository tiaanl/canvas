
#include "canvas/Windows/WindowDelegate.h"

namespace ca {

class Window;

bool WindowDelegate::onWindowCreated(Window*) {
  return true;
}

void WindowDelegate::tick(F32 NU_UNUSED(delta)) {}

void WindowDelegate::onWindowResized(const fl::Size&) {}

void WindowDelegate::onMouseMoved(const MouseEvent&) {}

bool WindowDelegate::onMousePressed(const MouseEvent&) {
  return true;
}

void WindowDelegate::onMouseReleased(const MouseEvent&) {}

void WindowDelegate::onMouseWheel(const MouseWheelEvent&) {}

void WindowDelegate::onKeyPressed(const KeyEvent&) {}

void WindowDelegate::onKeyReleased(const KeyEvent&) {}

}  // namespace ca

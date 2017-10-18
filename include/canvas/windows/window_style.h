
#ifndef CANVAS_WINDOWS_WINDOW_STYLE_H_
#define CANVAS_WINDOWS_WINDOW_STYLE_H_

namespace ca {

enum WindowStyle {
  // No border or title bar.  (this flag and all others are mutually exclusive)
  WindowStyleNone = 0,

  // Title bar and fixed border.
  WindowStyleTitleBar = 1 << 0,

  // Title bar and resizable border and maximize button.
  WindowStyleResize = 1 << 1,

  // Title bar and close button.
  WindowStyleClose = 1 << 2,

  // Fullscreen mode.  (this flag and all others are mutually exclusive)
  WindowStyleFullscreen = 1 << 3,

  // Default window style.
  WindowStyleDefault = WindowStyleTitleBar | WindowStyleResize | WindowStyleClose,
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_STYLE_H_

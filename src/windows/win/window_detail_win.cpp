// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "canvas/windows/win/window_detail_win.h"

#include <nucleus/logging.h>

#include "canvas/windows/window_style.h"

namespace {

// The name of the window class we register.
const wchar_t* kWindowClassName = L"canvasWindow";

// Holds track of how many windows we have open.
uint32_t g_windowCount = 0;

// Holds a pointer to the single fullscreen window.
ca::detail::WindowDetailWin* g_fullscreenWindow = nullptr;

}  // namespace

namespace ca {

namespace detail {

WindowDetailWin::WindowDetailWin(VideoMode mode, const std::string& title,
                                 uint32_t style,
                                 const ContextSettings& settings)
  : m_lastSize(mode.width, mode.height) {
#if 0
  // Set that this process is DPI aware and can handle DPI scaling.
  setProcessDpiAware();
#endif  // 0

  // Register the window class when we create the first window.
  if (g_windowCount == 0) {
    registerWindowClass();
  }

  // Get the initial position and size.
  HDC screenDC = ::GetDC(nullptr);
  int left =
      (::GetDeviceCaps(screenDC, HORZRES) - static_cast<int>(mode.width)) / 2;
  int top =
      (::GetDeviceCaps(screenDC, VERTRES) - static_cast<int>(mode.height)) / 2;
  int width = mode.width;
  int height = mode.height;
  ::ReleaseDC(nullptr, screenDC);

  // Choose the window style according to the style parameter.
  DWORD winStyle = WS_VISIBLE;
  if (style == WindowStyleNone) {
    winStyle |= WS_POPUP;
  } else {
    if (IS_BIT_SET(style, WindowStyleTitleBar)) {
      winStyle |= WS_CAPTION | WS_MINIMIZEBOX;
    }

    if (IS_BIT_SET(style, WindowStyleResize)) {
      winStyle |= WS_THICKFRAME | WS_MAXIMIZEBOX;
    }

    if (IS_BIT_SET(style, WindowStyleClose)) {
      winStyle |= WS_SYSMENU;
    }
  }

  // In windowed mode, adjust the width and height so that the client size will
  // have the requested size.
  bool fullscreen = IS_BIT_SET(style, WindowStyleFullscreen);
  if (!fullscreen) {
    RECT windowRect = {0, 0, width, height};
    ::AdjustWindowRect(&windowRect, winStyle, false);
    width = windowRect.right - windowRect.left;
    height = windowRect.bottom - windowRect.top;
  }

  // Convert the window title to a wide character format.
  std::wstring tempTitle(title.begin(), title.end());

  // Create the window handle.
  m_handle = ::CreateWindowW(kWindowClassName, tempTitle.c_str(), winStyle,
                             left, top, width, height, nullptr, nullptr,
                             ::GetModuleHandleW(nullptr), this);

  // By default, the OS limits the size of the window to the desktop size, so we
  // have to resize it after creation to apply the real size.
  setSize(Size<uint32_t>(mode.width, mode.height));

  if (fullscreen) {
    switchToFullscreen(mode);
  }

  // Increment the open window count.
  ++g_windowCount;
}

WindowDetailWin::WindowDetailWin(WindowHandle handle) : m_handle(handle) {
#if 0
  // Set that this process is DPI aware and can handle DPI scaling.
  setProcessDpiAware();
#endif  // 0

  if (m_handle) {
    // We change the event procedure of the control.  (It is important to save
    // the old one and restore it later.)
    ::SetWindowLongPtr(m_handle, GWLP_USERDATA,
                       reinterpret_cast<LONG_PTR>(this));
    m_callback = ::SetWindowLongPtrW(
        m_handle, GWLP_WNDPROC,
        reinterpret_cast<LONG_PTR>(&WindowDetailWin::onEvent));
  }
}

WindowDetailWin::~WindowDetailWin() {
  if (!m_callback) {
    // Destroy the window.
    if (m_handle) {
      ::DestroyWindow(m_handle);
    }

    // Decrement the global window count.
    --g_windowCount;

    // Unregister the window class if we were the last window.
    if (!g_windowCount) {
      ::UnregisterClassW(kWindowClassName, ::GetModuleHandleW(nullptr));
    }
  } else {
    // The window is external, so remove the hook on it's message callback.
    ::SetWindowLongPtr(m_handle, GWLP_WNDPROC, m_callback);
  }
}

WindowHandle WindowDetailWin::getNativeHandle() const {
  return m_handle;
}

Pos<int32_t> WindowDetailWin::getPosition() const {
  RECT rect;
  ::GetWindowRect(m_handle, &rect);

  return Pos<int32_t>(rect.left, rect.top);
}

void WindowDetailWin::setPosition(const Pos<int32_t>& pos) {
  ::SetWindowPos(m_handle, nullptr, pos.x, pos.y, 0, 0,
                 SWP_NOSIZE | SWP_NOZORDER);
}

Size<uint32_t> WindowDetailWin::getSize() const {
  RECT rect;
  ::GetClientRect(m_handle, &rect);

  return Size<uint32_t>(rect.right - rect.left, rect.bottom - rect.top);
}

void WindowDetailWin::setSize(const Size<uint32_t>& size) {
  // SetWindowPos wants the total size of the window (including the title bar
  // and borders), so we have to compute it.
  RECT windowRect = {0, 0, static_cast<long>(size.width),
                     static_cast<long>(size.height)};
  ::AdjustWindowRect(&windowRect, ::GetWindowLong(m_handle, GWL_STYLE), false);
  int width = windowRect.right - windowRect.left;
  int height = windowRect.bottom - windowRect.top;

  ::SetWindowPos(m_handle, nullptr, 0, 0, width, height,
                 SWP_NOMOVE | SWP_NOZORDER);
}

void WindowDetailWin::setTitle(const std::string& title) {
  std::wstring tempTitle(title.begin(), title.end());
  ::SetWindowTextW(m_handle, tempTitle.c_str());
}

void WindowDetailWin::setVisible(bool visible) {
  ::ShowWindow(m_handle, visible ? SW_SHOW : SW_HIDE);
}

void WindowDetailWin::setMouseCursorVisible(bool visible) {
#if 0
  if (visible) {
    m_cursor = ::LoadCursorW(nullptr, IDC_ARROW);
  } else {
    m_cursor = nullptr;
  }

  ::SetCursor(m_cursor);
#endif  // 0
}

void WindowDetailWin::setKeyRepeatEnabled(bool enabled) {
  m_keyRepeatEnabled = enabled;
}

void WindowDetailWin::requestFocus() {
  // Allow focus stealing only within the same process; compare PID's of the
  // current and foreground windows.
  DWORD thisPid = ::GetWindowThreadProcessId(m_handle, NULL);
  DWORD foregroundPid =
      ::GetWindowThreadProcessId(::GetForegroundWindow(), nullptr);

  if (thisPid == foregroundPid) {
    // The window requesting focus belongs to the same process as the current,
    // so steal the focus.
    ::SetForegroundWindow(m_handle);
  } else {
#if 0
    // Requested from a different process, so don't steal focus, but create a
    // taskbar notification (flash).
    FLASHINFO info;
    info.cbSize = sizeof(info);
    info.hwnd = m_handle;
    info.dwFlags = FLASHW_TRAY;
    info.dwTimeout = 0;
    info.uCount = 3;

    ::FlashWindowEx(&info);
#endif  // 0
  }
}

bool WindowDetailWin::hasFocus() const {
  return m_handle == ::GetForegroundWindow();
}

void WindowDetailWin::registerWindowClass() {
  WNDCLASSW wc;
  wc.style = 0;
  wc.lpfnWndProc = &WindowDetailWin::onEvent;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = ::GetModuleHandleW(nullptr);
  wc.hIcon = nullptr;
  wc.hCursor = 0;
  wc.hbrBackground = 0;
  wc.lpszMenuName = nullptr;
  wc.lpszClassName = kWindowClassName;
  ::RegisterClassW(&wc);
}

void WindowDetailWin::switchToFullscreen(const VideoMode& mode) {
  DEVMODEW devMode;
  devMode.dmSize = sizeof(devMode);
  devMode.dmPelsWidth = mode.width;
  devMode.dmPelsHeight = mode.height;
  devMode.dmBitsPerPel = mode.bitsPerPixel;
  devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

  // Apply fullscreen mode.
  if (::ChangeDisplaySettingsW(&devMode, CDS_FULLSCREEN) !=
      DISP_CHANGE_SUCCESSFUL) {
    LOG(Error) << "Failed to change display mode to fullscreen.";
    return;
  }

  // Make the window flags compatible with fullscreen mode.
  ::SetWindowLongW(m_handle, GWL_STYLE,
                   WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
  ::SetWindowLongW(m_handle, GWL_EXSTYLE, WS_EX_APPWINDOW);

  // Resize the window so that it fits the entire screen.
  ::SetWindowPos(m_handle, HWND_TOP, 0, 0, mode.width, mode.height,
                 SWP_FRAMECHANGED);
  ::ShowWindow(m_handle, SW_SHOW);

  // Set "this" as the current fullscreen window.
  g_fullscreenWindow = this;
}

void WindowDetailWin::cleanup() {
  // Restore the previous video mode (in case we were running fullscreen).
  if (g_fullscreenWindow == this) {
    ::ChangeDisplaySettingsW(nullptr, 0);
    g_fullscreenWindow = nullptr;
  }

  // Unhide the mouse (in case it was hidden).
  setMouseCursorVisible(true);

  // No longer track the cursor.
  setMouseTracking(false);

  // No longer capture the cursor.
  ::ReleaseCapture();
}

void WindowDetailWin::setMouseTracking(bool tracking) {
  TRACKMOUSEEVENT mouseEvent;
  mouseEvent.cbSize = sizeof(mouseEvent);
  mouseEvent.dwFlags = tracking ? TME_LEAVE : TME_CANCEL;
  mouseEvent.hwndTrack = m_handle;
  mouseEvent.dwHoverTime = HOVER_DEFAULT;
  ::TrackMouseEvent(&mouseEvent);
}

void WindowDetailWin::processEvent(UINT message, WPARAM wParam, LPARAM lParam) {
  // Don't process any messages until window is created.
  if (m_handle == nullptr) {
    return;
  }

  switch (message) {
    // Destroy event.
    case WM_DESTROY: {
      cleanup();
      break;
    }

#if 0
    // Set cursor event.
    case WM_SETCURSOR: {
      // The mouse has moved, if the cursor is in our window we must refresh the
      // cursor.
      if (LOWORD(lParam) == HTCLIENT) {
        ::SetCursor(m_cursor);
      }
      break;
    }
#endif  // 0

    // Start resizing.
    case WM_ENTERSIZEMOVE: {
      m_isResizing = true;
      break;
    }

    // Stop resizing.
    case WM_EXITSIZEMOVE: {
      m_isResizing = false;

      // Ignore cases where the window has only been moved.
      if (m_lastSize != getSize()) {
        // Update the last handled size.
        m_lastSize = getSize();

#if 0
                // Push a resize event
                Event event;
                event.type        = Event::Resized;
                event.size.width  = m_lastSize.x;
                event.size.height = m_lastSize.y;
                pushEvent(event);
#endif  // 0
      }
      break;
    }
  }
}

LRESULT CALLBACK WindowDetailWin::onEvent(HWND handle, UINT message,
                                          WPARAM wParam, LPARAM lParam) {
  // Associate handle and window instance when the creation message is received.
  if (message == WM_CREATE) {
    // Get the WindowDetailWin instance.
    LONG_PTR instance = reinterpret_cast<LONG_PTR>(
        reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

    // Set the user data to the instance.
    ::SetWindowLongPtr(handle, GWLP_USERDATA, instance);
  }

  // Get the instance from the window handle.
  WindowDetailWin* instance =
      handle ? reinterpret_cast<WindowDetailWin*>(
                   ::GetWindowLongPtrW(handle, GWLP_USERDATA))
             : nullptr;

  // Forward the event to the appropriate function.
  if (instance) {
    instance->processEvent(message, wParam, lParam);

    if (instance->m_callback) {
      return ::CallWindowProcW(reinterpret_cast<WNDPROC>(instance->m_callback),
                               handle, message, wParam, lParam);
    }
  }

  // We don't forward WM_CLOSE message to prevent the OS from automatically
  // destroying the window.
  if (message == WM_CLOSE) {
    return 0;
  }

  // Don't forward the menu system command, so that pressing ALT or F10 doesn't
  // steal the focus.
  if (message == WM_SYSCOMMAND && wParam == SC_KEYMENU) {
    return 0;
  }

  // Handle the message with the default handler.
  return ::DefWindowProcW(handle, message, wParam, lParam);
}

}  // namespace detail

}  // namespace ca

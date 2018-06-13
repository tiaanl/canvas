
#include "canvas/Windows/MessageLoop/MessageWindow.h"

#include "nucleus/Logging.h"

namespace ca {

namespace {

const wchar_t kMessageWindowClassName[] = L"MessageWindow";

}  // namespace

class MessageWindow::WindowClass {
public:
  WindowClass() : m_atom(0), m_instance(::GetModuleHandleW(nullptr)) {
    WNDCLASSEXW wc;
    wc.cbSize = sizeof(wc);
    wc.style = 0;
    wc.lpfnWndProc = windowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_instance;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = kMessageWindowClassName;
    wc.hIconSm = NULL;
    m_atom = ::RegisterClassExW(&wc);
    if (m_atom == 0) {
      LOG(Fatal) << "Failed to register the window class for a message-only window";
    }
  }

  ~WindowClass() {
    if (m_atom != 0) {
      BOOL result = ::UnregisterClass(MAKEINTATOM(m_atom), m_instance);
      DCHECK(result);
    }
  }

  ATOM getAtom() {
    return m_atom;
  }

  HINSTANCE getInstance() {
    return m_instance;
  }

private:
  ATOM m_atom;
  HINSTANCE m_instance;
};

namespace {

static MessageWindow::WindowClass g_windowClass;

}  // namespace

MessageWindow::MessageWindow() = default;

MessageWindow::~MessageWindow() {
  // TODO: Check that this is called on the thread where `this` was created.

  if (m_handle != nullptr) {
    BOOL result = ::DestroyWindow(m_handle);
    DCHECK(result);
  }
}

bool MessageWindow::create(MessageCallback messageCallback) {
  return doCreate(std::move(messageCallback), NULL);
}

bool MessageWindow::createNamed(MessageCallback messageCallback, const LPWSTR windowName) {
  return doCreate(std::move(messageCallback), windowName);
}

// static
HWND MessageWindow::findWindow(const LPWSTR windowName) {
  return FindWindowExW(HWND_MESSAGE, NULL, kMessageWindowClassName, windowName);
}

bool MessageWindow::doCreate(MessageCallback messageCallback, const LPWSTR windowName) {
  // TODO: Check that this is called on the thread where `this` was created.

  DCHECK(m_messageCallback == nullptr);
  DCHECK(!m_handle);

  m_messageCallback = std::move(messageCallback);

  WindowClass& windowClass = g_windowClass;
  m_handle = ::CreateWindowExW(0, MAKEINTATOM(windowClass.getAtom()), windowName, 0, 0, 0, 0, 0, HWND_MESSAGE, 0,
                               windowClass.getInstance(), this);
  if (!m_handle) {
    LOG(Fatal) << "Failed to create a message-only window";
    return false;
  }

  return true;
}

// static
LRESULT CALLBACK MessageWindow::windowProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam) {
  MessageWindow* self = reinterpret_cast<MessageWindow*>(GetWindowLongPtrW(wnd, GWLP_USERDATA));

  switch (message) {
    // Set up the `self` before handling WM_CREATE.
    case WM_CREATE: {
      CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
      self = reinterpret_cast<MessageWindow*>(cs->lpCreateParams);

      // Make `wnd` available to the message handler.  At this point the control hasn't returned from
      // `CreateWindowExW()` yet.
      self->m_handle = wnd;

      // Store pointer to the `self` to the window's user data.
      ::SetLastError(ERROR_SUCCESS);
      LONG_PTR result = ::SetWindowLongPtrW(wnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
      DCHECK(result != 0 || GetLastError() == ERROR_SUCCESS);
      break;
    }

    // Clear the pointer to stop calling `self` once WM_DESTROY is received.
    case WM_DESTROY: {
      ::SetLastError(ERROR_SUCCESS);
      LONG_PTR result = ::SetWindowLongPtrW(wnd, GWLP_USERDATA, NULL);
      DCHECK(result != 0 || GetLastError() == ERROR_SUCCESS);
      break;
    }
  }

  // Handle the message.
  if (self) {
    LRESULT messageResult;
    if (self->m_messageCallback(message, wParam, lParam, &messageResult)) {
      return messageResult;
    }
  }

  return ::DefWindowProcW(wnd, message, wParam, lParam);
}

}  // namespace ca

#if 0



}  // namespace win
}  // namespace base

#endif  // 0

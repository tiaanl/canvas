
#ifndef CANVAS_WINDOWS_MESSAGE_LOOP_MESSAGE_WINDOW_H_
#define CANVAS_WINDOWS_MESSAGE_LOOP_MESSAGE_WINDOW_H_

#include "nucleus/Macros.h"
#include "nucleus/Win/WindowsMixin.h"

namespace ca {

class MessageWindow {
public:
  COPY_DELETE(MessageWindow);
  MOVE_DELETE(MessageWindow);

  // Used to register a process-wide message window class.
  class WindowClass;

  // Implement this callback to handle messages received by the message window.  If the callback returns `false`, the
  // first four parameters are passed to `::DefWindowProc()`.  Otherwise, `*result` is returned by the window procedure.
  using MessageCallback = bool (*)(UINT message, WPARAM wparam, LPARAM lparam, LRESULT* result);

  MessageWindow();
  ~MessageWindow();

  // Creates a message-only window.  The incoming messages will be passed by `m_messageCallback`.  `m_message_callback`
  // must outlive `this`.
  bool create(MessageCallback messageCallback);

  // Same as `create()`, but assigns the given name to the created window.
  bool createNamed(MessageCallback messageCallback, const LPWSTR windowName);

  HWND getHandle() const {
    return m_handle;
  }

  // Retrieves a handle of the first message-only window with matching `windowName`.
  static HWND findWindow(const LPWSTR windowName);

private:
  // Give `WindowClass` access to `WindowProc()`.
  friend class WindowClass;

  // Contains the actual window creation code.
  bool doCreate(MessageCallback messageCallback, const LPWSTR windowName);

  // Invoked by the OS to process incoming window messages.
  static LRESULT CALLBACK windowProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam);

  // Invoked to handle messages received by the window.
  MessageCallback m_messageCallback = nullptr;

  // Handle of the input window.
  HWND m_handle = nullptr;
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_MESSAGE_LOOP_MESSAGE_WINDOW_H_

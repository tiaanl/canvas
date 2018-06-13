
#ifndef CANVAS_WINDOWS_MESSAGE_LOOP_MESSAGE_PUMP_UI_H_
#define CANVAS_WINDOWS_MESSAGE_LOOP_MESSAGE_PUMP_UI_H_

#include "canvas/Windows/MessageLoop/MessageWindow.h"
#include "nucleus/MessageLoop/MessagePump.h"
#include "nucleus/Win/WindowsMixin.h"

namespace ca {

#if 0
class MessagePumpUI : public nu::MessagePump {
public:
  MessagePumpUI();
  ~MessagePumpUI() override;

  // Override: nu::MessagePump
  void run(Delegate* delegate) override;
  void quit() override;
  void scheduleWork() override;

private:
  MessageWindow m_messageWindow;
};
#endif  // 0

#if 0
class MessagePumpWin : public nu::MessagePump {
public:
  MessagePumpWin();

  // Override: MessagePump
  void run(Delegate* delegate) override;
  void quit() override;

protected:
  struct RunState {
    Delegate* delegate;

    // Used to flag that the current `run()` invocation should return ASAP.
    bool shouldQuit;

    // Used to count how many `run()` invocations are on the stack.
    int runDepth;
  };

  // State used with `m_workState` variable.
  enum class WorkState {
    // Ready to accept new work.
    Ready = 0,

    // New work has been signalled.
    HaveWork = 1,

    // Handling work.
    Working = 2,
  };

  virtual void doRunLoop() = 0;

  // A value used to indicate if there is a `kMsgDoWork` message pending in the Windows Message queue.  There is at most
  // one such message and it can drive execution of tasks when a native message pump is running.
  LONG m_workState = WorkState::Ready;

  // State for the current invocation of `run()`.
  RunState* m_runState = nullptr;
};

class MessagePumpUI : public MessagePumpWin {
public:
  MessagePumpUI();
  ~MessagePumpUI() override;

  // Override: MessagePump
  void scheduleWork() override;

private:
  bool MessageCallback(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* result);

  void doRunLoop() override;
  void waitForWork();
  void handleWorkMessage();
  bool processNextWindowsMessage();
  bool processMessageHelper(const MSG& msg);
  bool processPumpReplacementMessage();

  // m_messageWindow?
};
#endif  // 0

#if 0
 private:
  bool MessageCallback(
      UINT message, WPARAM wparam, LPARAM lparam, LRESULT* result);
  void DoRunLoop() override;
  void WaitForWork();
  void HandleWorkMessage();
  void HandleTimerMessage();
  void RescheduleTimer();
  bool ProcessNextWindowsMessage();
  bool ProcessMessageHelper(const MSG& msg);
  bool ProcessPumpReplacementMessage();

  base::win::MessageWindow message_window_;
};
#endif  // 0

}  // namespace ca

#endif  // CANVAS_WINDOWS_MESSAGE_LOOP_MESSAGE_PUMP_UI_H_


#include "canvas/Windows/MessageLoop/MessagePumpUI.h"
#include "nucleus/Logging.h"

#if 0

namespace ca {

namespace {

bool messageCallback(UINT message, WPARAM wparam, LPARAM lparam, LRESULT* result) {
  switch (message) {
    case kMsgHaveWork:
      handleWorkMessage();
      break;
  }

  return false;
}

}  // namespace

MessagePumpUI::MessagePumpUI() {
  bool result = m_messageWindow.create(&messageCallback);
  DCHECK(result);
}

MessagePumpUI::~MessagePumpUI() = default;

void MessagePumpUI::run(Delegate* delegate) {}

void MessagePumpUI::quit() {}

void MessagePumpUI::scheduleWork() {}

#if 0
namespace {

// Message sent to get an additional time slice for pumping another task.
static const int kMsgDoWork = WM_USER + 1;

}  // namespace

MessagePumpWin::MessagePumpWin() = default;

void MessagePumpWin::run(Delegate* delegate) {
  RunState s;
  s.delegate = delegate;
  s.shouldQuit = false;
  s.runDepth = m_runState ? m_runState->runDepth + 1 : 1;

  RunState* previousRunState = m_runState;
  m_runState = &s;

  doRunLoop();

  m_runState = previousRunState;
}

void MessagePumpWin::quit() {
  DCHECK(m_runState);
  m_runState->shouldQuit = true;
}

MessagePumpUI::MessagePumpUI() {
  // bool succeeded = m_messageWindow.create(BindRepeating(&MessagePumpUI::MessageCallback, Unretained(this)));
  // DCHECK(succeeded);
}

MessagePumpUI::~MessagePumpUI() = default;

void MessagePumpUI::scheduleWork() {
  if (::InterlockedExchange(&m_workState, WorkState::HaveWork) != WorkState::Ready) {
    return;
  }

  // Make sure the MessagePump does some work for us.
  BOOL ret = ::PostMessage(m_messageWindow.getHandle(), kMsgDoWork, 0, 0);
  if (ret) {
    // There was room in the Windows Message queue.
    return;
  }

  // Clarify that we didn't really insert.
  ::InterlockedExchange(&m_workState, WorkState::Ready);
}

bool MessagePumpUI::MessageCallback(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* result) {
  switch (message) {
    case kMsgDoWork:
      handleWorkMessage();
      break;
  }

  return false;
}

void MessagePumpUI::doRunLoop() {
  // IF this was just a simple PeekMessage() loop (servicing all possible work queues), then Windows would try to
  // achieve the following order according to MSDN documentation about PeekMessage with no filter):
  //
  //   - Sent messages
  //   - Posted messages
  //   - Sent messages (again)
  //   - WM_PAINT messages
  //   - WM_TIMER messages
  //
  // Summary: none of the above classes is starved, and sent messages has twice the chance of being processed (i.e.,
  // reduced service time).

  for (;;) {
    // If we do any work, we may create more messages etc., and more work may possibly be waiting in another task group.
    // When we (for example) processNextWindowsMessage(), there is a good chance there are still more messages waiting.
    // On the other hand, when any of these methods return having done no work, then it is pretty unlikely that calling
    // them again quickly will find any work to do.  Finally, if they all say they had no work, then it is a good time
    // to consider sleeping (waiting) for more work.

    bool moreWorkIsPlausible = processNextWindowsMessage();
    if (m_runState->shouldQuit) {
      break;
    }

    moreWorkIsPlausible |= m_runState->delegate->doWork();
    if (m_runState->shouldQuit) {
      break;
    }

    moreWorkIsPlausible |= m_runState->delegate->doDelayedWork(&delayed_work_time_);
    // If we did not process any delayed work, then we can assume that our
    // existing WM_TIMER if any will fire when delayed work should run.  We
    // don't want to disturb that timer if it is already in flight.  However,
    // if we did do all remaining delayed work, then lets kill the WM_TIMER.
    if (moreWorkIsPlausible && delayed_work_time_.is_null())
      KillTimer(m_messageWindow.getHandle(), reinterpret_cast<UINT_PTR>(this));
    if (m_runState->shouldQuit)
      break;

    if (moreWorkIsPlausible)
      continue;

    moreWorkIsPlausible = m_runState->delegate->doIdleWork();
    if (m_runState->shouldQuit)
      break;

    if (moreWorkIsPlausible)
      continue;

    // Wait (sleep) until we have work to do again.
    waitForWork();
  }
}

void MessagePumpUI::waitForWork() {
  // Wait until a message is available.
  int delay = INFINITE;
  DWORD waitFlags = MWMO_INPUTAVAILABLE;

  while (;;) {
    DWORD result = ::MsgWaitForMultipleObjectsEx(0, nullptr, delay, QS_ALLINPUT, waitFlags);

    if (result == WAIT_OBJECT_0) {
      // A WM_* message is available.
      //
      // The subsequent `::PeekMessages` call may fail to return any messages thus causing us to enter a tight loop at
      // times.  The code below is a workaround to give the child window some time to process its input messages by
      // looping back to MsgWaitForMultipleObjectsEx above when there are no messages for the current thread.
      MSG msg = {0};
      bool hasPendingSentMessage = (HIWORD(::GetQueueStatus(QS_SENDMESSAGE)) & QS_SENDMESSAGE) != 0;
      if (hasPendingSentMessage || ::PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
        return;
      }

      // We know there are no more messages for this thread because `::PeekMessage` has returned false. Reset
      // `waitFlags` so that we wait for a *new* message.
      waitFlags = 0;
    }

    DCHECK(result != WAIT_FAILED) << GetLastError();
  }
}

void MessagePumpUI::handleWorkMessage() {
  // If we are being called outside of the context of `run()`, then don't try to do any work.  This could correspond to
  // a `::MessageBox` call or something of that sort.
  if (!m_workState) {
    // Since we handled a `kMsgHaveWork` message, we must still update this flag.
    ::InterlockedExchange(&m_workState, WorkState::Ready);
    return;
  }

  processPumpReplacementMessage();

  // Now give the delegate a chance to do some work.  It'll let us know if it needs to do more work.
  if (m_runState->delegate->doWork()) {
    scheduleWork();
  }
}

bool MessagePumpUI::processNextWindowsMessage() {
  // If there are sent messages in the queue then PeekMessage internally dispatches the message and returns false.  We
  // return `true` in this case to ensure that the message loop peeks again instead of calling
  // `::MsgWaitForMultipleObjectsEx` again.
  bool sentMessagesInQueue = false;
  DWORD queueStatus = ::GetQueueStatus(QS_SENDMESSAGE);
  if (HIWORD(queueStatus) & QS_SENDMESSAGE) {
    sentMessagesInQueue = true;
  }

  MSG msg;
  if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != FALSE) {
    return processMessageHelper(msg);
  }

  return sentMessagesInQueue;
}

bool MessagePumpUI::processMessageHelper(const MSG& msg) {
  if (msg.message == WM_QUIT) {
    // Repost the QUIT message so that it will be retrieved by the primary `::GetMessage()` loop.
    m_runState->shouldQuit = true;
    ::PostQuitMessage(static_cast<int>(msg.wParam));
    return false;
  }

  // While running our main message pump, we discard kMsgHaveWork messages.
  if (msg.message == kMsgDoWork && msg.hwnd == m_messageWindow.getHandle()) {
    return processPumpReplacementMessage();
  }

  ::TranslateMessage(&msg);
  ::DispatchMessage(&msg);

  return true;
}

bool MessagePumpUI::processPumpReplacementMessage() {
  // When we encounter a `kMsgHaveWork` message, this method is called to peek and process a replacement message. The
  // goal is to make the `kMsgHaveWork` as non-intrusive as possible, even though a continuous stream of such messages
  // are posted.  This method carefully peeks a message while there is no chance for a `kMsgHaveWork` to be pending,
  // then resets the `m_haveWork` flag (allowing a replacement `kMsgHaveWork` to possibly be posted), and finally
  // dispatches that peeked replacement.  Note that the re-post of `kMsgHaveWork` may be asynchronous to this thread!!

  MSG msg;
  const bool haveMessage = ::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != FALSE;

  // Expect no message or a message different than `kMsgHaveWork`.
  DCHECK(!haveMessage || msg.message != kMsgDoWork || msg.hwnd != m_messageWindow.getHandle());

  // Since we discarded a `kMsgHaveWork` message, we must update the flag.
  int oldWorkState = ::InterlockedExchange(&m_workState, WorkState::Ready);
  DCHECK(oldWorkState == WorkState::HaveWork);

  // We don't need a special time slice if we dont't have a message to process.
  if (!haveMessage) {
    return false;
  }

  // Guarantee we'll get another time slice in the case where we go into native windows code.  This `scheduleWork()` may
  // hurt performance a tiny bit when tasks appear very infrequently, but when the event queue is busy, the
  // `kMsgHaveWork` events get (percentage wise) rarer and rarer.
  scheduleWork();

  return processMessageHelper(msg);
}
#endif  // 0

}  // namespace ca

#endif  // 0

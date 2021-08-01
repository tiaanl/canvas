#include "canvas/message_loop/message_pump_ui.h"

#include <GLFW/glfw3.h>

#include "canvas/windows/window.h"
#include "nucleus/high_resolution_timer.h"

namespace ca {

MessagePumpUI::MessagePumpUI(Window* window) : window_{window} {}

MessagePumpUI::~MessagePumpUI() {}

void MessagePumpUI::schedule_task() {}

void MessagePumpUI::run(nu::MessagePump::Delegate* delegate) {
  auto tick = nu::getTimeInMicroseconds();

  for (;;) {
    {
      bool has_more_work = window_->processEvents();
      if (!has_more_work) {
        break;
      }
    }

    auto now = nu::getTimeInMicroseconds();
    window_->tick(static_cast<F32>(1000000.0 / 60.0 / (now - tick)));
    tick = now;

    {
      bool has_more_work = delegate->progress();
      if (!has_more_work) {
        break;
      }
    }

    window_->paint();
  }
}

}  // namespace ca

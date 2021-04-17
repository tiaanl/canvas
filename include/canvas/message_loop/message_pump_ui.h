#pragma once

#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/Macros.h"
#include "nucleus/message_loop/message_pump.h"

namespace ca {

class Window;

class MessagePumpUI : public nu::MessagePump {
  NU_DELETE_COPY_AND_MOVE(MessagePumpUI);

public:
  explicit MessagePumpUI(Window* window);
  ~MessagePumpUI() override;

  // Override: nu::MessagePump
  void schedule_task() override;
  void run(nu::MessagePump::Delegate* delegate) override;

private:
  Window* window_;
};

}  // namespace ca

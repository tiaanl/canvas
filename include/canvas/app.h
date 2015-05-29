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

#ifndef CANVAS_APP_H_
#define CANVAS_APP_H_

#include <vector>

#include "nucleus/macros.h"

#include "canvas/windows/window.h"

namespace ca {

class App {
public:
  // Construct a new app with the specified delegate that will control the app.
  App(WindowDelegate* delegate);

  // Destruct the app.
  ~App();

  // Run the application and only return once all the windows are closed.
  void run();

private:
  // The single window we are managing.
  std::unique_ptr<Window> m_window;

  DISALLOW_COPY_AND_ASSIGN(App);
};

}  // namespace ca

#define CANVAS_APP(DelegateType)                                               \
  int main(int argc, char* argv[]) {                                           \
    ca::App app{new DelegateType};                                             \
    app.run();                                                                 \
    return 0;                                                                  \
  }

#endif  // CANVAS_APP_H_
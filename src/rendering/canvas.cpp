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

#include "canvas/rendering/canvas.h"

#include "canvas/opengl.h"
#include "canvas/windows/window.h"

namespace ca {

Canvas::Canvas(Window* window) : m_window(window) {
  // When the canvas is created, we set the window's context to active.
  m_window->activateContext();
}

Canvas::~Canvas() {
}

void Canvas::clear(const Color& color) {
  glClearColor(
      static_cast<float>(color.r) / 255, static_cast<float>(color.g) / 255,
      static_cast<float>(color.b) / 255, static_cast<float>(color.a) / 255);
  glClear(GL_COLOR_BUFFER_BIT);
}

}  // namespace ca

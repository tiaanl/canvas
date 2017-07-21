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

#ifndef CANVAS_RENDERING_CANVAS_H_
#define CANVAS_RENDERING_CANVAS_H_

#include "canvas/opengl.h"
#include "canvas/rendering/Command.h"
#include "canvas/utils/color.h"
#include "canvas/utils/size.h"
#include "nucleus/macros.h"

namespace ca {

class Window;

class Canvas {
public:
    explicit Canvas(Window* window);
    ~Canvas();

    // Get the size of the render area of the canvas.
    ca::Size<I32> getSize() const;

    // Clear the entire surface of the canvas with the specified color.
    void clear(const Color& color);

    Command* render(GLuint program, GLuint vertexArray, GLenum primitiveType, GLint first, GLint count);

    void render();

private:
    // The window we will paint to.
    Window* m_window;

    std::vector<Command> m_commands;

    DISALLOW_COPY_AND_ASSIGN(Canvas);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_CANVAS_H_

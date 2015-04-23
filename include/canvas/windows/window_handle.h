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

#ifndef CANVAS_WINDOWS_WINDOW_HANDLE_H_
#define CANVAS_WINDOWS_WINDOW_HANDLE_H_

#include <nucleus/config.h>

#if OS(WIN)
#include <nucleus/win/windows_mixin.h>
#endif

namespace ca {

// Native window handle type.

#if OS(WIN)
using WindowHandle = HWND;
#elif OS(MACOSX) || OS(ANDROID)
using WindowHandle = void*;
#elif OS(POSIX)
using WindowHandle = unsigned long;
#else
#error Your platform is not supported.
#endif

}  // namespace ca

#endif  // CANVAS_WINDOWS_WINDOW_HANDLE_H_

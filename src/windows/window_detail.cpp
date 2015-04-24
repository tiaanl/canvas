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

#include "canvas/windows/window_detail.h"

#include <nucleus/config.h>

#if OS(WIN)
#include "canvas/windows/win/window_detail_win.h"
using WindowDetailType = ca::detail::WindowDetailWin;
#else
#error "Your platform is not supported."
#endif

namespace ca {

namespace detail {

// static
std::unique_ptr<WindowDetail> WindowDetail::create(
    VideoMode mode, const std::string& title, uint32_t style,
    const ContextSettings& settings) {
  return std::move(
      std::make_unique<WindowDetailType>(mode, title, style, settings));
}

// static
std::unique_ptr<WindowDetail> WindowDetail::create(WindowHandle handle) {
  return std::move(std::make_unique<WindowDetailType>(handle));
}

WindowDetail::~WindowDetail() {
}

WindowDetail::WindowDetail() {
}

}  // namespace detail

}  // namespace ca

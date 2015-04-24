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

#include "canvas/windows/video_mode.h"

#include <algorithm>

#include <nucleus/win/windows_mixin.h>

namespace ca {

// static
VideoMode VideoMode::getDesktopMode() {
  DEVMODEW devMode;
  devMode.dmSize = sizeof(devMode);
  ::EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &devMode);

  return VideoMode(devMode.dmPelsWidth, devMode.dmPelsHeight,
                   devMode.dmBitsPerPel);
}

// static
std::vector<VideoMode> VideoMode::getFullscreenModes() {
  std::vector<VideoMode> modes;

  // Enumerate all available video modes for the primary display adapter.
  DEVMODEW devMode;
  devMode.dmSize = sizeof(devMode);
  for (int count = 0; ::EnumDisplaySettingsW(nullptr, count, &devMode);
       ++count) {
    VideoMode mode(devMode.dmPelsWidth, devMode.dmPelsHeight,
                   devMode.dmBitsPerPel);

    // Add it only if it is not alread in the array.
    if (std::find(std::begin(modes), std::end(modes), mode) ==
        std::end(modes)) {
      modes.push_back(mode);
    }
  }

  return std::move(modes);
}

}  // namespace ca

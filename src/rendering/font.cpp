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

#include "canvas/rendering/font.h"

#include <vector>

#include "nucleus/logging.h"
#include "nucleus/streams/file_input_stream.h"
#include "nucleus/types.h"
#include "nucleus/utils/stl.h"
#include "canvas/utils/rect.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace ca {

void fontTest() {
  nu::FileInputStream fontStream{
      nu::FilePath{FILE_PATH_LITERAL("C:\\Windows\\Fonts\\arial.ttf")}};
  std::vector<unsigned char> buffer;
  auto length = fontStream.getLength();
  fontStream.read(nu::vectorAsArray(&buffer, length), length);

  stbtt_fontinfo fontInfo;
  if (!stbtt_InitFont(&fontInfo, nu::vectorAsArray(&buffer), 0)) {
    LOG(Error) << "Could not initialize font";
    return;  
  }

  const i32 bitmapWidth = 512;
  const i32 bitmapHeight = 128;
  const i32 lineHeight = 64;

  std::vector<u8> bitmap;
  nu::vectorAsArray(&bitmap, bitmapWidth * bitmapHeight);

  const f32 fontScale = stbtt_ScaleForPixelHeight(&fontInfo, lineHeight);

  std::string words = "How are you?";

  i32 x = 0;
  i32 ascent, descent, lineGap;
  stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);
  ascent *= fontScale;
  descent *= fontScale;

  for (i32 i = 0; i < words.length(); ++i) {
    // Get bounding box for character (may be offset to account for chars that
    // dip above or below the line.
    Rect<i32> rect;
    stbtt_GetCodepointBitmapBox(&fontInfo, words[i], fontScale, fontScale,
                                &rect.pos.x, &rect.pos.y, &rect.size.width,
                                &rect.size.height);
    rect.size.width -= rect.pos.x;
    rect.size.height -= rect.pos.y;

    // Computer Y (different characters have different heights.
    i32 y = ascent + rect.pos.y;

    // Render character (stride and offset is important here.
    i32 byteOffset = x + (y * bitmapWidth);
    stbtt_MakeCodepointBitmap(
        &fontInfo, nu::vectorAsArray(&bitmap) + byteOffset, rect.size.width,
        rect.size.height, bitmapWidth, fontScale, fontScale, words[i]);

    // How wide is the character?
    i32 ax;
    stbtt_GetCodepointHMetrics(&fontInfo, words[i], &ax, 0);
    x += ax * fontScale;

    // Add kerning.
    i32 kern = stbtt_GetCodepointKernAdvance(&fontInfo, words[i], words[i + 1]);
    x += kern * fontScale;
  }

  // Save out a 1 channel image.
  stbi_write_png("C:\\Workspace\\canvas\\out.png", bitmapWidth, bitmapHeight, 1,
                 nu::vectorAsArray(&bitmap), bitmapWidth);
}

}  // namespace ca

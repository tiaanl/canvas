
#include "gtest/gtest.h"
#include "nucleus/Streams/FileInputStream.h"

#include "canvas/Rendering/Font.h"

namespace ca {

TEST(FontTest, Basic) {
#if 0
  fontTest();

  nu::FileInputStream fontStream{
      nu::FilePath{FILE_PATH_LITERAL("C:\\Windows\\Fonts\\arial.ttf")}};

  Font f;
  f.loadFromStream(&fontStream);
  f.getOrInsertGlyph(10, 'a');
#endif  // 0
}

}  // namespace ca

#pragma once

#include "canvas/renderer/types.h"
#include "nucleus/containers/static_array.h"
#include "nucleus/function.h"

namespace ca {

class TextureSlots {
public:
  static constexpr MemSize MAX_TEXTURE_SLOTS = 8;

  TextureSlots();
  TextureSlots(TextureId texture);
  TextureSlots(std::initializer_list<TextureId> textures);

  void set(U32 slot, TextureId texture);
  void clear(U32 slot);

  void for_each_valid_slot(nu::Function<void(U32, TextureId)> func) const;

private:
  nu::StaticArray<TextureId, MAX_TEXTURE_SLOTS> textures_;
};

}  // namespace ca

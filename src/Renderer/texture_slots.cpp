#include "canvas/Renderer/texture_slots.h"

#include <algorithm>

namespace ca {

TextureSlots::TextureSlots() {}

TextureSlots::TextureSlots(TextureId texture) {
  textures_[0] = texture;
}

TextureSlots::TextureSlots(std::initializer_list<TextureId> textures) {
  MemSize index = 0;
  for (auto& texture : textures) {
    textures_[index] = texture;

    ++index;

    if (index >= MAX_TEXTURE_SLOTS) {
      break;
    }
  }
}

void TextureSlots::set(U32 slot, TextureId texture) {
  slot = std::clamp<U32>(slot, 0, 8);
  textures_[slot] = texture;
}

void TextureSlots::clear(U32 slot) {
  slot = std::clamp<U32>(slot, 0, 8);
  textures_[slot] = {};
}

void TextureSlots::for_each_valid_slot(nu::Function<void(U32, TextureId)> func) const {
  for (U32 index = 0; index < textures_.size(); ++index) {
    if (textures_[index].isValid()) {
      func(index, textures_[index]);
    }
  }
}

}  // namespace ca

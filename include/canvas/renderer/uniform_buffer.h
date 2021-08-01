#pragma once

#include <functional>

#include "canvas/renderer/types.h"
#include "canvas/utils/color.h"
#include "floats/mat4.h"
#include "floats/vec2.h"
#include "floats/vec3.h"
#include "floats/vec4.h"
#include "nucleus/containers/dynamic_array.h"
#include "nucleus/function.h"

namespace ca {

class UniformBuffer {
public:
  using ApplyFunc =
      nu::Function<void(UniformId uniformId, ComponentType type, U32 count, const void* values)>;

  void set(UniformId uniformId, F32 value);
  void set(UniformId uniformId, const fl::Vec2& value);
  void set(UniformId uniformId, const fl::Vec3& value);
  void set(UniformId uniformId, const fl::Vec4& value);
  void set(UniformId uniformId, const fl::Mat4& value);
  void set(UniformId uniformId, const Color& value);
  void set(UniformId uniformId, U32 value);
  void set(UniformId uniformId, I32 value);

  void apply(ApplyFunc func) const;

private:
  struct UniformData {
    UniformId uniformId;
    ComponentType type;
    U32 count;
    U8 data[sizeof(F32) * 16];
  };

  void addUniformData(UniformId uniform_id, ComponentType type, U32 count, const void* data);

  nu::DynamicArray<UniformData> m_uniforms;
};

}  // namespace ca
